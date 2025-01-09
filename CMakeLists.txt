cmake_minimum_required(VERSION 3.10)

project(StudentAPI)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавьте исходники проекта
add_executable(StudentAPI
    main.cpp
    routes/disciplines.cpp
    routes/results.cpp
    routes/tests.cpp
    routes/questions.cpp
    database/db_connection.cpp
)

# Подключите библиотеки
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

target_include_directories(StudentAPI PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(StudentAPI ${PQXX_LIBRARIES})
