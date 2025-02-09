cmake_minimum_required(VERSION 3.10)
set (CXX=C:/MinGW/bin/g++.exe)
project(Inventory-System-CPP[CXX] VERSION 1.0)
add_executable(Inventory-System-CPP src/main.cpp)
target_include_directories(Inventory-System-CPP PUBLIC ${CMAKE_SOURCE_DIR}/include )
target_link_directories(Inventory-System-CPP PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Inventory-System-CPP PUBLIC sqlite3)

