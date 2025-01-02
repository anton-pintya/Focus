# Имя проекта
project(nodes)

# Находим все файлы .cpp и .hpp в папках nodes
file(GLOB_RECURSE NODES_SOURCES "*/*.cpp" "*/*.hpp")
#file(GLOB_RECURSE NODES_SOURCES "imu_node/*.cpp" "imu_node/*.hpp")

# Указание директории вывода для файлов CMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/nodes)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/nodes)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/nodes)

# Собираем все найденные файлы в одну переменную
set(SOURCES
    ${NODES_SOURCES}
)

message(STATUS "NODES_SOURCES: ${NODES_SOURCES}")

# Создаем библиотеку sensors из этих файлов
add_library(nodes ${SOURCES})

# Указываем включаемые директории (include directories)
target_include_directories(
        nodes PUBLIC
)

# Связываем с библиотекой utils
target_link_libraries(nodes PUBLIC utils)