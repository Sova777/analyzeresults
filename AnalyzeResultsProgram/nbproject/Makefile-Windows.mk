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
FC=
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Windows
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=-L../AnalyzeFootballResults/dist/Windows/MinGW-Windows -lAnalyzeFootballResults

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Windows.mk dist/Windows/MinGW-Windows/analyzeresultsprogram.exe

dist/Windows/MinGW-Windows/analyzeresultsprogram.exe: ../AnalyzeFootballResults/dist/Windows/MinGW-Windows/libAnalyzeFootballResults.dll

dist/Windows/MinGW-Windows/analyzeresultsprogram.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Windows/MinGW-Windows
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/analyzeresultsprogram ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../AnalyzeFootballResults -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../AnalyzeFootballResults && ${MAKE}  -f Makefile CONF=Windows
	cd ../AnalyzeFootballResults && ${MAKE}  -f Makefile CONF=Windows

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Windows
	${RM} dist/Windows/MinGW-Windows/analyzeresultsprogram.exe

# Subprojects
.clean-subprojects:
	cd ../AnalyzeFootballResults && ${MAKE}  -f Makefile CONF=Windows clean
	cd ../AnalyzeFootballResults && ${MAKE}  -f Makefile CONF=Windows clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
