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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/lusin_counter.o \
	${OBJECTDIR}/lusin_counter_config.o \
	${OBJECTDIR}/lusin_counter_log.o \
	${OBJECTDIR}/lusin_counter_memory.o \
	${OBJECTDIR}/lusin_counter_network.o \
	${OBJECTDIR}/lusin_counter_protocol.o \
	${OBJECTDIR}/lusin_counter_signal.o \
	${OBJECTDIR}/lusin_counter_threads.o


# C Compiler Flags
CFLAGS=-zmuldefs -Wshadow -O3

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lconfig -lpthread -lpcap

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lusin_counter.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lusin_counter.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lusin_counter ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/lusin_counter.o: lusin_counter.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/lusin_counter.o lusin_counter.c

${OBJECTDIR}/lusin_counter_config.o: lusin_counter_config.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/lusin_counter_config.o lusin_counter_config.c

${OBJECTDIR}/lusin_counter_log.o: lusin_counter_log.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/lusin_counter_log.o lusin_counter_log.c

${OBJECTDIR}/lusin_counter_memory.o: lusin_counter_memory.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/lusin_counter_memory.o lusin_counter_memory.c

${OBJECTDIR}/lusin_counter_network.o: lusin_counter_network.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/lusin_counter_network.o lusin_counter_network.c

${OBJECTDIR}/lusin_counter_protocol.o: lusin_counter_protocol.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/lusin_counter_protocol.o lusin_counter_protocol.c

${OBJECTDIR}/lusin_counter_signal.o: lusin_counter_signal.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/lusin_counter_signal.o lusin_counter_signal.c

${OBJECTDIR}/lusin_counter_threads.o: lusin_counter_threads.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/lusin_counter_threads.o lusin_counter_threads.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lusin_counter.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
