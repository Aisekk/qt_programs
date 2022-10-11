# CMakeLists.txt for project

cmake_minimum_required(VERSION 3.16.0)

set(PROJECT_NAME 3D_Geometric_Curves)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_C_COMPILER_WORKS 1)
#set(CMAKE_CXX_COMPILER_WORKS 1)

set(BOOST_COMPONENTS system) #thread filesystem)

set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_NO_SYSTEM_PATHS TRUE)
#set (Boost_USE_STATIC_RUNTIME OFF)
#set (BOOST_ALL_DYN_LINK OFF)

set(BOOST_ROOT "D:/tools/boost/boost_1_80_0/")

#set(CMAKE_PREFIX_PATH "D:/tools/boost/boost_1_80_0/")
list(APPEND CMAKE_PREFIX_PATH "D:/tools/boost/boost_1_80_0/")
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} PARENT_SCOPE)

project(${PROJECT_NAME} LANGUAGES CXX)

include_directories (../)

# Подключаем необходимые модули. Для примера подключим program_options
#find_package (Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS}) #ALL)
find_package (Boost REQUIRED COMPONENTS ALL)

#message(STATUS "Boost_INCLUDE_DIRS = " ${Boost_INCLUDE_DIRS})
#message(STATUS "Boost_LIBRARY_DIRS = " ${Boost_LIBRARY_DIRS})

# Если библиотека найдена, то
#if (Boost_FOUND)
    #include_directories (${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы
    #add_executable (${PROJECT_NAME} "main.cpp") # Создаем исполняемый файл для нашего проекта
    #target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES}) # подключаем библиотеку
#endif ()

add_subdirectory(curves_lib)
add_subdirectory(program)

# End file
