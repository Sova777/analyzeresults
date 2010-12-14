#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as
PROC=proc
QMAKE=qmake

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Unix
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES=


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,-rpath ../AnalyzeFootballResults/dist/Linux/GNU-Linux-x86 -L../AnalyzeFootballResults/dist/Linux/GNU-Linux-x86 -lAnalyzeFootballResults

nbproject/qt-${CND_CONF}.mk: nbproject/qt-${CND_CONF}.pro FORCE
	${QMAKE} VPATH=. -o qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.pro
	mv -f qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.mk

FORCE:

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	"${MAKE}" -f nbproject/qt-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/QAnalyzeFootballResults

${CND_BUILDDIR}/Unix/%.o: nbproject/qt-${CND_CONF}.mk
	$(MAKE) -f nbproject/qt-${CND_CONF}.mk "$@"

# Subprojects
.build-subprojects:
	cd ../AnalyzeFootballResults && ${MAKE}  -f Makefile CONF=Linux

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	$(MAKE) -f nbproject/qt-${CND_CONF}.mk distclean

# Subprojects
.clean-subprojects:
	cd ../AnalyzeFootballResults && ${MAKE}  -f Makefile CONF=Linux clean
