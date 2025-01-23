# Имя проекта
project(core)

# Находим все файлы .cpp и .hpp
file(GLOB_RECURSE TRANSPORT_SOURCES "transport/*.cpp" "transport/*.hpp" "transport/msg_generated/*.hpp")
file(GLOB_RECURSE MAP_SOURCES "map/*.cpp" "map/*.hpp")
file(GLOB_RECURSE VIS_SOURCES "visualizer/*.cpp" "visualizer/*.hpp")

# Указание директории вывода для файлов CMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/core)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/core)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/core)

# Собираем все найденные файлы в одну переменную
set(SOURCES
    ${TRANSPORT_SOURCES}
    ${MAP_SOURCES}
    ${VIS_SOURCES}
)

# Создаем библиотеку core из этих файлов
add_library(core ${SOURCES})

# Указываем включаемые директории (include directories)
target_include_directories(
        core PUBLIC
)

# Связываем с библиотекой utils
target_link_libraries(core PUBLIC utils)