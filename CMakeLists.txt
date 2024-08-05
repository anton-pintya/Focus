cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME VINS-Focus)
project(${PROJECT_NAME})

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# Указываем путь к заголовочным файлам модуля vins_core/dataset_handler
include_directories(modules)

# Добавляем исходные файлы модуля vins_core/dataset_handler
set(VINS_CORE_DIR modules/vins_core)

set(SOURCES
    ${VINS_CORE_DIR}/dataset_handler/DatasetHandler.cpp
    ${VINS_CORE_DIR}/param_handler/ParamHandler.cpp
)

# Основной исполняемый файл проекта
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
