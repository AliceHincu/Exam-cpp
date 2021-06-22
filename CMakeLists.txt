cmake_minimum_required(VERSION 3.17)
project(e2_913AliceHincu)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake")
find_package(Qt5Widgets REQUIRED)


add_executable(e2_913AliceHincu
        main.cpp domain.cpp domain.h Repository.cpp Repository.h Service.h Observer.h GUI.cpp GUI.h TableModel.cpp TableModel.h)

target_link_libraries(e2_913AliceHincu Qt5::Widgets)