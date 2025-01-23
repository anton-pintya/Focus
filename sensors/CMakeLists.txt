# Имя проекта
project(sensors)

# Находим все файлы .cpp и .hpp в папках dataset_handler и param_handler

set(REAL_SENSORS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/real_sensors)
set(SOFT_SENSORS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/soft_sensors)

file(GLOB_RECURSE REAL_SENSOR
        "${REAL_SENSORS_DIR}/video/*/*.hpp"
        "${REAL_SENSORS_DIR}/video/*/*.cpp"
        "${REAL_SENSORS_DIR}/video/*.hpp"

        "${REAL_SENSORS_DIR}/imu/*/*.hpp"
        "${REAL_SENSORS_DIR}/imu/*/*.cpp"
        "${REAL_SENSORS_DIR}/imu/*.hpp"
)

file(GLOB_RECURSE SOFT_SENSOR
        "${SOFT_SENSORS_DIR}/detector/*.hpp"
        "${SOFT_SENSORS_DIR}/detector/*.cpp"

        "${SOFT_SENSORS_DIR}/tracker/*.hpp"
        "${SOFT_SENSORS_DIR}/tracker/*.cpp"

        "${SOFT_SENSORS_DIR}/triangulator/*.hpp"
        "${SOFT_SENSORS_DIR}/triangulator/*.cpp"
)

# Указание директории вывода для файлов CMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/sensors)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/sensors)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/sensors)

# Собираем все найденные файлы в одну переменную
set(SOURCES
    ${REAL_SENSOR}
    ${SOFT_SENSOR}
)

# Создаем библиотеку sensors из этих файлов
add_library(sensors ${SOURCES})

# Указываем включаемые директории (include directories)
target_include_directories(
        sensors PUBLIC
)

# Связываем с библиотекой utils
target_link_libraries(sensors PUBLIC utils core)