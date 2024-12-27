cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME VINS-Focus)
project(${PROJECT_NAME})

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# Указываем путь к заголовочным файлам модуля vins_sensors/dataset_handler
include_directories(modules)


# Добавляем подпроекты
add_subdirectory(modules/vins_sensors build/vins_sensors EXCLUDE_FROM_ALL)
add_subdirectory(modules/vins_utils build/vins_utils EXCLUDE_FROM_ALL)

# Подключаем библиотеки


# Основной исполняемый файл проекта
add_executable(${PROJECT_NAME} main.cpp
        modules/vins_core/node/Node.cpp
        modules/vins_core/node/Node.hpp
        modules/vins_core/core.hpp
        modules/vins_core/publisher/Publisher.cpp
        modules/vins_core/publisher/Publisher.hpp
        modules/vins_core/subscriber/Subscriber.cpp
        modules/vins_core/subscriber/Subscriber.hpp
        modules/vins_core/topics/Topic.hpp
)

# Генерируем HPP-файлы vins-сообщений
find_package( PythonInterp 3.10 REQUIRED )

add_custom_target(
        msg_generate ALL
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMAND ${PYTHON_EXECUTABLE} tools/msg_generator.py
        COMMENT "Generating VINS-messages"
)

add_dependencies(${PROJECT_NAME} msg_generate)

target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE vins_sensors vins_utils)