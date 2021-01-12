cmake_minimum_required(VERSION 3.14)

get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Core5Compat REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Core5Compat REQUIRED)

set(PROJECT_SOURCES
	main.cpp 
)

add_executable(${CMAKE_PROJECT_NAME}
	${PROJECT_SOURCES}
)

target_link_libraries(${CMAKE_PROJECT_NAME}  Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${CMAKE_PROJECT_NAME}  Qt${QT_VERSION_MAJOR}::Core5Compat)

