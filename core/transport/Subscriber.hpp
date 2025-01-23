//
// Created by apin on 20.12.2024.
//

#ifndef VINS_FOCUS_SUBSCRIBER_HPP
#define VINS_FOCUS_SUBSCRIBER_HPP


#include <iostream>
#include <fcntl.h>           /* For O_* constants */
#include <sys/mman.h>        /* For shm_open */
#include <unistd.h>          /* For ftruncate */
#include <cstring>           /* For memset, strerror */
#include <string>
#include <stdexcept>


#include "Topic.hpp"


namespace vins {
namespace core {
namespace transport {

    template<typename T>
    class Subscriber {

        public:
            /*********Public fields*********/


            /*********Public methods*********/
            explicit Subscriber() : _topic(&Topic<T>::get_instance()) {};

            void subscribe() {
                if (_topic == nullptr) {
                    throw std::runtime_error("Topic is not initialized");
                }
                _topic->subscribe(this);
            }

            void update() {
                _updated = true;
            }

            T receive() {
                while (!_updated) {}
                _updated = false;
                return _topic->get();
            }


        protected:
            /*********Protected fields*********/


            /*********Protected methods*********/


        private:
            /*********Private fields*********/
            Topic<T>* _topic;
            bool _updated{false};

            /*********Private methods*********/


    };
}; // namespace transport
}; // namespace core
}; // namespace vins



#endif //VINS_FOCUS_SUBSCRIBER_HPP
