project(QFootballStat)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
set(GUI_TYPE WIN32)
set(QT_USE_QTXML TRUE)
set(SRC main.cpp Record.cpp MainWindow.cpp XmlFileReader.cpp moc_MainWindow.cpp)
set(HEADRES MainWindow.h Record.h XmlFileReader.h Report.h constants.h)

include(${QT_USE_FILE})
QT4_ADD_RESOURCES(QFootballStat_rc resources.qrc)

add_executable(QFootballStat WIN32 ${SRC} ${HEADERS} ${QFootballStat_rc})
target_link_libraries(QFootballStat ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY})
