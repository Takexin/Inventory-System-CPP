cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "C:/ProgramData/mingw64/mingw64/bin/c++.exe")
set(CMAKE_C_COMPILER "C:/ProgramData/mingw64/mingw64/bin/gcc.exe")
project(Inventory-System-CPP VERSION 1.0 LANGUAGES CXX)
add_executable(Inventory-System-CPP src/main.cpp)
target_include_directories(Inventory-System-CPP PUBLIC ${CMAKE_SOURCE_DIR}/include )
target_link_directories(Inventory-System-CPP PUBLIC ${CMAKE_SOURCE_DIR}/lib64)
target_link_libraries(Inventory-System-CPP PUBLIC sqlite3)

#cmake -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER="C:/ProgramData/mingw64/mingw64/bin/c++.exe" -DCMAKE_C_COMPILER="C:/ProgramData/mingw64/mingw64/bin/gcc.exe" ..
