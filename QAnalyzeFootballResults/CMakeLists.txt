project(QAnalyzeFootballResults)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
set(SRC main.cpp mainform.cpp)
set(HEADRES mainform.hpp)

include_directories ( ../AnalyzeFootballResults )
link_directories ( C:/tmp/cmake )

include(${QT_USE_FILE})
add_executable(QAnalyzeFootballResults ${SRC} ${HEADERS})
target_link_libraries( QAnalyzeFootballResults ${QT_LIBRARIES} AnalyzeFootballResults )
