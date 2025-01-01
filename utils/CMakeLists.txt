file(GLOB SOURCES
    "*/*.cpp"
    "*.cpp"
)
file(GLOB HEADERS
    "*/*.hpp"
    "*.hpp"
)

add_library(utils ${SOURCES} ${HEADERS})

# Указание директории вывода для файлов CMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/utils)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/utils)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/utils)

# Имя проекта
project(utils)


# Указываем директорию с заголовочными файлами
target_include_directories(utils PUBLIC)