cmake_minimum_required(VERSION 3.23)
project(HierarchicalStructureOfDataStorage)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")

set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
add_executable(HierarchicalStructureOfDataStorage main.cpp University.cpp University.h Faculty.cpp Faculty.h Department.cpp Department.h Group.cpp Group.h Student.cpp Student.h supportFunctions.cpp supportFunctions.h constants.h Messages.cpp Messages.h validationFunctions.cpp validationFunctions.h FileManager.cpp FileManager.h ConsoleCp.h)
