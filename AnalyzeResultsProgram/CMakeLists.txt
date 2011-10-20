project(AnalyzeResultsProgram)
cmake_minimum_required(VERSION 2.6)
set(SRC main.cpp)

include_directories ( ../AnalyzeFootballResults )
link_directories ( "C:/Documents and Settings/valera/My Documents/NetBeansProjects/analyzeresults~mercurial/AnalyzeFootballResults/build/Release" )

add_executable(AnalyzeResultsProgram ${SRC})
target_link_libraries( AnalyzeResultsProgram AnalyzeFootballResults )
