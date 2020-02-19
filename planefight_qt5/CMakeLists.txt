cmake_minimum_required(VERSION 3.15)
project(planefight_qt5 LANGUAGES CXX)

find_package(Qt5 REQUIRED Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

aux_source_directory(src sources)
add_executable(${PROJECT_NAME} ${sources})
target_sources(${PROJECT_NAME} PRIVATE res/planefight_qt5.qrc)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG> $<$<CONFIG:Release>:RELEASE>)

if(MSVC_IDE)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "/subsystem:windows /entry:mainCRTStartup")
endif()