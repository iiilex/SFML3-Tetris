cmake_minimum_required(VERSION 3.28)
project(HelloSFML CXX)

set(SFML_ROOT "D:/SFML-3.0.2")
list(APPEND CMAKE_PREFIX_PATH "${SFML_ROOT}/lib/cmake/SFML")

include(FetchContent)
FetchContent_Declare(sfml GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 3.0.2)
FetchContent_MakeAvailable(sfml)

set(PROJECT_SOURCES
        main.cpp
        src/block.cpp
        src/game.cpp
        src/board.cpp
)
add_executable(HelloSFML ${PROJECT_SOURCES})
target_include_directories(HelloSFML PRIVATE ${CMAKE_SOURCE_DIR}/include)


target_compile_features(HelloSFML PRIVATE cxx_std_20)
target_link_libraries(HelloSFML PRIVATE SFML::Graphics)
target_link_libraries(HelloSFML PRIVATE SFML::Audio)
