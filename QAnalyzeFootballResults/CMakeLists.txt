project(QAnalyzeFootballResults)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
set(SRC main.cpp mainform.cpp moc_mainform.cpp)
set(HEADRES mainform.hpp)

include_directories ( ../AnalyzeFootballResults )
link_directories ( "C:/Documents and Settings/valera/My Documents/NetBeansProjects/analyzeresults~mercurial/AnalyzeFootballResults/build/Release" )

include(${QT_USE_FILE})
add_executable(QAnalyzeFootballResults ${SRC} ${HEADERS})
target_link_libraries( QAnalyzeFootballResults ${QT_LIBRARIES} AnalyzeFootballResults )
