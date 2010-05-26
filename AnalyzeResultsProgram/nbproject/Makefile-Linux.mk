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

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Linux
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
LDLIBSOPTIONS=-Wl,-rpath ../AnalyzeFootballResults/dist/Linux/GNU-Linux-x86 -L../AnalyzeFootballResults/dist/Linux/GNU-Linux-x86 -lAnalyzeFootballResults

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Linux.mk dist/Linux/GNU-Linux-x86/analyzeresultsprogram

dist/Linux/GNU-Linux-x86/analyzeresultsprogram: ../AnalyzeFootballResults/dist/Linux/GNU-Linux-x86/libAnalyzeFootballResults.so

dist/Linux/GNU-Linux-x86/analyzeresultsprogram: ${OBJECTFILES}
	${MKDIR} -p dist/Linux/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/analyzeresultsprogram ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../AnalyzeFootballResults -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../AnalyzeFootballResults && ${MAKE}  -f Makefile CONF=Linux

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Linux
	${RM} dist/Linux/GNU-Linux-x86/analyzeresultsprogram

# Subprojects
.clean-subprojects:
	cd ../AnalyzeFootballResults && ${MAKE}  -f Makefile CONF=Linux clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
