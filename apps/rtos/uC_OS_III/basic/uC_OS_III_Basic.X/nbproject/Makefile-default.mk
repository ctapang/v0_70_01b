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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/uC_OS_III_Basic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/uC_OS_III_Basic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_a.s ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_c.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/cpu_core.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_a.S ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_c.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_cfg_app.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_core.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_dbg.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_flag.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_int.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mem.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_msg.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mutex.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_pend_multi.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_prio.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_q.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_sem.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_stat.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_task.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tick.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_time.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tmr.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_var.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_ascii.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_math.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_mem.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_str.c ../src/_exit.c ../src/default-bootstrap-exception-handler.c ../src/default-general-exception-handler.c ../src/default-nmi-handler.S ../src/default-on-bootstrap.c ../src/default-on-reset.c ../src/defaultinterrupt.c ../src/p32mz2048ech144_voff_init.S ../src/pic32_software_reset.S ../src/main.c ../src/crt0.S ../src/config_words.c ../src/bsp.c ../src/bsp_a.S

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1872009673/cpu_a.o ${OBJECTDIR}/_ext/1872009673/cpu_c.o ${OBJECTDIR}/_ext/400789967/cpu_core.o ${OBJECTDIR}/_ext/681344765/os_cpu_a.o ${OBJECTDIR}/_ext/681344765/os_cpu_c.o ${OBJECTDIR}/_ext/773801292/os_cfg_app.o ${OBJECTDIR}/_ext/773801292/os_core.o ${OBJECTDIR}/_ext/773801292/os_dbg.o ${OBJECTDIR}/_ext/773801292/os_flag.o ${OBJECTDIR}/_ext/773801292/os_int.o ${OBJECTDIR}/_ext/773801292/os_mem.o ${OBJECTDIR}/_ext/773801292/os_msg.o ${OBJECTDIR}/_ext/773801292/os_mutex.o ${OBJECTDIR}/_ext/773801292/os_pend_multi.o ${OBJECTDIR}/_ext/773801292/os_prio.o ${OBJECTDIR}/_ext/773801292/os_q.o ${OBJECTDIR}/_ext/773801292/os_sem.o ${OBJECTDIR}/_ext/773801292/os_stat.o ${OBJECTDIR}/_ext/773801292/os_task.o ${OBJECTDIR}/_ext/773801292/os_tick.o ${OBJECTDIR}/_ext/773801292/os_time.o ${OBJECTDIR}/_ext/773801292/os_tmr.o ${OBJECTDIR}/_ext/773801292/os_var.o ${OBJECTDIR}/_ext/400781554/lib_ascii.o ${OBJECTDIR}/_ext/400781554/lib_math.o ${OBJECTDIR}/_ext/400781554/lib_mem.o ${OBJECTDIR}/_ext/400781554/lib_str.o ${OBJECTDIR}/_ext/1360937237/_exit.o ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o ${OBJECTDIR}/_ext/1360937237/default-on-reset.o ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/crt0.o ${OBJECTDIR}/_ext/1360937237/config_words.o ${OBJECTDIR}/_ext/1360937237/bsp.o ${OBJECTDIR}/_ext/1360937237/bsp_a.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1872009673/cpu_a.o.d ${OBJECTDIR}/_ext/1872009673/cpu_c.o.d ${OBJECTDIR}/_ext/400789967/cpu_core.o.d ${OBJECTDIR}/_ext/681344765/os_cpu_a.o.d ${OBJECTDIR}/_ext/681344765/os_cpu_c.o.d ${OBJECTDIR}/_ext/773801292/os_cfg_app.o.d ${OBJECTDIR}/_ext/773801292/os_core.o.d ${OBJECTDIR}/_ext/773801292/os_dbg.o.d ${OBJECTDIR}/_ext/773801292/os_flag.o.d ${OBJECTDIR}/_ext/773801292/os_int.o.d ${OBJECTDIR}/_ext/773801292/os_mem.o.d ${OBJECTDIR}/_ext/773801292/os_msg.o.d ${OBJECTDIR}/_ext/773801292/os_mutex.o.d ${OBJECTDIR}/_ext/773801292/os_pend_multi.o.d ${OBJECTDIR}/_ext/773801292/os_prio.o.d ${OBJECTDIR}/_ext/773801292/os_q.o.d ${OBJECTDIR}/_ext/773801292/os_sem.o.d ${OBJECTDIR}/_ext/773801292/os_stat.o.d ${OBJECTDIR}/_ext/773801292/os_task.o.d ${OBJECTDIR}/_ext/773801292/os_tick.o.d ${OBJECTDIR}/_ext/773801292/os_time.o.d ${OBJECTDIR}/_ext/773801292/os_tmr.o.d ${OBJECTDIR}/_ext/773801292/os_var.o.d ${OBJECTDIR}/_ext/400781554/lib_ascii.o.d ${OBJECTDIR}/_ext/400781554/lib_math.o.d ${OBJECTDIR}/_ext/400781554/lib_mem.o.d ${OBJECTDIR}/_ext/400781554/lib_str.o.d ${OBJECTDIR}/_ext/1360937237/_exit.o.d ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d ${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/crt0.o.d ${OBJECTDIR}/_ext/1360937237/config_words.o.d ${OBJECTDIR}/_ext/1360937237/bsp.o.d ${OBJECTDIR}/_ext/1360937237/bsp_a.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1872009673/cpu_a.o ${OBJECTDIR}/_ext/1872009673/cpu_c.o ${OBJECTDIR}/_ext/400789967/cpu_core.o ${OBJECTDIR}/_ext/681344765/os_cpu_a.o ${OBJECTDIR}/_ext/681344765/os_cpu_c.o ${OBJECTDIR}/_ext/773801292/os_cfg_app.o ${OBJECTDIR}/_ext/773801292/os_core.o ${OBJECTDIR}/_ext/773801292/os_dbg.o ${OBJECTDIR}/_ext/773801292/os_flag.o ${OBJECTDIR}/_ext/773801292/os_int.o ${OBJECTDIR}/_ext/773801292/os_mem.o ${OBJECTDIR}/_ext/773801292/os_msg.o ${OBJECTDIR}/_ext/773801292/os_mutex.o ${OBJECTDIR}/_ext/773801292/os_pend_multi.o ${OBJECTDIR}/_ext/773801292/os_prio.o ${OBJECTDIR}/_ext/773801292/os_q.o ${OBJECTDIR}/_ext/773801292/os_sem.o ${OBJECTDIR}/_ext/773801292/os_stat.o ${OBJECTDIR}/_ext/773801292/os_task.o ${OBJECTDIR}/_ext/773801292/os_tick.o ${OBJECTDIR}/_ext/773801292/os_time.o ${OBJECTDIR}/_ext/773801292/os_tmr.o ${OBJECTDIR}/_ext/773801292/os_var.o ${OBJECTDIR}/_ext/400781554/lib_ascii.o ${OBJECTDIR}/_ext/400781554/lib_math.o ${OBJECTDIR}/_ext/400781554/lib_mem.o ${OBJECTDIR}/_ext/400781554/lib_str.o ${OBJECTDIR}/_ext/1360937237/_exit.o ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o ${OBJECTDIR}/_ext/1360937237/default-on-reset.o ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/crt0.o ${OBJECTDIR}/_ext/1360937237/config_words.o ${OBJECTDIR}/_ext/1360937237/bsp.o ${OBJECTDIR}/_ext/1360937237/bsp_a.o

# Source Files
SOURCEFILES=../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_a.s ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_c.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/cpu_core.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_a.S ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_c.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_cfg_app.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_core.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_dbg.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_flag.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_int.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mem.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_msg.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mutex.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_pend_multi.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_prio.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_q.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_sem.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_stat.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_task.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tick.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_time.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tmr.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_var.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_ascii.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_math.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_mem.c ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_str.c ../src/_exit.c ../src/default-bootstrap-exception-handler.c ../src/default-general-exception-handler.c ../src/default-nmi-handler.S ../src/default-on-bootstrap.c ../src/default-on-reset.c ../src/defaultinterrupt.c ../src/p32mz2048ech144_voff_init.S ../src/pic32_software_reset.S ../src/main.c ../src/crt0.S ../src/config_words.c ../src/bsp.c ../src/bsp_a.S


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/uC_OS_III_Basic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2048ECH144
MP_LINKER_FILE_OPTION=,--script="..\src\p32MZ2048ECH144.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1872009673/cpu_a.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1872009673 
	@${RM} ${OBJECTDIR}/_ext/1872009673/cpu_a.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1872009673/cpu_a.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -o ${OBJECTDIR}/_ext/1872009673/cpu_a.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_a.s  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--gdwarf-2,-MD="${OBJECTDIR}/_ext/1872009673/cpu_a.o.d",-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
else
${OBJECTDIR}/_ext/1872009673/cpu_a.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1872009673 
	@${RM} ${OBJECTDIR}/_ext/1872009673/cpu_a.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1872009673/cpu_a.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -o ${OBJECTDIR}/_ext/1872009673/cpu_a.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_a.s  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),--gdwarf-2,-MD="${OBJECTDIR}/_ext/1872009673/cpu_a.o.d",-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/681344765/os_cpu_a.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681344765 
	@${RM} ${OBJECTDIR}/_ext/681344765/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/681344765/os_cpu_a.o 
	@${RM} ${OBJECTDIR}/_ext/681344765/os_cpu_a.o.ok ${OBJECTDIR}/_ext/681344765/os_cpu_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681344765/os_cpu_a.o.d" "${OBJECTDIR}/_ext/681344765/os_cpu_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/681344765/os_cpu_a.o.d"  -o ${OBJECTDIR}/_ext/681344765/os_cpu_a.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_a.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/681344765/os_cpu_a.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o: ../src/default-nmi-handler.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.ok ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d" "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d"  -o ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o ../src/default-nmi-handler.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o: ../src/p32mz2048ech144_voff_init.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.ok ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d" "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d"  -o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o ../src/p32mz2048ech144_voff_init.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o: ../src/pic32_software_reset.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.ok ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d" "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d"  -o ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o ../src/pic32_software_reset.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
${OBJECTDIR}/_ext/1360937237/crt0.o: ../src/crt0.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o.ok ${OBJECTDIR}/_ext/1360937237/crt0.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/crt0.o.d" "${OBJECTDIR}/_ext/1360937237/crt0.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/crt0.o.d"  -o ${OBJECTDIR}/_ext/1360937237/crt0.o ../src/crt0.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/crt0.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
${OBJECTDIR}/_ext/1360937237/bsp_a.o: ../src/bsp_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp_a.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp_a.o.ok ${OBJECTDIR}/_ext/1360937237/bsp_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/bsp_a.o.d" "${OBJECTDIR}/_ext/1360937237/bsp_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/bsp_a.o.d"  -o ${OBJECTDIR}/_ext/1360937237/bsp_a.o ../src/bsp_a.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/bsp_a.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
else
${OBJECTDIR}/_ext/681344765/os_cpu_a.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681344765 
	@${RM} ${OBJECTDIR}/_ext/681344765/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/681344765/os_cpu_a.o 
	@${RM} ${OBJECTDIR}/_ext/681344765/os_cpu_a.o.ok ${OBJECTDIR}/_ext/681344765/os_cpu_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681344765/os_cpu_a.o.d" "${OBJECTDIR}/_ext/681344765/os_cpu_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/681344765/os_cpu_a.o.d"  -o ${OBJECTDIR}/_ext/681344765/os_cpu_a.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_a.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/681344765/os_cpu_a.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o: ../src/default-nmi-handler.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.ok ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d" "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d"  -o ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o ../src/default-nmi-handler.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o: ../src/p32mz2048ech144_voff_init.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.ok ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d" "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d"  -o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o ../src/p32mz2048ech144_voff_init.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o: ../src/pic32_software_reset.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.ok ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d" "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d"  -o ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o ../src/pic32_software_reset.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
${OBJECTDIR}/_ext/1360937237/crt0.o: ../src/crt0.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o.ok ${OBJECTDIR}/_ext/1360937237/crt0.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/crt0.o.d" "${OBJECTDIR}/_ext/1360937237/crt0.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/crt0.o.d"  -o ${OBJECTDIR}/_ext/1360937237/crt0.o ../src/crt0.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/crt0.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
${OBJECTDIR}/_ext/1360937237/bsp_a.o: ../src/bsp_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp_a.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp_a.o.ok ${OBJECTDIR}/_ext/1360937237/bsp_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/bsp_a.o.d" "${OBJECTDIR}/_ext/1360937237/bsp_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/bsp_a.o.d"  -o ${OBJECTDIR}/_ext/1360937237/bsp_a.o ../src/bsp_a.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/bsp_a.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1872009673/cpu_c.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1872009673 
	@${RM} ${OBJECTDIR}/_ext/1872009673/cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1872009673/cpu_c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1872009673/cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1872009673/cpu_c.o.d" -o ${OBJECTDIR}/_ext/1872009673/cpu_c.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_c.c   
	
${OBJECTDIR}/_ext/400789967/cpu_core.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/cpu_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/400789967 
	@${RM} ${OBJECTDIR}/_ext/400789967/cpu_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/400789967/cpu_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/400789967/cpu_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/400789967/cpu_core.o.d" -o ${OBJECTDIR}/_ext/400789967/cpu_core.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/cpu_core.c   
	
${OBJECTDIR}/_ext/681344765/os_cpu_c.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681344765 
	@${RM} ${OBJECTDIR}/_ext/681344765/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/681344765/os_cpu_c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681344765/os_cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/681344765/os_cpu_c.o.d" -o ${OBJECTDIR}/_ext/681344765/os_cpu_c.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_c.c   
	
${OBJECTDIR}/_ext/773801292/os_cfg_app.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_cfg_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_cfg_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_cfg_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_cfg_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_cfg_app.o.d" -o ${OBJECTDIR}/_ext/773801292/os_cfg_app.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_cfg_app.c   
	
${OBJECTDIR}/_ext/773801292/os_core.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_core.o.d" -o ${OBJECTDIR}/_ext/773801292/os_core.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_core.c   
	
${OBJECTDIR}/_ext/773801292/os_dbg.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_dbg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_dbg.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_dbg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_dbg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_dbg.o.d" -o ${OBJECTDIR}/_ext/773801292/os_dbg.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_dbg.c   
	
${OBJECTDIR}/_ext/773801292/os_flag.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_flag.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_flag.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_flag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_flag.o.d" -o ${OBJECTDIR}/_ext/773801292/os_flag.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_flag.c   
	
${OBJECTDIR}/_ext/773801292/os_int.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_int.o.d" -o ${OBJECTDIR}/_ext/773801292/os_int.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_int.c   
	
${OBJECTDIR}/_ext/773801292/os_mem.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_mem.o.d" -o ${OBJECTDIR}/_ext/773801292/os_mem.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mem.c   
	
${OBJECTDIR}/_ext/773801292/os_msg.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_msg.o.d" -o ${OBJECTDIR}/_ext/773801292/os_msg.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_msg.c   
	
${OBJECTDIR}/_ext/773801292/os_mutex.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_mutex.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_mutex.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_mutex.o.d" -o ${OBJECTDIR}/_ext/773801292/os_mutex.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mutex.c   
	
${OBJECTDIR}/_ext/773801292/os_pend_multi.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_pend_multi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_pend_multi.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_pend_multi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_pend_multi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_pend_multi.o.d" -o ${OBJECTDIR}/_ext/773801292/os_pend_multi.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_pend_multi.c   
	
${OBJECTDIR}/_ext/773801292/os_prio.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_prio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_prio.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_prio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_prio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_prio.o.d" -o ${OBJECTDIR}/_ext/773801292/os_prio.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_prio.c   
	
${OBJECTDIR}/_ext/773801292/os_q.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_q.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_q.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_q.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_q.o.d" -o ${OBJECTDIR}/_ext/773801292/os_q.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_q.c   
	
${OBJECTDIR}/_ext/773801292/os_sem.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_sem.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_sem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_sem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_sem.o.d" -o ${OBJECTDIR}/_ext/773801292/os_sem.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_sem.c   
	
${OBJECTDIR}/_ext/773801292/os_stat.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_stat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_stat.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_stat.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_stat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_stat.o.d" -o ${OBJECTDIR}/_ext/773801292/os_stat.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_stat.c   
	
${OBJECTDIR}/_ext/773801292/os_task.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_task.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_task.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_task.o.d" -o ${OBJECTDIR}/_ext/773801292/os_task.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_task.c   
	
${OBJECTDIR}/_ext/773801292/os_tick.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_tick.o.d" -o ${OBJECTDIR}/_ext/773801292/os_tick.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tick.c   
	
${OBJECTDIR}/_ext/773801292/os_time.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_time.o.d" -o ${OBJECTDIR}/_ext/773801292/os_time.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_time.c   
	
${OBJECTDIR}/_ext/773801292/os_tmr.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_tmr.o.d" -o ${OBJECTDIR}/_ext/773801292/os_tmr.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tmr.c   
	
${OBJECTDIR}/_ext/773801292/os_var.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_var.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_var.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_var.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_var.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_var.o.d" -o ${OBJECTDIR}/_ext/773801292/os_var.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_var.c   
	
${OBJECTDIR}/_ext/400781554/lib_ascii.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/400781554 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/400781554/lib_ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/400781554/lib_ascii.o.d" -o ${OBJECTDIR}/_ext/400781554/lib_ascii.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_ascii.c   
	
${OBJECTDIR}/_ext/400781554/lib_math.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_math.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/400781554 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_math.o.d 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_math.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/400781554/lib_math.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/400781554/lib_math.o.d" -o ${OBJECTDIR}/_ext/400781554/lib_math.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_math.c   
	
${OBJECTDIR}/_ext/400781554/lib_mem.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/400781554 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/400781554/lib_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/400781554/lib_mem.o.d" -o ${OBJECTDIR}/_ext/400781554/lib_mem.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_mem.c   
	
${OBJECTDIR}/_ext/400781554/lib_str.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_str.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/400781554 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_str.o.d 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_str.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/400781554/lib_str.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/400781554/lib_str.o.d" -o ${OBJECTDIR}/_ext/400781554/lib_str.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_str.c   
	
${OBJECTDIR}/_ext/1360937237/_exit.o: ../src/_exit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/_exit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/_exit.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/_exit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/_exit.o.d" -o ${OBJECTDIR}/_ext/1360937237/_exit.o ../src/_exit.c   
	
${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o: ../src/default-bootstrap-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o ../src/default-bootstrap-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o: ../src/default-general-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o ../src/default-general-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o: ../src/default-on-bootstrap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o ../src/default-on-bootstrap.c   
	
${OBJECTDIR}/_ext/1360937237/default-on-reset.o: ../src/default-on-reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-reset.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-on-reset.o ../src/default-on-reset.c   
	
${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o: ../src/defaultinterrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d" -o ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o ../src/defaultinterrupt.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/1360937237/config_words.o: ../src/config_words.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/config_words.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/config_words.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/config_words.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/config_words.o.d" -o ${OBJECTDIR}/_ext/1360937237/config_words.o ../src/config_words.c   
	
${OBJECTDIR}/_ext/1360937237/bsp.o: ../src/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/bsp.o.d" -o ${OBJECTDIR}/_ext/1360937237/bsp.o ../src/bsp.c   
	
else
${OBJECTDIR}/_ext/1872009673/cpu_c.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1872009673 
	@${RM} ${OBJECTDIR}/_ext/1872009673/cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1872009673/cpu_c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1872009673/cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1872009673/cpu_c.o.d" -o ${OBJECTDIR}/_ext/1872009673/cpu_c.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC/cpu_c.c   
	
${OBJECTDIR}/_ext/400789967/cpu_core.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/cpu_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/400789967 
	@${RM} ${OBJECTDIR}/_ext/400789967/cpu_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/400789967/cpu_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/400789967/cpu_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/400789967/cpu_core.o.d" -o ${OBJECTDIR}/_ext/400789967/cpu_core.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/cpu_core.c   
	
${OBJECTDIR}/_ext/681344765/os_cpu_c.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681344765 
	@${RM} ${OBJECTDIR}/_ext/681344765/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/681344765/os_cpu_c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681344765/os_cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/681344765/os_cpu_c.o.d" -o ${OBJECTDIR}/_ext/681344765/os_cpu_c.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC/os_cpu_c.c   
	
${OBJECTDIR}/_ext/773801292/os_cfg_app.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_cfg_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_cfg_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_cfg_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_cfg_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_cfg_app.o.d" -o ${OBJECTDIR}/_ext/773801292/os_cfg_app.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_cfg_app.c   
	
${OBJECTDIR}/_ext/773801292/os_core.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_core.o.d" -o ${OBJECTDIR}/_ext/773801292/os_core.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_core.c   
	
${OBJECTDIR}/_ext/773801292/os_dbg.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_dbg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_dbg.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_dbg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_dbg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_dbg.o.d" -o ${OBJECTDIR}/_ext/773801292/os_dbg.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_dbg.c   
	
${OBJECTDIR}/_ext/773801292/os_flag.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_flag.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_flag.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_flag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_flag.o.d" -o ${OBJECTDIR}/_ext/773801292/os_flag.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_flag.c   
	
${OBJECTDIR}/_ext/773801292/os_int.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_int.o.d" -o ${OBJECTDIR}/_ext/773801292/os_int.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_int.c   
	
${OBJECTDIR}/_ext/773801292/os_mem.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_mem.o.d" -o ${OBJECTDIR}/_ext/773801292/os_mem.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mem.c   
	
${OBJECTDIR}/_ext/773801292/os_msg.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_msg.o.d" -o ${OBJECTDIR}/_ext/773801292/os_msg.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_msg.c   
	
${OBJECTDIR}/_ext/773801292/os_mutex.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_mutex.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_mutex.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_mutex.o.d" -o ${OBJECTDIR}/_ext/773801292/os_mutex.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_mutex.c   
	
${OBJECTDIR}/_ext/773801292/os_pend_multi.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_pend_multi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_pend_multi.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_pend_multi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_pend_multi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_pend_multi.o.d" -o ${OBJECTDIR}/_ext/773801292/os_pend_multi.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_pend_multi.c   
	
${OBJECTDIR}/_ext/773801292/os_prio.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_prio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_prio.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_prio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_prio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_prio.o.d" -o ${OBJECTDIR}/_ext/773801292/os_prio.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_prio.c   
	
${OBJECTDIR}/_ext/773801292/os_q.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_q.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_q.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_q.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_q.o.d" -o ${OBJECTDIR}/_ext/773801292/os_q.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_q.c   
	
${OBJECTDIR}/_ext/773801292/os_sem.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_sem.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_sem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_sem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_sem.o.d" -o ${OBJECTDIR}/_ext/773801292/os_sem.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_sem.c   
	
${OBJECTDIR}/_ext/773801292/os_stat.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_stat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_stat.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_stat.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_stat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_stat.o.d" -o ${OBJECTDIR}/_ext/773801292/os_stat.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_stat.c   
	
${OBJECTDIR}/_ext/773801292/os_task.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_task.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_task.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_task.o.d" -o ${OBJECTDIR}/_ext/773801292/os_task.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_task.c   
	
${OBJECTDIR}/_ext/773801292/os_tick.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_tick.o.d" -o ${OBJECTDIR}/_ext/773801292/os_tick.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tick.c   
	
${OBJECTDIR}/_ext/773801292/os_time.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_time.o.d" -o ${OBJECTDIR}/_ext/773801292/os_time.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_time.c   
	
${OBJECTDIR}/_ext/773801292/os_tmr.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_tmr.o.d" -o ${OBJECTDIR}/_ext/773801292/os_tmr.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_tmr.c   
	
${OBJECTDIR}/_ext/773801292/os_var.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_var.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/773801292 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_var.o.d 
	@${RM} ${OBJECTDIR}/_ext/773801292/os_var.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/773801292/os_var.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/773801292/os_var.o.d" -o ${OBJECTDIR}/_ext/773801292/os_var.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source/os_var.c   
	
${OBJECTDIR}/_ext/400781554/lib_ascii.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/400781554 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/400781554/lib_ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/400781554/lib_ascii.o.d" -o ${OBJECTDIR}/_ext/400781554/lib_ascii.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_ascii.c   
	
${OBJECTDIR}/_ext/400781554/lib_math.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_math.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/400781554 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_math.o.d 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_math.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/400781554/lib_math.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/400781554/lib_math.o.d" -o ${OBJECTDIR}/_ext/400781554/lib_math.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_math.c   
	
${OBJECTDIR}/_ext/400781554/lib_mem.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/400781554 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/400781554/lib_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/400781554/lib_mem.o.d" -o ${OBJECTDIR}/_ext/400781554/lib_mem.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_mem.c   
	
${OBJECTDIR}/_ext/400781554/lib_str.o: ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_str.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/400781554 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_str.o.d 
	@${RM} ${OBJECTDIR}/_ext/400781554/lib_str.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/400781554/lib_str.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/400781554/lib_str.o.d" -o ${OBJECTDIR}/_ext/400781554/lib_str.o ../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB/lib_str.c   
	
${OBJECTDIR}/_ext/1360937237/_exit.o: ../src/_exit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/_exit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/_exit.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/_exit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/_exit.o.d" -o ${OBJECTDIR}/_ext/1360937237/_exit.o ../src/_exit.c   
	
${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o: ../src/default-bootstrap-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o ../src/default-bootstrap-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o: ../src/default-general-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o ../src/default-general-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o: ../src/default-on-bootstrap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o ../src/default-on-bootstrap.c   
	
${OBJECTDIR}/_ext/1360937237/default-on-reset.o: ../src/default-on-reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-reset.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-on-reset.o ../src/default-on-reset.c   
	
${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o: ../src/defaultinterrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d" -o ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o ../src/defaultinterrupt.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/1360937237/config_words.o: ../src/config_words.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/config_words.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/config_words.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/config_words.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/config_words.o.d" -o ${OBJECTDIR}/_ext/1360937237/config_words.o ../src/config_words.c   
	
${OBJECTDIR}/_ext/1360937237/bsp.o: ../src/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../framework" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Source" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uCOS_III/Ports/MIPS32_M14KEc/ExternalInterruptController/MPLABX_XC32_GCC" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_LIB" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU" -I"../../../../../third_party/rtos/Micrium/MicriumOSIII/Software/uC_CPU/MIPS32_14KEc/MPLABX_XC32_GCC" -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/bsp.o.d" -o ${OBJECTDIR}/_ext/1360937237/bsp.o ../src/bsp.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/uC_OS_III_Basic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/p32MZ2048ECH144.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -nostartfiles -o dist/${CND_CONF}/${IMAGE_TYPE}/uC_OS_III_Basic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x27F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=4000,--defsym=_min_stack_size=2000,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/uC_OS_III_Basic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/p32MZ2048ECH144.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -nostartfiles -o dist/${CND_CONF}/${IMAGE_TYPE}/uC_OS_III_Basic.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4000,--defsym=_min_stack_size=2000,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/uC_OS_III_Basic.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
