cmake_minimum_required (VERSION 3.8)
project (Diplom)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

configure_file (${SOURCE_DIR}/data.ini ${CMAKE_CURRENT_BINARY_DIR}/data.ini COPYONLY)
add_subdirectory(libpqxx libpqxx-build) 

add_executable (Diplom main.cpp Pauk.h Pauk.cpp Parser.h syntax.h)

target_link_libraries(Diplom Boost::boost OpenSSL::SSL OpenSSL::Crypto pqxx)