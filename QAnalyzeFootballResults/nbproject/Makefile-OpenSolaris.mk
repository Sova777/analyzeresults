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
CC=cc
CCC=CC
CXX=CC
FC=f95
AS=as
QMAKE=qmake

# Macros
CND_PLATFORM=OracleSolarisStudio-Solaris-x86
CND_CONF=OpenSolaris
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

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
LDLIBSOPTIONS=-R../AnalyzeFootballResults/dist/OpenSolaris/OracleSolarisStudio-Solaris-x86 -L../AnalyzeFootballResults/dist/OpenSolaris/OracleSolarisStudio-Solaris-x86 -lAnalyzeFootballResults

nbproject/qt-${CND_CONF}.mk: nbproject/qt-${CND_CONF}.pro FORCE
	${QMAKE} VPATH=. -o qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.pro
	mv -f qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.mk

FORCE:

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	"${MAKE}" -f nbproject/qt-${CND_CONF}.mk dist/OpenSolaris/OracleSolarisStudio-Solaris-x86/QAnalyzeFootballResults

build/OpenSolaris/%.o: nbproject/qt-OpenSolaris.mk
	$(MAKE) -f nbproject/qt-OpenSolaris.mk "$@"

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS} nbproject/qt-OpenSolaris.mk
	$(MAKE) -f nbproject/qt-OpenSolaris.mk distclean

# Subprojects
.clean-subprojects:
