cmake_minimum_required(VERSION 3.20)
project(sfml_game CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Game app ---
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(rogue_app
  src/main.cpp
)
target_link_libraries(rogue_app
  PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# --- Tests (Catch2 + CTest) ---
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.3
)
FetchContent_MakeAvailable(catch2)

enable_testing()
include(CTest)

add_executable(t_player tests/test_player_move.cpp)
target_include_directories(t_player PRIVATE src)
target_link_libraries(t_player PRIVATE Catch2::Catch2WithMain SFML::Graphics SFML::Window SFML::System)
target_compile_definitions(t_player PRIVATE GAME_TEST)

include(Catch)
catch_discover_tests(t_player)
