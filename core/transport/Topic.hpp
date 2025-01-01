//
// Created by apin on 25.12.2024.
//

#ifndef VINS_FOCUS_TOPIC_HPP
#define VINS_FOCUS_TOPIC_HPP


#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cstring>
#include <mutex>
#include <condition_variable>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <cxxabi.h>


// Шаблонный класс реестра
template <typename T>
struct TopicRegistry : std::false_type {  }; // По умолчанию структура не зарегистрирована

// Специализация для зарегистрированных структур
#define REGISTER_TOPIC(T) template<> struct TopicRegistry<T> : std::true_type {  };
#define DECLARE(n)  #n


namespace vins {
namespace core {
namespace transport {

    template <typename T>
    class Topic {

    public:
        /*********Public fields*********/


        /*********Public methods*********/

        explicit Topic() {
            // Регистрация структуры
            static_assert(TopicRegistry<T>::value, "The specified topic is not registered");

            // Создаем топик и открываем shared memory
            _topic_name = demangle();
            _shm_fd = shm_open(("/" + _topic_name).c_str(), O_CREAT | O_RDWR, 0666);

            if (_shm_fd == -1) {
                throw std::runtime_error("Failed to create/open shared memory: " + std::string(strerror(errno)));
            }

            // Задаем размер shared memory
            if (ftruncate(_shm_fd, sizeof(T)) == -1) {
                throw std::runtime_error("Failed to set shared memory size: " + std::string(strerror(errno)));
            }

            // Отображаем shared memory в адресное пространство
            _shared_memory = mmap(nullptr, sizeof(T), PROT_READ | PROT_WRITE, MAP_SHARED, _shm_fd, 0);

            if (_shared_memory == MAP_FAILED) {
                throw std::runtime_error("Failed to map shared memory: " + std::string(strerror(errno)));
            }

            _updated = false;
        }


        ~Topic() {
            munmap(_shared_memory, sizeof(T));
            close(_shm_fd);
            shm_unlink(_topic_name.c_str());
        }

        /**
         * @brief Pushes a message to the topic in the shared memory
         * @param message
         */
        void post(const T& message) {
            {
                std::lock_guard<std::mutex> lock(_mutex);
                memcpy(_shared_memory, &message, sizeof(message));
            }

            _updated = true;
            _var.notify_all();
        }


        /**
         * @brief Returns the latest message from the topic in the shared memory
         * @return Structure containing the latest message
         */
        T get() {
            std::unique_lock<std::mutex> lock(_mutex);
//            _var.wait(lock, [this] { return _updated; });
            _updated = false;
            T message = *static_cast<T*>(_shared_memory);
            return message;
        }

    protected:
        /*********Protected fields*********/


        /*********Protected methods*********/


    private:
        /*********Private fields*********/
        void* _shared_memory;
        int _shm_fd;
        std::string _topic_name;

        std::mutex _mutex;
        std::condition_variable _var;

        // Updated flag
        bool _updated;

        /*********Private methods*********/

        /**
         * @brief Parses the demangled name of the structure
         * @return Demangled name as std::string
         */
        static std::string demangle() {
            int status = 0;
            char* demangled_name = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
            if (status == 0 && demangled_name != nullptr) {
                std::string result(demangled_name);
                free(demangled_name);
                return result;
            }
            return typeid(T).name();
        }

    };
}; // namespace transport
}; // namespace core
}; // namespace vins


#endif //VINS_FOCUS_TOPIC_HPP
