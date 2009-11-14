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
CCADMIN=CCadmin
RANLIB=ranlib
CC=cc
CCC=CC
CXX=CC
FC=f95
AS=as

# Macros
CND_PLATFORM=SunStudio-Solaris-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/club_info_name.o \
	${OBJECTDIR}/clubs.o \
	${OBJECTDIR}/parse_file.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/club_info.o \
	${OBJECTDIR}/utils.o \
	${OBJECTDIR}/years.o \
	${OBJECTDIR}/results.o

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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/SunStudio-Solaris-x86/analyzefootballresults

dist/Release/SunStudio-Solaris-x86/analyzefootballresults: ${OBJECTFILES}
	${MKDIR} -p dist/Release/SunStudio-Solaris-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/analyzefootballresults ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/club_info_name.o: nbproject/Makefile-${CND_CONF}.mk club_info_name.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/club_info_name.o club_info_name.cpp

${OBJECTDIR}/clubs.o: nbproject/Makefile-${CND_CONF}.mk clubs.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/clubs.o clubs.cpp

${OBJECTDIR}/parse_file.o: nbproject/Makefile-${CND_CONF}.mk parse_file.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/parse_file.o parse_file.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/club_info.o: nbproject/Makefile-${CND_CONF}.mk club_info.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/club_info.o club_info.cpp

${OBJECTDIR}/utils.o: nbproject/Makefile-${CND_CONF}.mk utils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/utils.o utils.cpp

${OBJECTDIR}/years.o: nbproject/Makefile-${CND_CONF}.mk years.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/years.o years.cpp

${OBJECTDIR}/results.o: nbproject/Makefile-${CND_CONF}.mk results.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/results.o results.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/SunStudio-Solaris-x86/analyzefootballresults
	${CCADMIN} -clean

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
