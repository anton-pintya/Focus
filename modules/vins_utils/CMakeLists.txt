file(GLOB SOURCES
    "*/*.cpp"
    "*.cpp"
)
file(GLOB HEADERS
    "*/*.hpp"
    "*.hpp"
)

add_library(vins_utils ${SOURCES} ${HEADERS})

# Указание директории вывода для файлов CMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_utils)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_utils)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/vins_utils)

# Имя проекта
project(vins_utils)


# Указываем директорию с заголовочными файлами
target_include_directories(vins_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})