cmake_minimum_required(VERSION 3.12)
project(DesktopTimeTable VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(IGNORE_ME ${CMAKE_C_COMPILER})

set(wxBUILD_SHARED OFF)
add_subdirectory(3rdparty/wxWidgets)
option(OPENXLSX_CREATE_DOCS OFF)
option(OPENXLSX_BUILD_SAMPLES OFF)
option(OPENXLSX_BUILD_TESTS OFF)
option(OPENXLSX_BUILD_BENCHMARKS OFF)
option(OPENXLSX_ENABLE_LIBZIP OFF)
add_subdirectory(3rdparty/OpenXLSX)
add_subdirectory(3rdparty/json)


add_executable(DesktopTimeTable WIN32
    src/app.cpp
    src/excel_marker.cpp
    src/excel_marker.h
    src/excel_reader.cpp
    src/excel_reader.h
    src/excel_template.cpp
    src/excel_template.h
    src/excel_writer.cpp
    src/excel_writer.h
    src/generate_frame.cpp
    src/generate_frame.h
    src/main_frame.cpp
    src/main_frame.h
    src/pair.cpp
    src/pair.h
    src/pair_list.cpp
    src/pair_list.h
    src/pair_list_frame.cpp
    src/pair_list_frame.h
    src/pair_manager.cpp
    src/pair_manager.h
    src/template_create_frame.cpp
    src/template_create_frame.h
    src/template_manager.cpp
    src/template_manager.h
    src/template_manager_frame.cpp
    src/template_manager_frame.h
    src/timetable.cpp
    src/timetable.h
    src/timetable_loader_frame.cpp
    src/timetable_loader_frame.h
    src/timetable_manager.cpp
    src/timetable_manager.h
    src/timetable_manager_frame.cpp
    src/timetable_manager_frame.h
    src/codec_converter.cpp
    src/codec_converter.h
)

target_compile_features(DesktopTimeTable PRIVATE cxx_std_17)
target_link_libraries(DesktopTimeTable wx::net wx::core wx::base)
target_link_libraries(DesktopTimeTable OpenXLSX::OpenXLSX)
target_link_libraries(DesktopTimeTable nlohmann_json::nlohmann_json)
