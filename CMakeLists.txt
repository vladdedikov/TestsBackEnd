cmake_minimum_required(VERSION 3.10)
project(StudentAPI)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
add_executable(StudentAPI main.cpp routes/disciplines.cpp routes/tests.cpp routes/results.cpp database/db_connection.cpp)
target_include_directories(StudentAPI PUBLIC /usr/include)
target_link_libraries(StudentAPI pqxx pthread)
