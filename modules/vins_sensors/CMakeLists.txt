# Имя проекта
project(vins_sensors)

# Находим все файлы .cpp и .hpp в папках dataset_handler и param_handler
file(GLOB_RECURSE VIDEO_SENSOR "video/src/*.cpp" "video/inc/*.hpp" "video/*.hpp")
file(GLOB_RECURSE IMU_SENSOR "imu/src/*.cpp" "imu/inc/*.hpp" "imu/*.hpp")

# Указание директории вывода для файлов CMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_sensors)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_sensors)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_sensors)

# Собираем все найденные файлы в одну переменную
set(SOURCES 
    ${VIDEO_SENSOR}
    ${IMU_SENSOR}
)

# Создаем библиотеку vins_sensors из этих файлов
add_library(vins_sensors ${SOURCES})

# Указываем включаемые директории (include directories)
target_include_directories(
        vins_sensors PUBLIC
)

# Связываем с библиотекой vins_utils
target_link_libraries(vins_sensors PUBLIC vins_utils)