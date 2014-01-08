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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/combined_gfx_usb_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/combined_gfx_usb_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/default-bootstrap-exception-handler.c ../src/default-cache-err-exception-handler.c ../src/default-general-exception-handler.c ../src/default-gettimeofday.S ../src/default-nmi-handler.S ../src/default-on-bootstrap.c ../src/default-on-reset.c ../src/default-simple-tlb-refill-exception-handler.c ../src/defaultinterrupt.c ../src/general-exception.S ../src/p32mz2048ech144_div.S ../src/p32mz2048ech144_voff_init.S ../src/pic32_init_cache.S ../src/pic32_init_tlb_ebi_sqi.S ../src/pic32_software_reset.S ../src/simple-tlb-refill-exception.S ../src/software-debug-break.c ../src/crt0.S ../src/main.c ../src/app_USBDeviceEventCallback.c ../src/app_init.c ../src/app_tasks.c ../src/bsp.c ../src/system_config.c ../src/system_init.c ../src/system_int.c ../src/app_keyboard.c ../src/system_tasks.c ../src/app_RTOSHooks.c ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port.c ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port_asm.S ../../../../../third_party/rtos/FreeRTOS/Source/croutine.c ../../../../../third_party/rtos/FreeRTOS/Source/list.c ../../../../../third_party/rtos/FreeRTOS/Source/queue.c ../../../../../third_party/rtos/FreeRTOS/Source/tasks.c ../../../../../third_party/rtos/FreeRTOS/Source/timers.c ../../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_3.c ../../../../../framework/driver/gfx/gfx_lcc/src/drv_gfx_lcc.c ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb.c ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb_device.c ../../../../../framework/gfx/src/gfx_primitive.c ../../../../../framework/osal/osal.c ../../../../../framework/peripheral/int/src/plib_int_pic32.c ../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../framework/usb/src/dynamic/usb_device_hid.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o ${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o ${OBJECTDIR}/_ext/1360937237/default-on-reset.o ${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o ${OBJECTDIR}/_ext/1360937237/general-exception.o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o ${OBJECTDIR}/_ext/1360937237/software-debug-break.o ${OBJECTDIR}/_ext/1360937237/crt0.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o ${OBJECTDIR}/_ext/1360937237/app_init.o ${OBJECTDIR}/_ext/1360937237/app_tasks.o ${OBJECTDIR}/_ext/1360937237/bsp.o ${OBJECTDIR}/_ext/1360937237/system_config.o ${OBJECTDIR}/_ext/1360937237/system_init.o ${OBJECTDIR}/_ext/1360937237/system_int.o ${OBJECTDIR}/_ext/1360937237/app_keyboard.o ${OBJECTDIR}/_ext/1360937237/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o ${OBJECTDIR}/_ext/1282498061/port.o ${OBJECTDIR}/_ext/1282498061/port_asm.o ${OBJECTDIR}/_ext/373060831/croutine.o ${OBJECTDIR}/_ext/373060831/list.o ${OBJECTDIR}/_ext/373060831/queue.o ${OBJECTDIR}/_ext/373060831/tasks.o ${OBJECTDIR}/_ext/373060831/timers.o ${OBJECTDIR}/_ext/1107379230/heap_3.o ${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o ${OBJECTDIR}/_ext/179651966/drv_usb.o ${OBJECTDIR}/_ext/179651966/drv_usb_device.o ${OBJECTDIR}/_ext/1127269358/gfx_primitive.o ${OBJECTDIR}/_ext/1223714961/osal.o ${OBJECTDIR}/_ext/198928529/plib_int_pic32.o ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o ${OBJECTDIR}/_ext/2136608937/usb_device.o ${OBJECTDIR}/_ext/2136608937/usb_device_hid.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d ${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o.d ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.d ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d ${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d ${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o.d ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d ${OBJECTDIR}/_ext/1360937237/general-exception.o.d ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.d ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.d ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.d ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.d ${OBJECTDIR}/_ext/1360937237/software-debug-break.o.d ${OBJECTDIR}/_ext/1360937237/crt0.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o.d ${OBJECTDIR}/_ext/1360937237/app_init.o.d ${OBJECTDIR}/_ext/1360937237/app_tasks.o.d ${OBJECTDIR}/_ext/1360937237/bsp.o.d ${OBJECTDIR}/_ext/1360937237/system_config.o.d ${OBJECTDIR}/_ext/1360937237/system_init.o.d ${OBJECTDIR}/_ext/1360937237/system_int.o.d ${OBJECTDIR}/_ext/1360937237/app_keyboard.o.d ${OBJECTDIR}/_ext/1360937237/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o.d ${OBJECTDIR}/_ext/1282498061/port.o.d ${OBJECTDIR}/_ext/1282498061/port_asm.o.d ${OBJECTDIR}/_ext/373060831/croutine.o.d ${OBJECTDIR}/_ext/373060831/list.o.d ${OBJECTDIR}/_ext/373060831/queue.o.d ${OBJECTDIR}/_ext/373060831/tasks.o.d ${OBJECTDIR}/_ext/373060831/timers.o.d ${OBJECTDIR}/_ext/1107379230/heap_3.o.d ${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o.d ${OBJECTDIR}/_ext/179651966/drv_usb.o.d ${OBJECTDIR}/_ext/179651966/drv_usb_device.o.d ${OBJECTDIR}/_ext/1127269358/gfx_primitive.o.d ${OBJECTDIR}/_ext/1223714961/osal.o.d ${OBJECTDIR}/_ext/198928529/plib_int_pic32.o.d ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d ${OBJECTDIR}/_ext/2136608937/usb_device.o.d ${OBJECTDIR}/_ext/2136608937/usb_device_hid.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o ${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o ${OBJECTDIR}/_ext/1360937237/default-on-reset.o ${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o ${OBJECTDIR}/_ext/1360937237/general-exception.o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o ${OBJECTDIR}/_ext/1360937237/software-debug-break.o ${OBJECTDIR}/_ext/1360937237/crt0.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o ${OBJECTDIR}/_ext/1360937237/app_init.o ${OBJECTDIR}/_ext/1360937237/app_tasks.o ${OBJECTDIR}/_ext/1360937237/bsp.o ${OBJECTDIR}/_ext/1360937237/system_config.o ${OBJECTDIR}/_ext/1360937237/system_init.o ${OBJECTDIR}/_ext/1360937237/system_int.o ${OBJECTDIR}/_ext/1360937237/app_keyboard.o ${OBJECTDIR}/_ext/1360937237/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o ${OBJECTDIR}/_ext/1282498061/port.o ${OBJECTDIR}/_ext/1282498061/port_asm.o ${OBJECTDIR}/_ext/373060831/croutine.o ${OBJECTDIR}/_ext/373060831/list.o ${OBJECTDIR}/_ext/373060831/queue.o ${OBJECTDIR}/_ext/373060831/tasks.o ${OBJECTDIR}/_ext/373060831/timers.o ${OBJECTDIR}/_ext/1107379230/heap_3.o ${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o ${OBJECTDIR}/_ext/179651966/drv_usb.o ${OBJECTDIR}/_ext/179651966/drv_usb_device.o ${OBJECTDIR}/_ext/1127269358/gfx_primitive.o ${OBJECTDIR}/_ext/1223714961/osal.o ${OBJECTDIR}/_ext/198928529/plib_int_pic32.o ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o ${OBJECTDIR}/_ext/2136608937/usb_device.o ${OBJECTDIR}/_ext/2136608937/usb_device_hid.o

# Source Files
SOURCEFILES=../src/default-bootstrap-exception-handler.c ../src/default-cache-err-exception-handler.c ../src/default-general-exception-handler.c ../src/default-gettimeofday.S ../src/default-nmi-handler.S ../src/default-on-bootstrap.c ../src/default-on-reset.c ../src/default-simple-tlb-refill-exception-handler.c ../src/defaultinterrupt.c ../src/general-exception.S ../src/p32mz2048ech144_div.S ../src/p32mz2048ech144_voff_init.S ../src/pic32_init_cache.S ../src/pic32_init_tlb_ebi_sqi.S ../src/pic32_software_reset.S ../src/simple-tlb-refill-exception.S ../src/software-debug-break.c ../src/crt0.S ../src/main.c ../src/app_USBDeviceEventCallback.c ../src/app_init.c ../src/app_tasks.c ../src/bsp.c ../src/system_config.c ../src/system_init.c ../src/system_int.c ../src/app_keyboard.c ../src/system_tasks.c ../src/app_RTOSHooks.c ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port.c ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port_asm.S ../../../../../third_party/rtos/FreeRTOS/Source/croutine.c ../../../../../third_party/rtos/FreeRTOS/Source/list.c ../../../../../third_party/rtos/FreeRTOS/Source/queue.c ../../../../../third_party/rtos/FreeRTOS/Source/tasks.c ../../../../../third_party/rtos/FreeRTOS/Source/timers.c ../../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_3.c ../../../../../framework/driver/gfx/gfx_lcc/src/drv_gfx_lcc.c ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb.c ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb_device.c ../../../../../framework/gfx/src/gfx_primitive.c ../../../../../framework/osal/osal.c ../../../../../framework/peripheral/int/src/plib_int_pic32.c ../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../framework/usb/src/dynamic/usb_device_hid.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/combined_gfx_usb_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2048ECH144
MP_LINKER_FILE_OPTION=,--script="..\src\p32MZ2048ECH144.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o: ../src/default-gettimeofday.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.ok ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.d" "${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.d"  -o ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o ../src/default-gettimeofday.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o: ../src/default-nmi-handler.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.ok ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d" "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d"  -o ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o ../src/default-nmi-handler.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/general-exception.o: ../src/general-exception.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/general-exception.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/general-exception.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/general-exception.o.ok ${OBJECTDIR}/_ext/1360937237/general-exception.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/general-exception.o.d" "${OBJECTDIR}/_ext/1360937237/general-exception.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/general-exception.o.d"  -o ${OBJECTDIR}/_ext/1360937237/general-exception.o ../src/general-exception.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/general-exception.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o: ../src/p32mz2048ech144_div.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.ok ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.d" "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.d"  -o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o ../src/p32mz2048ech144_div.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o: ../src/p32mz2048ech144_voff_init.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.ok ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d" "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d"  -o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o ../src/p32mz2048ech144_voff_init.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o: ../src/pic32_init_cache.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.ok ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.d" "${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.d"  -o ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o ../src/pic32_init_cache.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o: ../src/pic32_init_tlb_ebi_sqi.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.ok ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.d" "${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.d"  -o ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o ../src/pic32_init_tlb_ebi_sqi.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o: ../src/pic32_software_reset.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.ok ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d" "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d"  -o ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o ../src/pic32_software_reset.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o: ../src/simple-tlb-refill-exception.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.ok ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.d" "${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.d"  -o ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o ../src/simple-tlb-refill-exception.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/crt0.o: ../src/crt0.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o.ok ${OBJECTDIR}/_ext/1360937237/crt0.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/crt0.o.d" "${OBJECTDIR}/_ext/1360937237/crt0.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/crt0.o.d"  -o ${OBJECTDIR}/_ext/1360937237/crt0.o ../src/crt0.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/crt0.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1282498061/port_asm.o: ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1282498061 
	@${RM} ${OBJECTDIR}/_ext/1282498061/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1282498061/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1282498061/port_asm.o.ok ${OBJECTDIR}/_ext/1282498061/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1282498061/port_asm.o.d" "${OBJECTDIR}/_ext/1282498061/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1282498061/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1282498061/port_asm.o ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1282498061/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
else
${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o: ../src/default-gettimeofday.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.ok ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.d" "${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.d"  -o ${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o ../src/default-gettimeofday.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/default-gettimeofday.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o: ../src/default-nmi-handler.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.ok ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d" "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.d"  -o ${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o ../src/default-nmi-handler.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/default-nmi-handler.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/general-exception.o: ../src/general-exception.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/general-exception.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/general-exception.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/general-exception.o.ok ${OBJECTDIR}/_ext/1360937237/general-exception.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/general-exception.o.d" "${OBJECTDIR}/_ext/1360937237/general-exception.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/general-exception.o.d"  -o ${OBJECTDIR}/_ext/1360937237/general-exception.o ../src/general-exception.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/general-exception.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o: ../src/p32mz2048ech144_div.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.ok ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.d" "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.d"  -o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o ../src/p32mz2048ech144_div.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_div.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o: ../src/p32mz2048ech144_voff_init.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.ok ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d" "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.d"  -o ${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o ../src/p32mz2048ech144_voff_init.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/p32mz2048ech144_voff_init.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o: ../src/pic32_init_cache.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.ok ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.d" "${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.d"  -o ${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o ../src/pic32_init_cache.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/pic32_init_cache.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o: ../src/pic32_init_tlb_ebi_sqi.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.ok ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.d" "${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.d"  -o ${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o ../src/pic32_init_tlb_ebi_sqi.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/pic32_init_tlb_ebi_sqi.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o: ../src/pic32_software_reset.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.ok ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d" "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.d"  -o ${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o ../src/pic32_software_reset.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/pic32_software_reset.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o: ../src/simple-tlb-refill-exception.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.ok ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.d" "${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.d"  -o ${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o ../src/simple-tlb-refill-exception.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/simple-tlb-refill-exception.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1360937237/crt0.o: ../src/crt0.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crt0.o.ok ${OBJECTDIR}/_ext/1360937237/crt0.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/crt0.o.d" "${OBJECTDIR}/_ext/1360937237/crt0.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/crt0.o.d"  -o ${OBJECTDIR}/_ext/1360937237/crt0.o ../src/crt0.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/crt0.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
${OBJECTDIR}/_ext/1282498061/port_asm.o: ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1282498061 
	@${RM} ${OBJECTDIR}/_ext/1282498061/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1282498061/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/1282498061/port_asm.o.ok ${OBJECTDIR}/_ext/1282498061/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1282498061/port_asm.o.d" "${OBJECTDIR}/_ext/1282498061/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -DPIC32MZ -DINIT_MMU_MZ_FIXED -DINIT_SSX -DINIT_L1_CACHE -DINIT_DSPR2 -DPIC32_SRS_SET_COUNT=8 -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1282498061/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1282498061/port_asm.o ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1282498061/port_asm.o.asm.d",--gdwarf-2,-I"../src",-I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o: ../src/default-bootstrap-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o ../src/default-bootstrap-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o: ../src/default-cache-err-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o ../src/default-cache-err-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o: ../src/default-general-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o ../src/default-general-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o: ../src/default-on-bootstrap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o ../src/default-on-bootstrap.c   
	
${OBJECTDIR}/_ext/1360937237/default-on-reset.o: ../src/default-on-reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-reset.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-on-reset.o ../src/default-on-reset.c   
	
${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o: ../src/default-simple-tlb-refill-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o ../src/default-simple-tlb-refill-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o: ../src/defaultinterrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d" -o ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o ../src/defaultinterrupt.c   
	
${OBJECTDIR}/_ext/1360937237/software-debug-break.o: ../src/software-debug-break.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/software-debug-break.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/software-debug-break.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/software-debug-break.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/software-debug-break.o.d" -o ${OBJECTDIR}/_ext/1360937237/software-debug-break.o ../src/software-debug-break.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o: ../src/app_USBDeviceEventCallback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o ../src/app_USBDeviceEventCallback.c   
	
${OBJECTDIR}/_ext/1360937237/app_init.o: ../src/app_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_init.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_init.o ../src/app_init.c   
	
${OBJECTDIR}/_ext/1360937237/app_tasks.o: ../src/app_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_tasks.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_tasks.o ../src/app_tasks.c   
	
${OBJECTDIR}/_ext/1360937237/bsp.o: ../src/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/bsp.o.d" -o ${OBJECTDIR}/_ext/1360937237/bsp.o ../src/bsp.c   
	
${OBJECTDIR}/_ext/1360937237/system_config.o: ../src/system_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/system_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_config.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_config.o ../src/system_config.c   
	
${OBJECTDIR}/_ext/1360937237/system_init.o: ../src/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_init.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_init.o ../src/system_init.c   
	
${OBJECTDIR}/_ext/1360937237/system_int.o: ../src/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_int.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_int.o ../src/system_int.c   
	
${OBJECTDIR}/_ext/1360937237/app_keyboard.o: ../src/app_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_keyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app_keyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_keyboard.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_keyboard.o ../src/app_keyboard.c   
	
${OBJECTDIR}/_ext/1360937237/system_tasks.o: ../src/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_tasks.o ../src/system_tasks.c   
	
${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o: ../src/app_RTOSHooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o ../src/app_RTOSHooks.c   
	
${OBJECTDIR}/_ext/1282498061/port.o: ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1282498061 
	@${RM} ${OBJECTDIR}/_ext/1282498061/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1282498061/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1282498061/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1282498061/port.o.d" -o ${OBJECTDIR}/_ext/1282498061/port.o ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port.c   
	
${OBJECTDIR}/_ext/373060831/croutine.o: ../../../../../third_party/rtos/FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/373060831 
	@${RM} ${OBJECTDIR}/_ext/373060831/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/373060831/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/373060831/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/373060831/croutine.o.d" -o ${OBJECTDIR}/_ext/373060831/croutine.o ../../../../../third_party/rtos/FreeRTOS/Source/croutine.c   
	
${OBJECTDIR}/_ext/373060831/list.o: ../../../../../third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/373060831 
	@${RM} ${OBJECTDIR}/_ext/373060831/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/373060831/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/373060831/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/373060831/list.o.d" -o ${OBJECTDIR}/_ext/373060831/list.o ../../../../../third_party/rtos/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/373060831/queue.o: ../../../../../third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/373060831 
	@${RM} ${OBJECTDIR}/_ext/373060831/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/373060831/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/373060831/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/373060831/queue.o.d" -o ${OBJECTDIR}/_ext/373060831/queue.o ../../../../../third_party/rtos/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/373060831/tasks.o: ../../../../../third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/373060831 
	@${RM} ${OBJECTDIR}/_ext/373060831/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/373060831/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/373060831/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/373060831/tasks.o.d" -o ${OBJECTDIR}/_ext/373060831/tasks.o ../../../../../third_party/rtos/FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/_ext/373060831/timers.o: ../../../../../third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/373060831 
	@${RM} ${OBJECTDIR}/_ext/373060831/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/373060831/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/373060831/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/373060831/timers.o.d" -o ${OBJECTDIR}/_ext/373060831/timers.o ../../../../../third_party/rtos/FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/_ext/1107379230/heap_3.o: ../../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1107379230 
	@${RM} ${OBJECTDIR}/_ext/1107379230/heap_3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1107379230/heap_3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1107379230/heap_3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1107379230/heap_3.o.d" -o ${OBJECTDIR}/_ext/1107379230/heap_3.o ../../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_3.c   
	
${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o: ../../../../../framework/driver/gfx/gfx_lcc/src/drv_gfx_lcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1483060542 
	@${RM} ${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o.d" -o ${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o ../../../../../framework/driver/gfx/gfx_lcc/src/drv_gfx_lcc.c   
	
${OBJECTDIR}/_ext/179651966/drv_usb.o: ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/179651966 
	@${RM} ${OBJECTDIR}/_ext/179651966/drv_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/179651966/drv_usb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/179651966/drv_usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/179651966/drv_usb.o.d" -o ${OBJECTDIR}/_ext/179651966/drv_usb.o ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb.c   
	
${OBJECTDIR}/_ext/179651966/drv_usb_device.o: ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/179651966 
	@${RM} ${OBJECTDIR}/_ext/179651966/drv_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/179651966/drv_usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/179651966/drv_usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/179651966/drv_usb_device.o.d" -o ${OBJECTDIR}/_ext/179651966/drv_usb_device.o ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb_device.c   
	
${OBJECTDIR}/_ext/1127269358/gfx_primitive.o: ../../../../../framework/gfx/src/gfx_primitive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1127269358 
	@${RM} ${OBJECTDIR}/_ext/1127269358/gfx_primitive.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127269358/gfx_primitive.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127269358/gfx_primitive.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1127269358/gfx_primitive.o.d" -o ${OBJECTDIR}/_ext/1127269358/gfx_primitive.o ../../../../../framework/gfx/src/gfx_primitive.c   
	
${OBJECTDIR}/_ext/1223714961/osal.o: ../../../../../framework/osal/osal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1223714961 
	@${RM} ${OBJECTDIR}/_ext/1223714961/osal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1223714961/osal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1223714961/osal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1223714961/osal.o.d" -o ${OBJECTDIR}/_ext/1223714961/osal.o ../../../../../framework/osal/osal.c   
	
${OBJECTDIR}/_ext/198928529/plib_int_pic32.o: ../../../../../framework/peripheral/int/src/plib_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/198928529 
	@${RM} ${OBJECTDIR}/_ext/198928529/plib_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/198928529/plib_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/198928529/plib_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/198928529/plib_int_pic32.o.d" -o ${OBJECTDIR}/_ext/198928529/plib_int_pic32.o ../../../../../framework/peripheral/int/src/plib_int_pic32.c   
	
${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o: ../../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1042686532 
	@${RM} ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o ../../../../../framework/system/int/src/sys_int_pic32.c   
	
${OBJECTDIR}/_ext/2136608937/usb_device.o: ../../../../../framework/usb/src/dynamic/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2136608937 
	@${RM} ${OBJECTDIR}/_ext/2136608937/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/2136608937/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2136608937/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/2136608937/usb_device.o.d" -o ${OBJECTDIR}/_ext/2136608937/usb_device.o ../../../../../framework/usb/src/dynamic/usb_device.c   
	
${OBJECTDIR}/_ext/2136608937/usb_device_hid.o: ../../../../../framework/usb/src/dynamic/usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2136608937 
	@${RM} ${OBJECTDIR}/_ext/2136608937/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/2136608937/usb_device_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2136608937/usb_device_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/2136608937/usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/2136608937/usb_device_hid.o ../../../../../framework/usb/src/dynamic/usb_device_hid.c   
	
else
${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o: ../src/default-bootstrap-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-bootstrap-exception-handler.o ../src/default-bootstrap-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o: ../src/default-cache-err-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-cache-err-exception-handler.o ../src/default-cache-err-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o: ../src/default-general-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-general-exception-handler.o ../src/default-general-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o: ../src/default-on-bootstrap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-on-bootstrap.o ../src/default-on-bootstrap.c   
	
${OBJECTDIR}/_ext/1360937237/default-on-reset.o: ../src/default-on-reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-on-reset.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-on-reset.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-on-reset.o ../src/default-on-reset.c   
	
${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o: ../src/default-simple-tlb-refill-exception-handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/default-simple-tlb-refill-exception-handler.o ../src/default-simple-tlb-refill-exception-handler.c   
	
${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o: ../src/defaultinterrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o.d" -o ${OBJECTDIR}/_ext/1360937237/defaultinterrupt.o ../src/defaultinterrupt.c   
	
${OBJECTDIR}/_ext/1360937237/software-debug-break.o: ../src/software-debug-break.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/software-debug-break.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/software-debug-break.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/software-debug-break.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/software-debug-break.o.d" -o ${OBJECTDIR}/_ext/1360937237/software-debug-break.o ../src/software-debug-break.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o: ../src/app_USBDeviceEventCallback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_USBDeviceEventCallback.o ../src/app_USBDeviceEventCallback.c   
	
${OBJECTDIR}/_ext/1360937237/app_init.o: ../src/app_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_init.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_init.o ../src/app_init.c   
	
${OBJECTDIR}/_ext/1360937237/app_tasks.o: ../src/app_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_tasks.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_tasks.o ../src/app_tasks.c   
	
${OBJECTDIR}/_ext/1360937237/bsp.o: ../src/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/bsp.o.d" -o ${OBJECTDIR}/_ext/1360937237/bsp.o ../src/bsp.c   
	
${OBJECTDIR}/_ext/1360937237/system_config.o: ../src/system_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/system_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_config.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_config.o ../src/system_config.c   
	
${OBJECTDIR}/_ext/1360937237/system_init.o: ../src/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_init.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_init.o ../src/system_init.c   
	
${OBJECTDIR}/_ext/1360937237/system_int.o: ../src/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_int.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_int.o ../src/system_int.c   
	
${OBJECTDIR}/_ext/1360937237/app_keyboard.o: ../src/app_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_keyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app_keyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_keyboard.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_keyboard.o ../src/app_keyboard.c   
	
${OBJECTDIR}/_ext/1360937237/system_tasks.o: ../src/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_tasks.o ../src/system_tasks.c   
	
${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o: ../src/app_RTOSHooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o.d" -o ${OBJECTDIR}/_ext/1360937237/app_RTOSHooks.o ../src/app_RTOSHooks.c   
	
${OBJECTDIR}/_ext/1282498061/port.o: ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1282498061 
	@${RM} ${OBJECTDIR}/_ext/1282498061/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1282498061/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1282498061/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1282498061/port.o.d" -o ${OBJECTDIR}/_ext/1282498061/port.o ../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ/port.c   
	
${OBJECTDIR}/_ext/373060831/croutine.o: ../../../../../third_party/rtos/FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/373060831 
	@${RM} ${OBJECTDIR}/_ext/373060831/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/373060831/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/373060831/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/373060831/croutine.o.d" -o ${OBJECTDIR}/_ext/373060831/croutine.o ../../../../../third_party/rtos/FreeRTOS/Source/croutine.c   
	
${OBJECTDIR}/_ext/373060831/list.o: ../../../../../third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/373060831 
	@${RM} ${OBJECTDIR}/_ext/373060831/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/373060831/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/373060831/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/373060831/list.o.d" -o ${OBJECTDIR}/_ext/373060831/list.o ../../../../../third_party/rtos/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/373060831/queue.o: ../../../../../third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/373060831 
	@${RM} ${OBJECTDIR}/_ext/373060831/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/373060831/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/373060831/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/373060831/queue.o.d" -o ${OBJECTDIR}/_ext/373060831/queue.o ../../../../../third_party/rtos/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/373060831/tasks.o: ../../../../../third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/373060831 
	@${RM} ${OBJECTDIR}/_ext/373060831/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/373060831/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/373060831/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/373060831/tasks.o.d" -o ${OBJECTDIR}/_ext/373060831/tasks.o ../../../../../third_party/rtos/FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/_ext/373060831/timers.o: ../../../../../third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/373060831 
	@${RM} ${OBJECTDIR}/_ext/373060831/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/373060831/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/373060831/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/373060831/timers.o.d" -o ${OBJECTDIR}/_ext/373060831/timers.o ../../../../../third_party/rtos/FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/_ext/1107379230/heap_3.o: ../../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1107379230 
	@${RM} ${OBJECTDIR}/_ext/1107379230/heap_3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1107379230/heap_3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1107379230/heap_3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1107379230/heap_3.o.d" -o ${OBJECTDIR}/_ext/1107379230/heap_3.o ../../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_3.c   
	
${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o: ../../../../../framework/driver/gfx/gfx_lcc/src/drv_gfx_lcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1483060542 
	@${RM} ${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o.d" -o ${OBJECTDIR}/_ext/1483060542/drv_gfx_lcc.o ../../../../../framework/driver/gfx/gfx_lcc/src/drv_gfx_lcc.c   
	
${OBJECTDIR}/_ext/179651966/drv_usb.o: ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/179651966 
	@${RM} ${OBJECTDIR}/_ext/179651966/drv_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/179651966/drv_usb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/179651966/drv_usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/179651966/drv_usb.o.d" -o ${OBJECTDIR}/_ext/179651966/drv_usb.o ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb.c   
	
${OBJECTDIR}/_ext/179651966/drv_usb_device.o: ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/179651966 
	@${RM} ${OBJECTDIR}/_ext/179651966/drv_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/179651966/drv_usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/179651966/drv_usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/179651966/drv_usb_device.o.d" -o ${OBJECTDIR}/_ext/179651966/drv_usb_device.o ../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usb_device.c   
	
${OBJECTDIR}/_ext/1127269358/gfx_primitive.o: ../../../../../framework/gfx/src/gfx_primitive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1127269358 
	@${RM} ${OBJECTDIR}/_ext/1127269358/gfx_primitive.o.d 
	@${RM} ${OBJECTDIR}/_ext/1127269358/gfx_primitive.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1127269358/gfx_primitive.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1127269358/gfx_primitive.o.d" -o ${OBJECTDIR}/_ext/1127269358/gfx_primitive.o ../../../../../framework/gfx/src/gfx_primitive.c   
	
${OBJECTDIR}/_ext/1223714961/osal.o: ../../../../../framework/osal/osal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1223714961 
	@${RM} ${OBJECTDIR}/_ext/1223714961/osal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1223714961/osal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1223714961/osal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1223714961/osal.o.d" -o ${OBJECTDIR}/_ext/1223714961/osal.o ../../../../../framework/osal/osal.c   
	
${OBJECTDIR}/_ext/198928529/plib_int_pic32.o: ../../../../../framework/peripheral/int/src/plib_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/198928529 
	@${RM} ${OBJECTDIR}/_ext/198928529/plib_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/198928529/plib_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/198928529/plib_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/198928529/plib_int_pic32.o.d" -o ${OBJECTDIR}/_ext/198928529/plib_int_pic32.o ../../../../../framework/peripheral/int/src/plib_int_pic32.c   
	
${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o: ../../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1042686532 
	@${RM} ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o ../../../../../framework/system/int/src/sys_int_pic32.c   
	
${OBJECTDIR}/_ext/2136608937/usb_device.o: ../../../../../framework/usb/src/dynamic/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2136608937 
	@${RM} ${OBJECTDIR}/_ext/2136608937/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/2136608937/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2136608937/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/2136608937/usb_device.o.d" -o ${OBJECTDIR}/_ext/2136608937/usb_device.o ../../../../../framework/usb/src/dynamic/usb_device.c   
	
${OBJECTDIR}/_ext/2136608937/usb_device_hid.o: ../../../../../framework/usb/src/dynamic/usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2136608937 
	@${RM} ${OBJECTDIR}/_ext/2136608937/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/2136608937/usb_device_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2136608937/usb_device_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DINLINE_API="static inline" -DINLINE="static inline" -I"../../../../../framework" -I"../src" -I"../../../../../third_party/rtos/FreeRTOS/Source/include" -I"../../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MZ" -MMD -MF "${OBJECTDIR}/_ext/2136608937/usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/2136608937/usb_device_hid.o ../../../../../framework/usb/src/dynamic/usb_device_hid.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/combined_gfx_usb_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/p32MZ2048ECH144.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -nostartfiles -o dist/${CND_CONF}/${IMAGE_TYPE}/combined_gfx_usb_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x27F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=20000,--defsym=_min_stack_size=2000,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/combined_gfx_usb_FreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/p32MZ2048ECH144.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -nostartfiles -o dist/${CND_CONF}/${IMAGE_TYPE}/combined_gfx_usb_FreeRTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=20000,--defsym=_min_stack_size=2000,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/combined_gfx_usb_FreeRTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
