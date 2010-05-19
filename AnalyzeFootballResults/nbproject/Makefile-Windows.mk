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
	${OBJECTDIR}/ParseLine.o \
	${OBJECTDIR}/ClubName.o \
	${OBJECTDIR}/Utils.o \
	${OBJECTDIR}/Results.o \
	${OBJECTDIR}/Years.o \
	${OBJECTDIR}/Clubs.o \
	${OBJECTDIR}/ClubInfo.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Windows.mk dist/Windows/MinGW-Windows/libAnalyzeFootballResults.dll

dist/Windows/MinGW-Windows/libAnalyzeFootballResults.dll: ${OBJECTFILES}
	${MKDIR} -p dist/Windows/MinGW-Windows
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libAnalyzeFootballResults.dll ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/ParseLine.o: ParseLine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/ParseLine.o ParseLine.cpp

${OBJECTDIR}/ClubName.o: ClubName.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClubName.o ClubName.cpp

${OBJECTDIR}/Utils.o: Utils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Utils.o Utils.cpp

${OBJECTDIR}/Results.o: Results.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Results.o Results.cpp

${OBJECTDIR}/Years.o: Years.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Years.o Years.cpp

${OBJECTDIR}/Clubs.o: Clubs.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clubs.o Clubs.cpp

${OBJECTDIR}/ClubInfo.o: ClubInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClubInfo.o ClubInfo.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Windows
	${RM} dist/Windows/MinGW-Windows/libAnalyzeFootballResults.dll

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
