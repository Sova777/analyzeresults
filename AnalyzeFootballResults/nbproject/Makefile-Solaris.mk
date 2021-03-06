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

# Macros
CND_PLATFORM=OracleSolarisStudio-Solaris-x86
CND_DLIB_EXT=so
CND_CONF=Solaris
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ClubInfo.o \
	${OBJECTDIR}/ClubName.o \
	${OBJECTDIR}/Clubs.o \
	${OBJECTDIR}/Results.o \
	${OBJECTDIR}/ResultsDB.o \
	${OBJECTDIR}/Stat.o \
	${OBJECTDIR}/Utils.o \
	${OBJECTDIR}/Years.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-library=stlport4
CXXFLAGS=-library=stlport4

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libAnalyzeFootballResults.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libAnalyzeFootballResults.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libAnalyzeFootballResults.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -library=stlport4 -G -KPIC -norunpath -h libAnalyzeFootballResults.${CND_DLIB_EXT}

${OBJECTDIR}/ClubInfo.o: ClubInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/ClubInfo.o ClubInfo.cpp

${OBJECTDIR}/ClubName.o: ClubName.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/ClubName.o ClubName.cpp

${OBJECTDIR}/Clubs.o: Clubs.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/Clubs.o Clubs.cpp

${OBJECTDIR}/Results.o: Results.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/Results.o Results.cpp

${OBJECTDIR}/ResultsDB.o: ResultsDB.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/ResultsDB.o ResultsDB.cpp

${OBJECTDIR}/Stat.o: Stat.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/Stat.o Stat.cpp

${OBJECTDIR}/Utils.o: Utils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/Utils.o Utils.cpp

${OBJECTDIR}/Years.o: Years.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -KPIC  -o ${OBJECTDIR}/Years.o Years.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libAnalyzeFootballResults.${CND_DLIB_EXT}
	${CCADMIN} -clean

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
