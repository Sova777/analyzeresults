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
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ClubInfo.o \
	${OBJECTDIR}/ClubInfoName.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/Utils.o \
	${OBJECTDIR}/Clubs.o \
	${OBJECTDIR}/ParseLine.o \
	${OBJECTDIR}/Results.o \
	${OBJECTDIR}/AllMatches.o \
	${OBJECTDIR}/Years.o

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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/SunStudio-Solaris-x86/analyzefootballresults

dist/Debug/SunStudio-Solaris-x86/analyzefootballresults: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/SunStudio-Solaris-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/analyzefootballresults ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/ClubInfo.o: nbproject/Makefile-${CND_CONF}.mk ClubInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/ClubInfo.o ClubInfo.cpp

${OBJECTDIR}/ClubInfoName.o: nbproject/Makefile-${CND_CONF}.mk ClubInfoName.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/ClubInfoName.o ClubInfoName.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/Utils.o: nbproject/Makefile-${CND_CONF}.mk Utils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/Utils.o Utils.cpp

${OBJECTDIR}/Clubs.o: nbproject/Makefile-${CND_CONF}.mk Clubs.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/Clubs.o Clubs.cpp

${OBJECTDIR}/ParseLine.o: nbproject/Makefile-${CND_CONF}.mk ParseLine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/ParseLine.o ParseLine.cpp

${OBJECTDIR}/Results.o: nbproject/Makefile-${CND_CONF}.mk Results.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/Results.o Results.cpp

${OBJECTDIR}/AllMatches.o: nbproject/Makefile-${CND_CONF}.mk AllMatches.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/AllMatches.o AllMatches.cpp

${OBJECTDIR}/Years.o: nbproject/Makefile-${CND_CONF}.mk Years.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/Years.o Years.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/SunStudio-Solaris-x86/analyzefootballresults
	${CCADMIN} -clean

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
