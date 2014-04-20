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
ifeq "$(wildcard nbproject/Makefile-local-pic32mx_usb_sk_int_dyn.mk)" "nbproject/Makefile-local-pic32mx_usb_sk_int_dyn.mk"
include nbproject/Makefile-local-pic32mx_usb_sk_int_dyn.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic32mx_usb_sk_int_dyn
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/generic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/generic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic32mx_usb_sk_int_dyn/system_config.c ../src/system_config/pic32mx_usb_sk_int_dyn/system_init.c ../src/system_config/pic32mx_usb_sk_int_dyn/system_tasks.c ../src/system_config/pic32mx_usb_sk_int_dyn/system_interrupt.c ../src/app.c ../src/main.c ../../../../../../bsp/sk_pic32_mx_usb/bsp_sys_init.c ../../../../../../bsp/sk_pic32_mx_usb/config_performance.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c ../../../../../../framework/peripheral/int/src/plib_int_pic32.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../../framework/usb/src/dynamic/usb_device_generic.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/384610239/system_config.o ${OBJECTDIR}/_ext/384610239/system_init.o ${OBJECTDIR}/_ext/384610239/system_tasks.o ${OBJECTDIR}/_ext/384610239/system_interrupt.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/117104221/bsp_sys_init.o ${OBJECTDIR}/_ext/117104221/config_performance.o ${OBJECTDIR}/_ext/1585079243/drv_usb.o ${OBJECTDIR}/_ext/1585079243/drv_usb_device.o ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/692885480/usb_device.o ${OBJECTDIR}/_ext/692885480/usb_device_generic.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/384610239/system_config.o.d ${OBJECTDIR}/_ext/384610239/system_init.o.d ${OBJECTDIR}/_ext/384610239/system_tasks.o.d ${OBJECTDIR}/_ext/384610239/system_interrupt.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/117104221/bsp_sys_init.o.d ${OBJECTDIR}/_ext/117104221/config_performance.o.d ${OBJECTDIR}/_ext/1585079243/drv_usb.o.d ${OBJECTDIR}/_ext/1585079243/drv_usb_device.o.d ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d ${OBJECTDIR}/_ext/692885480/usb_device.o.d ${OBJECTDIR}/_ext/692885480/usb_device_generic.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/384610239/system_config.o ${OBJECTDIR}/_ext/384610239/system_init.o ${OBJECTDIR}/_ext/384610239/system_tasks.o ${OBJECTDIR}/_ext/384610239/system_interrupt.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/117104221/bsp_sys_init.o ${OBJECTDIR}/_ext/117104221/config_performance.o ${OBJECTDIR}/_ext/1585079243/drv_usb.o ${OBJECTDIR}/_ext/1585079243/drv_usb_device.o ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/692885480/usb_device.o ${OBJECTDIR}/_ext/692885480/usb_device_generic.o

# Source Files
SOURCEFILES=../src/system_config/pic32mx_usb_sk_int_dyn/system_config.c ../src/system_config/pic32mx_usb_sk_int_dyn/system_init.c ../src/system_config/pic32mx_usb_sk_int_dyn/system_tasks.c ../src/system_config/pic32mx_usb_sk_int_dyn/system_interrupt.c ../src/app.c ../src/main.c ../../../../../../bsp/sk_pic32_mx_usb/bsp_sys_init.c ../../../../../../bsp/sk_pic32_mx_usb/config_performance.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c ../../../../../../framework/peripheral/int/src/plib_int_pic32.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../../framework/usb/src/dynamic/usb_device_generic.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-pic32mx_usb_sk_int_dyn.mk dist/${CND_CONF}/${IMAGE_TYPE}/generic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/384610239/system_config.o: ../src/system_config/pic32mx_usb_sk_int_dyn/system_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/384610239 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/384610239/system_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/384610239/system_config.o.d" -o ${OBJECTDIR}/_ext/384610239/system_config.o ../src/system_config/pic32mx_usb_sk_int_dyn/system_config.c   
	
${OBJECTDIR}/_ext/384610239/system_init.o: ../src/system_config/pic32mx_usb_sk_int_dyn/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/384610239 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/384610239/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/384610239/system_init.o.d" -o ${OBJECTDIR}/_ext/384610239/system_init.o ../src/system_config/pic32mx_usb_sk_int_dyn/system_init.c   
	
${OBJECTDIR}/_ext/384610239/system_tasks.o: ../src/system_config/pic32mx_usb_sk_int_dyn/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/384610239 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/384610239/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/384610239/system_tasks.o.d" -o ${OBJECTDIR}/_ext/384610239/system_tasks.o ../src/system_config/pic32mx_usb_sk_int_dyn/system_tasks.c   
	
${OBJECTDIR}/_ext/384610239/system_interrupt.o: ../src/system_config/pic32mx_usb_sk_int_dyn/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/384610239 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/384610239/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/384610239/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/384610239/system_interrupt.o ../src/system_config/pic32mx_usb_sk_int_dyn/system_interrupt.c   
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/117104221/bsp_sys_init.o: ../../../../../../bsp/sk_pic32_mx_usb/bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/117104221 
	@${RM} ${OBJECTDIR}/_ext/117104221/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/117104221/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/117104221/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/117104221/bsp_sys_init.o.d" -o ${OBJECTDIR}/_ext/117104221/bsp_sys_init.o ../../../../../../bsp/sk_pic32_mx_usb/bsp_sys_init.c   
	
${OBJECTDIR}/_ext/117104221/config_performance.o: ../../../../../../bsp/sk_pic32_mx_usb/config_performance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/117104221 
	@${RM} ${OBJECTDIR}/_ext/117104221/config_performance.o.d 
	@${RM} ${OBJECTDIR}/_ext/117104221/config_performance.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/117104221/config_performance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/117104221/config_performance.o.d" -o ${OBJECTDIR}/_ext/117104221/config_performance.o ../../../../../../bsp/sk_pic32_mx_usb/config_performance.c   
	
${OBJECTDIR}/_ext/1585079243/drv_usb.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1585079243 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1585079243/drv_usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usb.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usb.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c   
	
${OBJECTDIR}/_ext/1585079243/drv_usb_device.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1585079243 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1585079243/drv_usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usb_device.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usb_device.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c   
	
${OBJECTDIR}/_ext/241097022/plib_int_pic32.o: ../../../../../../framework/peripheral/int/src/plib_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/241097022 
	@${RM} ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d" -o ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o ../../../../../../framework/peripheral/int/src/plib_int_pic32.c   
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711155467 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c   
	
${OBJECTDIR}/_ext/692885480/usb_device.o: ../../../../../../framework/usb/src/dynamic/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/692885480 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/692885480/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device.o ../../../../../../framework/usb/src/dynamic/usb_device.c   
	
${OBJECTDIR}/_ext/692885480/usb_device_generic.o: ../../../../../../framework/usb/src/dynamic/usb_device_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/692885480 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_generic.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_generic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/692885480/usb_device_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_generic.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_generic.o ../../../../../../framework/usb/src/dynamic/usb_device_generic.c   
	
else
${OBJECTDIR}/_ext/384610239/system_config.o: ../src/system_config/pic32mx_usb_sk_int_dyn/system_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/384610239 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/384610239/system_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/384610239/system_config.o.d" -o ${OBJECTDIR}/_ext/384610239/system_config.o ../src/system_config/pic32mx_usb_sk_int_dyn/system_config.c   
	
${OBJECTDIR}/_ext/384610239/system_init.o: ../src/system_config/pic32mx_usb_sk_int_dyn/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/384610239 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/384610239/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/384610239/system_init.o.d" -o ${OBJECTDIR}/_ext/384610239/system_init.o ../src/system_config/pic32mx_usb_sk_int_dyn/system_init.c   
	
${OBJECTDIR}/_ext/384610239/system_tasks.o: ../src/system_config/pic32mx_usb_sk_int_dyn/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/384610239 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/384610239/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/384610239/system_tasks.o.d" -o ${OBJECTDIR}/_ext/384610239/system_tasks.o ../src/system_config/pic32mx_usb_sk_int_dyn/system_tasks.c   
	
${OBJECTDIR}/_ext/384610239/system_interrupt.o: ../src/system_config/pic32mx_usb_sk_int_dyn/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/384610239 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/384610239/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/384610239/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/384610239/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/384610239/system_interrupt.o ../src/system_config/pic32mx_usb_sk_int_dyn/system_interrupt.c   
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/117104221/bsp_sys_init.o: ../../../../../../bsp/sk_pic32_mx_usb/bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/117104221 
	@${RM} ${OBJECTDIR}/_ext/117104221/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/117104221/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/117104221/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/117104221/bsp_sys_init.o.d" -o ${OBJECTDIR}/_ext/117104221/bsp_sys_init.o ../../../../../../bsp/sk_pic32_mx_usb/bsp_sys_init.c   
	
${OBJECTDIR}/_ext/117104221/config_performance.o: ../../../../../../bsp/sk_pic32_mx_usb/config_performance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/117104221 
	@${RM} ${OBJECTDIR}/_ext/117104221/config_performance.o.d 
	@${RM} ${OBJECTDIR}/_ext/117104221/config_performance.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/117104221/config_performance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/117104221/config_performance.o.d" -o ${OBJECTDIR}/_ext/117104221/config_performance.o ../../../../../../bsp/sk_pic32_mx_usb/config_performance.c   
	
${OBJECTDIR}/_ext/1585079243/drv_usb.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1585079243 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1585079243/drv_usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usb.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usb.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c   
	
${OBJECTDIR}/_ext/1585079243/drv_usb_device.o: ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1585079243 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1585079243/drv_usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1585079243/drv_usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/1585079243/drv_usb_device.o.d" -o ${OBJECTDIR}/_ext/1585079243/drv_usb_device.o ../../../../../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c   
	
${OBJECTDIR}/_ext/241097022/plib_int_pic32.o: ../../../../../../framework/peripheral/int/src/plib_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/241097022 
	@${RM} ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/241097022/plib_int_pic32.o.d" -o ${OBJECTDIR}/_ext/241097022/plib_int_pic32.o ../../../../../../framework/peripheral/int/src/plib_int_pic32.c   
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711155467 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c   
	
${OBJECTDIR}/_ext/692885480/usb_device.o: ../../../../../../framework/usb/src/dynamic/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/692885480 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/692885480/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device.o ../../../../../../framework/usb/src/dynamic/usb_device.c   
	
${OBJECTDIR}/_ext/692885480/usb_device_generic.o: ../../../../../../framework/usb/src/dynamic/usb_device_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/692885480 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_generic.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_generic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/692885480/usb_device_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE="static inline" -DINLINE_API="static inline" -I"../../../../../../framework" -I"../src" -I"../src/system_config/pic32mx_usb_sk_int_dyn" -I"../../../../../../bsp/sk_pic32_mx_usb" -I"." -I"../../../../../../framework/driver/usb/usbfs/src" -Wall -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_generic.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_generic.o ../../../../../../framework/usb/src/dynamic/usb_device_generic.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/generic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/generic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}              -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/generic.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/generic.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/generic.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/pic32mx_usb_sk_int_dyn
	${RM} -r dist/pic32mx_usb_sk_int_dyn

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
