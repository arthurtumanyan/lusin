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
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/lusin_store.o \
	${OBJECTDIR}/lusin_store_config.o \
	${OBJECTDIR}/lusin_store_log.o \
	${OBJECTDIR}/lusin_store_memory.o \
	${OBJECTDIR}/lusin_store_mysql.o \
	${OBJECTDIR}/lusin_store_network.o \
	${OBJECTDIR}/lusin_store_protocol.o \
	${OBJECTDIR}/lusin_store_signal.o


# C Compiler Flags
CFLAGS=-zmuldefs -Wshadow -ggdb

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lprotobuf-c -lconfig -lmysqlclient

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lusin_store

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lusin_store: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lusin_store ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/lusin_store.o: nbproject/Makefile-${CND_CONF}.mk lusin_store.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lusin_store.o lusin_store.c

${OBJECTDIR}/lusin_store_config.o: nbproject/Makefile-${CND_CONF}.mk lusin_store_config.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lusin_store_config.o lusin_store_config.c

${OBJECTDIR}/lusin_store_log.o: nbproject/Makefile-${CND_CONF}.mk lusin_store_log.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lusin_store_log.o lusin_store_log.c

${OBJECTDIR}/lusin_store_memory.o: nbproject/Makefile-${CND_CONF}.mk lusin_store_memory.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lusin_store_memory.o lusin_store_memory.c

${OBJECTDIR}/lusin_store_mysql.o: nbproject/Makefile-${CND_CONF}.mk lusin_store_mysql.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lusin_store_mysql.o lusin_store_mysql.c

${OBJECTDIR}/lusin_store_network.o: nbproject/Makefile-${CND_CONF}.mk lusin_store_network.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lusin_store_network.o lusin_store_network.c

${OBJECTDIR}/lusin_store_protocol.o: nbproject/Makefile-${CND_CONF}.mk lusin_store_protocol.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lusin_store_protocol.o lusin_store_protocol.c

${OBJECTDIR}/lusin_store_signal.o: nbproject/Makefile-${CND_CONF}.mk lusin_store_signal.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lusin_store_signal.o lusin_store_signal.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lusin_store

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
