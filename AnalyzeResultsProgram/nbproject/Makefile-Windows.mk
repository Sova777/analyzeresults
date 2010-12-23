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
FC=f90
AS=as
PROC=proc

# Macros
CND_PLATFORM=OracleSolarisStudio-Solaris-x86
CND_CONF=Windows
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

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
LDLIBSOPTIONS=../AnalyzeFootballResults/dist/Windows/OracleSolarisStudio-Solaris-x86/libAnalyzeFootballResults.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/analyzeresultsprogram

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/analyzeresultsprogram: ../AnalyzeFootballResults/dist/Windows/OracleSolarisStudio-Solaris-x86/libAnalyzeFootballResults.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/analyzeresultsprogram: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/analyzeresultsprogram ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -I../AnalyzeFootballResults -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../AnalyzeFootballResults && ${MAKE}  -f Makefile CONF=Windows

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/analyzeresultsprogram
	${CCADMIN} -clean

# Subprojects
.clean-subprojects:
	cd ../AnalyzeFootballResults && ${MAKE}  -f Makefile CONF=Windows clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
