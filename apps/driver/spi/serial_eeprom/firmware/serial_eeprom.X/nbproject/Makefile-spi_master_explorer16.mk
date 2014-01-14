#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-spi_master_explorer16.mk)" "nbproject/Makefile-local-spi_master_explorer16.mk"
include nbproject/Makefile-local-spi_master_explorer16.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=spi_master_explorer16
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/serial_eeprom.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/serial_eeprom.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic32mx_explorer16/system_init.c ../src/system_config/pic32mx_explorer16/system_int.c ../src/system_config/pic32mx_explorer16/system_tasks.c ../src/app.c ../src/main.c ../../../../../../bsp/explorer16/pic32mx795f512l/config_performance.c ../../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c ../../../../../../framework/peripheral/int/src/plib_int_pic32.c ../../../../../../framework/system/clk/src/sys_clk.c ../../../../../../framework/system/clk/src/sys_clk_pic32.c ../../../../../../framework/system/common/sys_queue.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/system/ports/src/sys_ports.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1296198278/system_init.o ${OBJECTDIR}/_ext/1296198278/system_int.o ${OBJECTDIR}/_ext/1296198278/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1959409634/config_performance.o ${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o ${OBJECTDIR}/_ext/1806780248/sys_clk.o ${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o ${OBJECTDIR}/_ext/55393638/sys_queue.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/1653354328/sys_ports.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1296198278/system_init.o.d ${OBJECTDIR}/_ext/1296198278/system_int.o.d ${OBJECTDIR}/_ext/1296198278/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1959409634/config_performance.o.d ${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o.d ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d ${OBJECTDIR}/_ext/1806780248/sys_clk.o.d ${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o.d ${OBJECTDIR}/_ext/55393638/sys_queue.o.d ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d ${OBJECTDIR}/_ext/1653354328/sys_ports.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1296198278/system_init.o ${OBJECTDIR}/_ext/1296198278/system_int.o ${OBJECTDIR}/_ext/1296198278/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1959409634/config_performance.o ${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o ${OBJECTDIR}/_ext/1806780248/sys_clk.o ${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o ${OBJECTDIR}/_ext/55393638/sys_queue.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/1653354328/sys_ports.o

# Source Files
SOURCEFILES=../src/system_config/pic32mx_explorer16/system_init.c ../src/system_config/pic32mx_explorer16/system_int.c ../src/system_config/pic32mx_explorer16/system_tasks.c ../src/app.c ../src/main.c ../../../../../../bsp/explorer16/pic32mx795f512l/config_performance.c ../../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c ../../../../../../framework/peripheral/int/src/plib_int_pic32.c ../../../../../../framework/system/clk/src/sys_clk.c ../../../../../../framework/system/clk/src/sys_clk_pic32.c ../../../../../../framework/system/common/sys_queue.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/system/ports/src/sys_ports.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-spi_master_explorer16.mk dist/${CND_CONF}/${IMAGE_TYPE}/serial_eeprom.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1296198278/system_init.o: ../src/system_config/pic32mx_explorer16/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1296198278 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1296198278/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1296198278/system_init.o.d" -o ${OBJECTDIR}/_ext/1296198278/system_init.o ../src/system_config/pic32mx_explorer16/system_init.c   
	
${OBJECTDIR}/_ext/1296198278/system_int.o: ../src/system_config/pic32mx_explorer16/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1296198278 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1296198278/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1296198278/system_int.o.d" -o ${OBJECTDIR}/_ext/1296198278/system_int.o ../src/system_config/pic32mx_explorer16/system_int.c   
	
${OBJECTDIR}/_ext/1296198278/system_tasks.o: ../src/system_config/pic32mx_explorer16/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1296198278 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1296198278/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1296198278/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1296198278/system_tasks.o ../src/system_config/pic32mx_explorer16/system_tasks.c   
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/1959409634/config_performance.o: ../../../../../../bsp/explorer16/pic32mx795f512l/config_performance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1959409634 
	@${RM} ${OBJECTDIR}/_ext/1959409634/config_performance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1959409634/config_performance.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1959409634/config_performance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1959409634/config_performance.o.d" -o ${OBJECTDIR}/_ext/1959409634/config_performance.o ../../../../../../bsp/explorer16/pic32mx795f512l/config_performance.c   
	
${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o: ../../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1535967397 
	@${RM} ${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o.d" -o ${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o ../../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c   
	
${OBJECTDIR}/_ext/241097022/plib_int_pic32.o: ../../../../../../framework/peripheral/int/src/plib_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/241097022 
	@${RM} ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d" -o ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o ../../../../../../framework/peripheral/int/src/plib_int_pic32.c   
	
${OBJECTDIR}/_ext/1806780248/sys_clk.o: ../../../../../../framework/system/clk/src/sys_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1806780248 
	@${RM} ${OBJECTDIR}/_ext/1806780248/sys_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1806780248/sys_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1806780248/sys_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1806780248/sys_clk.o.d" -o ${OBJECTDIR}/_ext/1806780248/sys_clk.o ../../../../../../framework/system/clk/src/sys_clk.c   
	
${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o: ../../../../../../framework/system/clk/src/sys_clk_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1806780248 
	@${RM} ${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o.d" -o ${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o ../../../../../../framework/system/clk/src/sys_clk_pic32.c   
	
${OBJECTDIR}/_ext/55393638/sys_queue.o: ../../../../../../framework/system/common/sys_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/55393638 
	@${RM} ${OBJECTDIR}/_ext/55393638/sys_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/55393638/sys_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55393638/sys_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/55393638/sys_queue.o.d" -o ${OBJECTDIR}/_ext/55393638/sys_queue.o ../../../../../../framework/system/common/sys_queue.c   
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711155467 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c   
	
${OBJECTDIR}/_ext/1653354328/sys_ports.o: ../../../../../../framework/system/ports/src/sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1653354328 
	@${RM} ${OBJECTDIR}/_ext/1653354328/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1653354328/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1653354328/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1653354328/sys_ports.o.d" -o ${OBJECTDIR}/_ext/1653354328/sys_ports.o ../../../../../../framework/system/ports/src/sys_ports.c   
	
else
${OBJECTDIR}/_ext/1296198278/system_init.o: ../src/system_config/pic32mx_explorer16/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1296198278 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1296198278/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1296198278/system_init.o.d" -o ${OBJECTDIR}/_ext/1296198278/system_init.o ../src/system_config/pic32mx_explorer16/system_init.c   
	
${OBJECTDIR}/_ext/1296198278/system_int.o: ../src/system_config/pic32mx_explorer16/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1296198278 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1296198278/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1296198278/system_int.o.d" -o ${OBJECTDIR}/_ext/1296198278/system_int.o ../src/system_config/pic32mx_explorer16/system_int.c   
	
${OBJECTDIR}/_ext/1296198278/system_tasks.o: ../src/system_config/pic32mx_explorer16/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1296198278 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1296198278/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1296198278/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1296198278/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1296198278/system_tasks.o ../src/system_config/pic32mx_explorer16/system_tasks.c   
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/1959409634/config_performance.o: ../../../../../../bsp/explorer16/pic32mx795f512l/config_performance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1959409634 
	@${RM} ${OBJECTDIR}/_ext/1959409634/config_performance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1959409634/config_performance.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1959409634/config_performance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1959409634/config_performance.o.d" -o ${OBJECTDIR}/_ext/1959409634/config_performance.o ../../../../../../bsp/explorer16/pic32mx795f512l/config_performance.c   
	
${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o: ../../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1535967397 
	@${RM} ${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o.d" -o ${OBJECTDIR}/_ext/1535967397/drv_spi_dynamic.o ../../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c   
	
${OBJECTDIR}/_ext/241097022/plib_int_pic32.o: ../../../../../../framework/peripheral/int/src/plib_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/241097022 
	@${RM} ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d" -o ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o ../../../../../../framework/peripheral/int/src/plib_int_pic32.c   
	
${OBJECTDIR}/_ext/1806780248/sys_clk.o: ../../../../../../framework/system/clk/src/sys_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1806780248 
	@${RM} ${OBJECTDIR}/_ext/1806780248/sys_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1806780248/sys_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1806780248/sys_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1806780248/sys_clk.o.d" -o ${OBJECTDIR}/_ext/1806780248/sys_clk.o ../../../../../../framework/system/clk/src/sys_clk.c   
	
${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o: ../../../../../../framework/system/clk/src/sys_clk_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1806780248 
	@${RM} ${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o.d" -o ${OBJECTDIR}/_ext/1806780248/sys_clk_pic32.o ../../../../../../framework/system/clk/src/sys_clk_pic32.c   
	
${OBJECTDIR}/_ext/55393638/sys_queue.o: ../../../../../../framework/system/common/sys_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/55393638 
	@${RM} ${OBJECTDIR}/_ext/55393638/sys_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/55393638/sys_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/55393638/sys_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/55393638/sys_queue.o.d" -o ${OBJECTDIR}/_ext/55393638/sys_queue.o ../../../../../../framework/system/common/sys_queue.c   
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711155467 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c   
	
${OBJECTDIR}/_ext/1653354328/sys_ports.o: ../../../../../../framework/system/ports/src/sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1653354328 
	@${RM} ${OBJECTDIR}/_ext/1653354328/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1653354328/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1653354328/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_explorer16" -MMD -MF "${OBJECTDIR}/_ext/1653354328/sys_ports.o.d" -o ${OBJECTDIR}/_ext/1653354328/sys_ports.o ../../../../../../framework/system/ports/src/sys_ports.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/serial_eeprom.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/serial_eeprom.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/serial_eeprom.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/serial_eeprom.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/serial_eeprom.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/spi_master_explorer16
	${RM} -r dist/spi_master_explorer16

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
