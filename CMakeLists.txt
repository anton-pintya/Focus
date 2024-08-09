cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME VINS-Focus)
project(${PROJECT_NAME})

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# Указываем путь к заголовочным файлам модуля vins_core/dataset_handler
include_directories(modules)

# set(VINS_CORE_DIR modules/vins_core)
# set(VINS_UTIL_DIR modules/vins_utils)

# add_subdirectory(${VINS_CORE_DIR})


# Добавляем подпроекты
add_subdirectory(modules/vins_core build/vins_core EXCLUDE_FROM_ALL)
add_subdirectory(modules/vins_utils build/vins_utils EXCLUDE_FROM_ALL)

# Подключаем библиотеки


# Основной исполняемый файл проекта
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE vins_core vins_utils)


# target_link_libraries(${PROJECT_NAME} vins_utils)
# target_link_libraries(${PROJECT_NAME} vins_core)


# # Установка пути для сборки

# # Добавление поддиректорий
# add_subdirectory(modules/vins_core)
# add_subdirectory(modules/vins_utils)

# # Главный исполняемый файл
# add_executable(${PROJECT_NAME} main.cpp)

# # Подключение библиотек
# target_link_libraries(${PROJECT_NAME} vins_core vins_utils ${OpenCV_LIBS})
