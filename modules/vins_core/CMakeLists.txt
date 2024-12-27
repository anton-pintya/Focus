# Имя проекта
project(vins_core)

# Находим все файлы .cpp и .hpp
file(GLOB_RECURSE NODE_SOURCES "node/*.cpp" "node/*.hpp")
file(GLOB_RECURSE PUB_SOURCES "publisher/*.cpp" "publisher/*.hpp")
file(GLOB_RECURSE SUB_SOURCES "subscriber/*.cpp" "subscriber/*.hpp")

# Указание директории вывода для файлов CMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_core)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_core)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_core)

# Собираем все найденные файлы в одну переменную
set(SOURCES
    ${NODE_SOURCES}
    ${PUB_SOURCES}
    ${SUB_SOURCES}
)

# Создаем библиотеку vins_core из этих файлов
add_library(vins_core ${SOURCES})

# Указываем включаемые директории (include directories)
target_include_directories(
        vins_core PUBLIC
)

# Связываем с библиотекой vins_utils
target_link_libraries(vins_core PUBLIC vins_utils)