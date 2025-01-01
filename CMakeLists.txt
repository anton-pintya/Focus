cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME VINS-Focus)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-address-of-packed-member")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_LIST_DIR}/libraries)

# Указываем путь к заголовочным файлам модуля sensors/dataset_handler
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(core)
include_directories(sensors)
include_directories(utils)


# Добавляем подпроекты
add_subdirectory(core build/core EXCLUDE_FROM_ALL)
add_subdirectory(sensors build/sensors EXCLUDE_FROM_ALL)
add_subdirectory(utils build/utils EXCLUDE_FROM_ALL)


# Подключаем библиотеки


# Основной исполняемый файл проекта
add_executable(${PROJECT_NAME} main.cpp)

# Генерируем HPP-файлы vins-сообщений
find_package( PythonInterp 3.10 REQUIRED )

add_custom_target(
        msg_generate ALL
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMAND ${PYTHON_EXECUTABLE} tools/msg_generator.py
        COMMENT "Generating VINS-messages"
)

#add_dependencies(${PROJECT_NAME} msg_generate)

target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE utils)
target_link_libraries(${PROJECT_NAME} PRIVATE sensors)
