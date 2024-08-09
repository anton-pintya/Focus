# Имя проекта
project(vins_core)

# Находим все файлы .cpp и .hpp в папках dataset_handler и param_handler
file(GLOB_RECURSE VIDEO_SOURCE_SOURCES "video_source/*.cpp" "video_source/*.hpp")
file(GLOB_RECURSE PARAM_HANDLER_SOURCES "param_handler/*.cpp" "param_handler/*.hpp")
file(GLOB_RECURSE CAMERA_MODEL_SOURCES "camera_model/*.cpp" "camera_model/*.hpp")

# Указание директории вывода для файлов CMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_core)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_core)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_core)

# Собираем все найденные файлы в одну переменную
set(SOURCES ${VIDEO_SOURCE_SOURCES} ${PARAM_HANDLER_SOURCES} ${CAMERA_MODEL_SOURCES})

# Создаем библиотеку vins_core из этих файлов
add_library(vins_core ${SOURCES})

# Указываем включаемые директории (include directories)
target_include_directories(vins_core PUBLIC video_source param_handler camera_model)

# Связываем с библиотекой vins_utils
target_link_libraries(vins_core PUBLIC vins_utils)