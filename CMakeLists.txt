cmake_minimum_required(VERSION 3.15)
project(planefight CXX)

find_package(Qt5 REQUIRED Widgets)

set(target planefight_qt5)
aux_source_directory(src sources)
add_executable(${target} ${sources})
target_sources(${target} PRIVATE asset/${target}.qrc)

target_compile_definitions(${target} PRIVATE
$<$<CONFIG:Debug>:DEBUG>
$<$<CONFIG:Release>:RELEASE>)

set_target_properties(${target} PROPERTIES
AUTOMOC ON
AUTORCC ON
AUTOUIC ON)

target_link_libraries(${target} PRIVATE
Qt5::Widgets)

if(MSVC_IDE)
    set_target_properties(${target} PROPERTIES LINK_FLAGS_RELEASE "/subsystem:windows /entry:mainCRTStartup")
endif()