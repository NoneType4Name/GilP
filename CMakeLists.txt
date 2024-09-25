set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.5)

set(INJECTOR "${EXECUTABLE_NAME}-injector")
set(DUMMY_WINDOW "${EXECUTABLE_NAME}-DummyWindow")

project(
  "GipL"
  LANGUAGES CXX
  VERSION 0.0.1.0)
set(EXECUTABLE_NAME "GipL")

find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)

file(GLOB IMGUI_IMPL_BINDINGS "${PROJECT_SOURCE_DIR}/bindings/*.cpp")
add_executable(DUMMY_WINDOW src/app.cxx)
add_executable(INJECTOR src/injector.cxx)
add_library(${EXECUTABLE_NAME} SHARED src/GilP.cxx)

target_include_directories(${EXECUTABLE_NAME} bindings/)
target_link_libraries(${EXECUTABLE_NAME} imgui::imgui)
target_link_libraries(${EXECUTABLE_NAME} glfw)

target_link_libraries(${DUMMY_WINDOW} glfw)

target_link_libraries(${INJECTOR} spdlog::spdlog)