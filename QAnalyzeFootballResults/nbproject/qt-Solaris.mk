#############################################################################
# Makefile for building: dist/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults
# Generated by qmake (2.01a) (Qt 4.7.1) on: Tue Feb 14 18:15:13 2012
# Project:  nbproject/qt-Solaris.pro
# Template: app
# Command: /usr/local/Trolltech/Qt-4.7.1/bin/qmake -spec /usr/local/Trolltech/Qt-4.7.1/mkspecs/solaris-cc VPATH=. -o qttmp-Solaris.mk nbproject/qt-Solaris.pro
#############################################################################

####### Compiler, tools and options

CC            = cc
CXX           = CC
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -g -mt $(DEFINES)
CXXFLAGS      = -g -mt $(DEFINES)
INCPATH       = -I/usr/local/Trolltech/Qt-4.7.1/mkspecs/solaris-cc -Inbproject -I/usr/local/Trolltech/Qt-4.7.1/include/QtCore -I/usr/local/Trolltech/Qt-4.7.1/include/QtGui -I/usr/local/Trolltech/Qt-4.7.1/include -I../AnalyzeFootballResults -I. -I. -Inbproject -I/usr/sfw/include -I.
LINK          = CC
LFLAGS        = -mt -R/usr/local/Trolltech/Qt-4.7.1/lib
LIBS          = $(SUBLIBS)  -L/usr/sfw/lib -L/usr/local/Trolltech/Qt-4.7.1/lib -R../AnalyzeFootballResults/dist/Unix/OracleSolarisStudio-Solaris-x86 ../AnalyzeFootballResults/dist/Unix/OracleSolarisStudio-Solaris-x86/libAnalyzeFootballResults.so -lQtGui -L/usr/local/Trolltech/Qt-4.7.1/lib -L/usr/sfw/lib -L/usr/openwin/lib -lQtCore -lpthread -lrt 
AR            = CC -xar -o
RANLIB        = 
QMAKE         = /usr/local/Trolltech/Qt-4.7.1/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/Solaris/OracleSolarisStudio-Solaris-x86/

####### Files

SOURCES       = mainform.cpp \
		main.cpp moc_mainform.cpp
OBJECTS       = build/Solaris/OracleSolarisStudio-Solaris-x86/mainform.o \
		build/Solaris/OracleSolarisStudio-Solaris-x86/main.o \
		build/Solaris/OracleSolarisStudio-Solaris-x86/moc_mainform.o
DIST          = /usr/local/Trolltech/Qt-4.7.1/mkspecs/common/unix.conf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/qconfig.pri \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/debug.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/warn_on.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/qt.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/moc.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/resources.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/uic.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/lex.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/include_source_dir.prf \
		nbproject/qt-Solaris.pro
QMAKE_TARGET  = QAnalyzeFootballResults
DESTDIR       = dist/Solaris/OracleSolarisStudio-Solaris-x86/
TARGET        = dist/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: qttmp-Solaris.mk $(TARGET)

$(TARGET): ui_mainform.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) dist/Solaris/OracleSolarisStudio-Solaris-x86/ || $(MKDIR) dist/Solaris/OracleSolarisStudio-Solaris-x86/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

qttmp-Solaris.mk: nbproject/qt-Solaris.pro  /usr/local/Trolltech/Qt-4.7.1/mkspecs/solaris-cc/qmake.conf /usr/local/Trolltech/Qt-4.7.1/mkspecs/common/unix.conf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/qconfig.pri \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/debug.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/warn_on.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/qt.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/moc.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/resources.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/uic.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/lex.prf \
		/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/include_source_dir.prf \
		/usr/local/Trolltech/Qt-4.7.1/lib/libQtGui.prl \
		/usr/local/Trolltech/Qt-4.7.1/lib/libQtCore.prl
	$(QMAKE) -spec /usr/local/Trolltech/Qt-4.7.1/mkspecs/solaris-cc VPATH=. -o qttmp-Solaris.mk nbproject/qt-Solaris.pro
/usr/local/Trolltech/Qt-4.7.1/mkspecs/common/unix.conf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/qconfig.pri:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/qt_functions.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/qt_config.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/exclusive_builds.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/default_pre.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/debug.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/default_post.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/warn_on.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/qt.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/unix/thread.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/moc.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/resources.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/uic.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/yacc.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/lex.prf:
/usr/local/Trolltech/Qt-4.7.1/mkspecs/features/include_source_dir.prf:
/usr/local/Trolltech/Qt-4.7.1/lib/libQtGui.prl:
/usr/local/Trolltech/Qt-4.7.1/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/Trolltech/Qt-4.7.1/mkspecs/solaris-cc VPATH=. -o qttmp-Solaris.mk nbproject/qt-Solaris.pro

dist: 
	@$(CHK_DIR_EXISTS) nbproject/build/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults1.0.0 || $(MKDIR) nbproject/build/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) nbproject/build/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults1.0.0/ && $(COPY_FILE) --parents mainform.h nbproject/build/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults1.0.0/ && $(COPY_FILE) --parents mainform.cpp main.cpp nbproject/build/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults1.0.0/ && $(COPY_FILE) --parents mainform.ui nbproject/build/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults1.0.0/ && (cd `dirname nbproject/build/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults1.0.0` && $(TAR) QAnalyzeFootballResults1.0.0.tar QAnalyzeFootballResults1.0.0 && $(COMPRESS) QAnalyzeFootballResults1.0.0.tar) && $(MOVE) `dirname nbproject/build/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults1.0.0`/QAnalyzeFootballResults1.0.0.tar.gz . && $(DEL_FILE) -r nbproject/build/Solaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) -r $(OBJECTS_DIR)Templates.DB $(OBJECTS_DIR)SunWS_cache
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) qttmp-Solaris.mk


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainform.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainform.cpp
moc_mainform.cpp: ui_mainform.h \
		mainform.h
	/usr/local/Trolltech/Qt-4.7.1/bin/moc $(DEFINES) $(INCPATH) mainform.h -o moc_mainform.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainform.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainform.h
ui_mainform.h: mainform.ui
	/usr/local/Trolltech/Qt-4.7.1/bin/uic mainform.ui -o ui_mainform.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

build/Solaris/OracleSolarisStudio-Solaris-x86/mainform.o: mainform.cpp mainform.h \
		ui_mainform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Solaris/OracleSolarisStudio-Solaris-x86/mainform.o mainform.cpp

build/Solaris/OracleSolarisStudio-Solaris-x86/main.o: main.cpp mainform.h \
		ui_mainform.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Solaris/OracleSolarisStudio-Solaris-x86/main.o main.cpp

build/Solaris/OracleSolarisStudio-Solaris-x86/moc_mainform.o: moc_mainform.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Solaris/OracleSolarisStudio-Solaris-x86/moc_mainform.o moc_mainform.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

