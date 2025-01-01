# Имя проекта
project(sensors)

# Находим все файлы .cpp и .hpp в папках dataset_handler и param_handler
file(GLOB_RECURSE VIDEO_SENSOR "video/*/*.cpp" "video/*/*.hpp" "video/*.hpp")
file(GLOB_RECURSE IMU_SENSOR "imu/*/*.cpp" "imu/*/*.hpp" "imu/*.hpp")

# Указание директории вывода для файлов CMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/sensors)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/sensors)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/sensors)

# Собираем все найденные файлы в одну переменную
set(SOURCES 
    ${VIDEO_SENSOR}
    ${IMU_SENSOR}
)

# Создаем библиотеку sensors из этих файлов
add_library(sensors ${SOURCES})

# Указываем включаемые директории (include directories)
target_include_directories(
        sensors PUBLIC
)

# Связываем с библиотекой utils
target_link_libraries(sensors PUBLIC utils)