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
ifeq "$(wildcard nbproject/Makefile-local-XC32_PIC32MX250F128B.mk)" "nbproject/Makefile-local-XC32_PIC32MX250F128B.mk"
include nbproject/Makefile-local-XC32_PIC32MX250F128B.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=XC32_PIC32MX250F128B
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_config.c C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_init.c C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_int.c C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_tasks.c C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/app.c sha256.c condominer.c ..\..\..\v0_70_01b\bsp\pic32mx_usb_audio\config_performance.c bsp_sys_init.c ../../framework/driver/adc/src/static/drv_adc_hw_static.c ../../framework/driver/adc/src/client_single/drv_adc_client_single.c ..\..\..\v0_70_01b\framework\driver\adc\src\drv_adc.c ..\..\..\v0_70_01b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c ..\..\..\v0_70_01b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c ../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c ../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c ..\..\..\v0_70_01b\framework\osal\osal.c ..\..\..\v0_70_01b\framework\peripheral\int\src\plib_int_pic32.c ../../framework/system/clk/src/sys_clk_pic32.c ../../framework/system/clk/src/sys_clk.c ..\..\..\v0_70_01b\framework\system\common\sys_buffer.c ..\..\..\v0_70_01b\framework\system\common\sys_queue.c ..\..\..\v0_70_01b\framework\system\int\src\sys_int_pic32.c ..\..\..\v0_70_01b\framework\system\ports\src\sys_ports.c ..\..\..\v0_70_01b\framework\system\tmr\src\sys_tmr.c ..\..\..\v0_70_01b\framework\system\wdt\src\sys_wdt.c ..\..\..\v0_70_01b\framework\usb\src\dynamic\usb_device.c ../../framework/usb/src/dynamic/usb_device_generic.c exceptions.c main.c system.c user.c HashTest.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/509517107/system_config.o ${OBJECTDIR}/_ext/509517107/system_init.o ${OBJECTDIR}/_ext/509517107/system_int.o ${OBJECTDIR}/_ext/509517107/system_tasks.o ${OBJECTDIR}/_ext/509517107/app.o ${OBJECTDIR}/sha256.o ${OBJECTDIR}/condominer.o ${OBJECTDIR}/_ext/1682119259/config_performance.o ${OBJECTDIR}/bsp_sys_init.o ${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o ${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o ${OBJECTDIR}/_ext/103060854/drv_adc.o ${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o ${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o ${OBJECTDIR}/_ext/1731315957/drv_usb.o ${OBJECTDIR}/_ext/1731315957/drv_usb_device.o ${OBJECTDIR}/_ext/1550366245/osal.o ${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o ${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o ${OBJECTDIR}/_ext/1119106408/sys_clk.o ${OBJECTDIR}/_ext/202626018/sys_buffer.o ${OBJECTDIR}/_ext/202626018/sys_queue.o ${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o ${OBJECTDIR}/_ext/326806979/sys_ports.o ${OBJECTDIR}/_ext/159010422/sys_tmr.o ${OBJECTDIR}/_ext/2047281992/sys_wdt.o ${OBJECTDIR}/_ext/517781785/usb_device.o ${OBJECTDIR}/_ext/184712360/usb_device_generic.o ${OBJECTDIR}/exceptions.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system.o ${OBJECTDIR}/user.o ${OBJECTDIR}/HashTest.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/509517107/system_config.o.d ${OBJECTDIR}/_ext/509517107/system_init.o.d ${OBJECTDIR}/_ext/509517107/system_int.o.d ${OBJECTDIR}/_ext/509517107/system_tasks.o.d ${OBJECTDIR}/_ext/509517107/app.o.d ${OBJECTDIR}/sha256.o.d ${OBJECTDIR}/condominer.o.d ${OBJECTDIR}/_ext/1682119259/config_performance.o.d ${OBJECTDIR}/bsp_sys_init.o.d ${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o.d ${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o.d ${OBJECTDIR}/_ext/103060854/drv_adc.o.d ${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o.d ${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o.d ${OBJECTDIR}/_ext/1731315957/drv_usb.o.d ${OBJECTDIR}/_ext/1731315957/drv_usb_device.o.d ${OBJECTDIR}/_ext/1550366245/osal.o.d ${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o.d ${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o.d ${OBJECTDIR}/_ext/1119106408/sys_clk.o.d ${OBJECTDIR}/_ext/202626018/sys_buffer.o.d ${OBJECTDIR}/_ext/202626018/sys_queue.o.d ${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o.d ${OBJECTDIR}/_ext/326806979/sys_ports.o.d ${OBJECTDIR}/_ext/159010422/sys_tmr.o.d ${OBJECTDIR}/_ext/2047281992/sys_wdt.o.d ${OBJECTDIR}/_ext/517781785/usb_device.o.d ${OBJECTDIR}/_ext/184712360/usb_device_generic.o.d ${OBJECTDIR}/exceptions.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/system.o.d ${OBJECTDIR}/user.o.d ${OBJECTDIR}/HashTest.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/509517107/system_config.o ${OBJECTDIR}/_ext/509517107/system_init.o ${OBJECTDIR}/_ext/509517107/system_int.o ${OBJECTDIR}/_ext/509517107/system_tasks.o ${OBJECTDIR}/_ext/509517107/app.o ${OBJECTDIR}/sha256.o ${OBJECTDIR}/condominer.o ${OBJECTDIR}/_ext/1682119259/config_performance.o ${OBJECTDIR}/bsp_sys_init.o ${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o ${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o ${OBJECTDIR}/_ext/103060854/drv_adc.o ${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o ${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o ${OBJECTDIR}/_ext/1731315957/drv_usb.o ${OBJECTDIR}/_ext/1731315957/drv_usb_device.o ${OBJECTDIR}/_ext/1550366245/osal.o ${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o ${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o ${OBJECTDIR}/_ext/1119106408/sys_clk.o ${OBJECTDIR}/_ext/202626018/sys_buffer.o ${OBJECTDIR}/_ext/202626018/sys_queue.o ${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o ${OBJECTDIR}/_ext/326806979/sys_ports.o ${OBJECTDIR}/_ext/159010422/sys_tmr.o ${OBJECTDIR}/_ext/2047281992/sys_wdt.o ${OBJECTDIR}/_ext/517781785/usb_device.o ${OBJECTDIR}/_ext/184712360/usb_device_generic.o ${OBJECTDIR}/exceptions.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system.o ${OBJECTDIR}/user.o ${OBJECTDIR}/HashTest.o

# Source Files
SOURCEFILES=C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_config.c C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_init.c C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_int.c C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_tasks.c C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/app.c sha256.c condominer.c ..\..\..\v0_70_01b\bsp\pic32mx_usb_audio\config_performance.c bsp_sys_init.c ../../framework/driver/adc/src/static/drv_adc_hw_static.c ../../framework/driver/adc/src/client_single/drv_adc_client_single.c ..\..\..\v0_70_01b\framework\driver\adc\src\drv_adc.c ..\..\..\v0_70_01b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c ..\..\..\v0_70_01b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c ../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c ../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c ..\..\..\v0_70_01b\framework\osal\osal.c ..\..\..\v0_70_01b\framework\peripheral\int\src\plib_int_pic32.c ../../framework/system/clk/src/sys_clk_pic32.c ../../framework/system/clk/src/sys_clk.c ..\..\..\v0_70_01b\framework\system\common\sys_buffer.c ..\..\..\v0_70_01b\framework\system\common\sys_queue.c ..\..\..\v0_70_01b\framework\system\int\src\sys_int_pic32.c ..\..\..\v0_70_01b\framework\system\ports\src\sys_ports.c ..\..\..\v0_70_01b\framework\system\tmr\src\sys_tmr.c ..\..\..\v0_70_01b\framework\system\wdt\src\sys_wdt.c ..\..\..\v0_70_01b\framework\usb\src\dynamic\usb_device.c ../../framework/usb/src/dynamic/usb_device_generic.c exceptions.c main.c system.c user.c HashTest.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-XC32_PIC32MX250F128B.mk dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128B
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
${OBJECTDIR}/_ext/509517107/system_config.o: C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/509517107 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/509517107/system_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/509517107/system_config.o.d" -o ${OBJECTDIR}/_ext/509517107/system_config.o C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_config.c   
	
${OBJECTDIR}/_ext/509517107/system_init.o: C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/509517107 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/509517107/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/509517107/system_init.o.d" -o ${OBJECTDIR}/_ext/509517107/system_init.o C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_init.c   
	
${OBJECTDIR}/_ext/509517107/system_int.o: C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/509517107 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/509517107/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/509517107/system_int.o.d" -o ${OBJECTDIR}/_ext/509517107/system_int.o C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_int.c   
	
${OBJECTDIR}/_ext/509517107/system_tasks.o: C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/509517107 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/509517107/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/509517107/system_tasks.o.d" -o ${OBJECTDIR}/_ext/509517107/system_tasks.o C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_tasks.c   
	
${OBJECTDIR}/_ext/509517107/app.o: C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/509517107 
	@${RM} ${OBJECTDIR}/_ext/509517107/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/509517107/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/509517107/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/509517107/app.o.d" -o ${OBJECTDIR}/_ext/509517107/app.o C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/app.c   
	
${OBJECTDIR}/sha256.o: sha256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sha256.o.d 
	@${RM} ${OBJECTDIR}/sha256.o 
	@${FIXDEPS} "${OBJECTDIR}/sha256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/sha256.o.d" -o ${OBJECTDIR}/sha256.o sha256.c   
	
${OBJECTDIR}/condominer.o: condominer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/condominer.o.d 
	@${RM} ${OBJECTDIR}/condominer.o 
	@${FIXDEPS} "${OBJECTDIR}/condominer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/condominer.o.d" -o ${OBJECTDIR}/condominer.o condominer.c   
	
${OBJECTDIR}/_ext/1682119259/config_performance.o: ..\..\..\v0_70_01b\bsp\pic32mx_usb_audio\config_performance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1682119259 
	@${RM} ${OBJECTDIR}/_ext/1682119259/config_performance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1682119259/config_performance.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1682119259/config_performance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1682119259/config_performance.o.d" -o ${OBJECTDIR}/_ext/1682119259/config_performance.o ..\..\..\v0_70_01b\bsp\pic32mx_usb_audio\config_performance.c   
	
${OBJECTDIR}/bsp_sys_init.o: bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/bsp_sys_init.o.d" -o ${OBJECTDIR}/bsp_sys_init.o bsp_sys_init.c   
	
${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o: ../../framework/driver/adc/src/static/drv_adc_hw_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1103877218 
	@${RM} ${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o.d" -o ${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o ../../framework/driver/adc/src/static/drv_adc_hw_static.c   
	
${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o: ../../framework/driver/adc/src/client_single/drv_adc_client_single.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/153341940 
	@${RM} ${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o.d 
	@${RM} ${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o.d" -o ${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o ../../framework/driver/adc/src/client_single/drv_adc_client_single.c   
	
${OBJECTDIR}/_ext/103060854/drv_adc.o: ..\..\..\v0_70_01b\framework\driver\adc\src\drv_adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/103060854 
	@${RM} ${OBJECTDIR}/_ext/103060854/drv_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/103060854/drv_adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/103060854/drv_adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/103060854/drv_adc.o.d" -o ${OBJECTDIR}/_ext/103060854/drv_adc.o ..\..\..\v0_70_01b\framework\driver\adc\src\drv_adc.c   
	
${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o: ..\..\..\v0_70_01b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2077502471 
	@${RM} ${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o.d" -o ${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o ..\..\..\v0_70_01b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c   
	
${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o: ..\..\..\v0_70_01b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1693901850 
	@${RM} ${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o.d" -o ${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o ..\..\..\v0_70_01b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c   
	
${OBJECTDIR}/_ext/1731315957/drv_usb.o: ../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1731315957 
	@${RM} ${OBJECTDIR}/_ext/1731315957/drv_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1731315957/drv_usb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1731315957/drv_usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1731315957/drv_usb.o.d" -o ${OBJECTDIR}/_ext/1731315957/drv_usb.o ../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c   
	
${OBJECTDIR}/_ext/1731315957/drv_usb_device.o: ../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1731315957 
	@${RM} ${OBJECTDIR}/_ext/1731315957/drv_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1731315957/drv_usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1731315957/drv_usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1731315957/drv_usb_device.o.d" -o ${OBJECTDIR}/_ext/1731315957/drv_usb_device.o ../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c   
	
${OBJECTDIR}/_ext/1550366245/osal.o: ..\..\..\v0_70_01b\framework\osal\osal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1550366245 
	@${RM} ${OBJECTDIR}/_ext/1550366245/osal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1550366245/osal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1550366245/osal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1550366245/osal.o.d" -o ${OBJECTDIR}/_ext/1550366245/osal.o ..\..\..\v0_70_01b\framework\osal\osal.c   
	
${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o: ..\..\..\v0_70_01b\framework\peripheral\int\src\plib_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1131485011 
	@${RM} ${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o ..\..\..\v0_70_01b\framework\peripheral\int\src\plib_int_pic32.c   
	
${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o: ../../framework/system/clk/src/sys_clk_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1119106408 
	@${RM} ${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o.d" -o ${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o ../../framework/system/clk/src/sys_clk_pic32.c   
	
${OBJECTDIR}/_ext/1119106408/sys_clk.o: ../../framework/system/clk/src/sys_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1119106408 
	@${RM} ${OBJECTDIR}/_ext/1119106408/sys_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1119106408/sys_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1119106408/sys_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1119106408/sys_clk.o.d" -o ${OBJECTDIR}/_ext/1119106408/sys_clk.o ../../framework/system/clk/src/sys_clk.c   
	
${OBJECTDIR}/_ext/202626018/sys_buffer.o: ..\..\..\v0_70_01b\framework\system\common\sys_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/202626018 
	@${RM} ${OBJECTDIR}/_ext/202626018/sys_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/202626018/sys_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/202626018/sys_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/202626018/sys_buffer.o.d" -o ${OBJECTDIR}/_ext/202626018/sys_buffer.o ..\..\..\v0_70_01b\framework\system\common\sys_buffer.c   
	
${OBJECTDIR}/_ext/202626018/sys_queue.o: ..\..\..\v0_70_01b\framework\system\common\sys_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/202626018 
	@${RM} ${OBJECTDIR}/_ext/202626018/sys_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/202626018/sys_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/202626018/sys_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/202626018/sys_queue.o.d" -o ${OBJECTDIR}/_ext/202626018/sys_queue.o ..\..\..\v0_70_01b\framework\system\common\sys_queue.c   
	
${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o: ..\..\..\v0_70_01b\framework\system\int\src\sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1301140128 
	@${RM} ${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o ..\..\..\v0_70_01b\framework\system\int\src\sys_int_pic32.c   
	
${OBJECTDIR}/_ext/326806979/sys_ports.o: ..\..\..\v0_70_01b\framework\system\ports\src\sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/326806979 
	@${RM} ${OBJECTDIR}/_ext/326806979/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/326806979/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/326806979/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/326806979/sys_ports.o.d" -o ${OBJECTDIR}/_ext/326806979/sys_ports.o ..\..\..\v0_70_01b\framework\system\ports\src\sys_ports.c   
	
${OBJECTDIR}/_ext/159010422/sys_tmr.o: ..\..\..\v0_70_01b\framework\system\tmr\src\sys_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/159010422 
	@${RM} ${OBJECTDIR}/_ext/159010422/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/159010422/sys_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/159010422/sys_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/159010422/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/159010422/sys_tmr.o ..\..\..\v0_70_01b\framework\system\tmr\src\sys_tmr.c   
	
${OBJECTDIR}/_ext/2047281992/sys_wdt.o: ..\..\..\v0_70_01b\framework\system\wdt\src\sys_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2047281992 
	@${RM} ${OBJECTDIR}/_ext/2047281992/sys_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/2047281992/sys_wdt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2047281992/sys_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/2047281992/sys_wdt.o.d" -o ${OBJECTDIR}/_ext/2047281992/sys_wdt.o ..\..\..\v0_70_01b\framework\system\wdt\src\sys_wdt.c   
	
${OBJECTDIR}/_ext/517781785/usb_device.o: ..\..\..\v0_70_01b\framework\usb\src\dynamic\usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/517781785 
	@${RM} ${OBJECTDIR}/_ext/517781785/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/517781785/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/517781785/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/517781785/usb_device.o.d" -o ${OBJECTDIR}/_ext/517781785/usb_device.o ..\..\..\v0_70_01b\framework\usb\src\dynamic\usb_device.c   
	
${OBJECTDIR}/_ext/184712360/usb_device_generic.o: ../../framework/usb/src/dynamic/usb_device_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/184712360 
	@${RM} ${OBJECTDIR}/_ext/184712360/usb_device_generic.o.d 
	@${RM} ${OBJECTDIR}/_ext/184712360/usb_device_generic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/184712360/usb_device_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/184712360/usb_device_generic.o.d" -o ${OBJECTDIR}/_ext/184712360/usb_device_generic.o ../../framework/usb/src/dynamic/usb_device_generic.c   
	
${OBJECTDIR}/exceptions.o: exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/exceptions.o.d 
	@${RM} ${OBJECTDIR}/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/exceptions.o.d" -o ${OBJECTDIR}/exceptions.o exceptions.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/system.o.d" -o ${OBJECTDIR}/system.o system.c   
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/user.o.d 
	@${RM} ${OBJECTDIR}/user.o 
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/user.o.d" -o ${OBJECTDIR}/user.o user.c   
	
${OBJECTDIR}/HashTest.o: HashTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/HashTest.o.d 
	@${RM} ${OBJECTDIR}/HashTest.o 
	@${FIXDEPS} "${OBJECTDIR}/HashTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/HashTest.o.d" -o ${OBJECTDIR}/HashTest.o HashTest.c   
	
else
${OBJECTDIR}/_ext/509517107/system_config.o: C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/509517107 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/509517107/system_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/509517107/system_config.o.d" -o ${OBJECTDIR}/_ext/509517107/system_config.o C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_config.c   
	
${OBJECTDIR}/_ext/509517107/system_init.o: C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/509517107 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/509517107/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/509517107/system_init.o.d" -o ${OBJECTDIR}/_ext/509517107/system_init.o C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_init.c   
	
${OBJECTDIR}/_ext/509517107/system_int.o: C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/509517107 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/509517107/system_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/509517107/system_int.o.d" -o ${OBJECTDIR}/_ext/509517107/system_int.o C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_int.c   
	
${OBJECTDIR}/_ext/509517107/system_tasks.o: C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/509517107 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/509517107/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/509517107/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/509517107/system_tasks.o.d" -o ${OBJECTDIR}/_ext/509517107/system_tasks.o C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/system_tasks.c   
	
${OBJECTDIR}/_ext/509517107/app.o: C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/509517107 
	@${RM} ${OBJECTDIR}/_ext/509517107/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/509517107/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/509517107/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/509517107/app.o.d" -o ${OBJECTDIR}/_ext/509517107/app.o C:/microchip/harmony/v0_70_01b/apps/Harmony4AvalonGen2.X/app.c   
	
${OBJECTDIR}/sha256.o: sha256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sha256.o.d 
	@${RM} ${OBJECTDIR}/sha256.o 
	@${FIXDEPS} "${OBJECTDIR}/sha256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/sha256.o.d" -o ${OBJECTDIR}/sha256.o sha256.c   
	
${OBJECTDIR}/condominer.o: condominer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/condominer.o.d 
	@${RM} ${OBJECTDIR}/condominer.o 
	@${FIXDEPS} "${OBJECTDIR}/condominer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/condominer.o.d" -o ${OBJECTDIR}/condominer.o condominer.c   
	
${OBJECTDIR}/_ext/1682119259/config_performance.o: ..\..\..\v0_70_01b\bsp\pic32mx_usb_audio\config_performance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1682119259 
	@${RM} ${OBJECTDIR}/_ext/1682119259/config_performance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1682119259/config_performance.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1682119259/config_performance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1682119259/config_performance.o.d" -o ${OBJECTDIR}/_ext/1682119259/config_performance.o ..\..\..\v0_70_01b\bsp\pic32mx_usb_audio\config_performance.c   
	
${OBJECTDIR}/bsp_sys_init.o: bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/bsp_sys_init.o.d" -o ${OBJECTDIR}/bsp_sys_init.o bsp_sys_init.c   
	
${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o: ../../framework/driver/adc/src/static/drv_adc_hw_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1103877218 
	@${RM} ${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o.d" -o ${OBJECTDIR}/_ext/1103877218/drv_adc_hw_static.o ../../framework/driver/adc/src/static/drv_adc_hw_static.c   
	
${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o: ../../framework/driver/adc/src/client_single/drv_adc_client_single.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/153341940 
	@${RM} ${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o.d 
	@${RM} ${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o.d" -o ${OBJECTDIR}/_ext/153341940/drv_adc_client_single.o ../../framework/driver/adc/src/client_single/drv_adc_client_single.c   
	
${OBJECTDIR}/_ext/103060854/drv_adc.o: ..\..\..\v0_70_01b\framework\driver\adc\src\drv_adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/103060854 
	@${RM} ${OBJECTDIR}/_ext/103060854/drv_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/103060854/drv_adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/103060854/drv_adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/103060854/drv_adc.o.d" -o ${OBJECTDIR}/_ext/103060854/drv_adc.o ..\..\..\v0_70_01b\framework\driver\adc\src\drv_adc.c   
	
${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o: ..\..\..\v0_70_01b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2077502471 
	@${RM} ${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o.d" -o ${OBJECTDIR}/_ext/2077502471/drv_spi_dynamic.o ..\..\..\v0_70_01b\framework\driver\spi\src\dynamic\drv_spi_dynamic.c   
	
${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o: ..\..\..\v0_70_01b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1693901850 
	@${RM} ${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o.d" -o ${OBJECTDIR}/_ext/1693901850/drv_tmr_dynamic.o ..\..\..\v0_70_01b\framework\driver\tmr\src\dynamic\drv_tmr_dynamic.c   
	
${OBJECTDIR}/_ext/1731315957/drv_usb.o: ../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1731315957 
	@${RM} ${OBJECTDIR}/_ext/1731315957/drv_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1731315957/drv_usb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1731315957/drv_usb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1731315957/drv_usb.o.d" -o ${OBJECTDIR}/_ext/1731315957/drv_usb.o ../../framework/driver/usb/usbfs/src/dynamic/drv_usb.c   
	
${OBJECTDIR}/_ext/1731315957/drv_usb_device.o: ../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1731315957 
	@${RM} ${OBJECTDIR}/_ext/1731315957/drv_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1731315957/drv_usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1731315957/drv_usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1731315957/drv_usb_device.o.d" -o ${OBJECTDIR}/_ext/1731315957/drv_usb_device.o ../../framework/driver/usb/usbfs/src/dynamic/drv_usb_device.c   
	
${OBJECTDIR}/_ext/1550366245/osal.o: ..\..\..\v0_70_01b\framework\osal\osal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1550366245 
	@${RM} ${OBJECTDIR}/_ext/1550366245/osal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1550366245/osal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1550366245/osal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1550366245/osal.o.d" -o ${OBJECTDIR}/_ext/1550366245/osal.o ..\..\..\v0_70_01b\framework\osal\osal.c   
	
${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o: ..\..\..\v0_70_01b\framework\peripheral\int\src\plib_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1131485011 
	@${RM} ${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1131485011/plib_int_pic32.o ..\..\..\v0_70_01b\framework\peripheral\int\src\plib_int_pic32.c   
	
${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o: ../../framework/system/clk/src/sys_clk_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1119106408 
	@${RM} ${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o.d" -o ${OBJECTDIR}/_ext/1119106408/sys_clk_pic32.o ../../framework/system/clk/src/sys_clk_pic32.c   
	
${OBJECTDIR}/_ext/1119106408/sys_clk.o: ../../framework/system/clk/src/sys_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1119106408 
	@${RM} ${OBJECTDIR}/_ext/1119106408/sys_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1119106408/sys_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1119106408/sys_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1119106408/sys_clk.o.d" -o ${OBJECTDIR}/_ext/1119106408/sys_clk.o ../../framework/system/clk/src/sys_clk.c   
	
${OBJECTDIR}/_ext/202626018/sys_buffer.o: ..\..\..\v0_70_01b\framework\system\common\sys_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/202626018 
	@${RM} ${OBJECTDIR}/_ext/202626018/sys_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/202626018/sys_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/202626018/sys_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/202626018/sys_buffer.o.d" -o ${OBJECTDIR}/_ext/202626018/sys_buffer.o ..\..\..\v0_70_01b\framework\system\common\sys_buffer.c   
	
${OBJECTDIR}/_ext/202626018/sys_queue.o: ..\..\..\v0_70_01b\framework\system\common\sys_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/202626018 
	@${RM} ${OBJECTDIR}/_ext/202626018/sys_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/202626018/sys_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/202626018/sys_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/202626018/sys_queue.o.d" -o ${OBJECTDIR}/_ext/202626018/sys_queue.o ..\..\..\v0_70_01b\framework\system\common\sys_queue.c   
	
${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o: ..\..\..\v0_70_01b\framework\system\int\src\sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1301140128 
	@${RM} ${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1301140128/sys_int_pic32.o ..\..\..\v0_70_01b\framework\system\int\src\sys_int_pic32.c   
	
${OBJECTDIR}/_ext/326806979/sys_ports.o: ..\..\..\v0_70_01b\framework\system\ports\src\sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/326806979 
	@${RM} ${OBJECTDIR}/_ext/326806979/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/326806979/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/326806979/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/326806979/sys_ports.o.d" -o ${OBJECTDIR}/_ext/326806979/sys_ports.o ..\..\..\v0_70_01b\framework\system\ports\src\sys_ports.c   
	
${OBJECTDIR}/_ext/159010422/sys_tmr.o: ..\..\..\v0_70_01b\framework\system\tmr\src\sys_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/159010422 
	@${RM} ${OBJECTDIR}/_ext/159010422/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/159010422/sys_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/159010422/sys_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/159010422/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/159010422/sys_tmr.o ..\..\..\v0_70_01b\framework\system\tmr\src\sys_tmr.c   
	
${OBJECTDIR}/_ext/2047281992/sys_wdt.o: ..\..\..\v0_70_01b\framework\system\wdt\src\sys_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2047281992 
	@${RM} ${OBJECTDIR}/_ext/2047281992/sys_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/2047281992/sys_wdt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2047281992/sys_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/2047281992/sys_wdt.o.d" -o ${OBJECTDIR}/_ext/2047281992/sys_wdt.o ..\..\..\v0_70_01b\framework\system\wdt\src\sys_wdt.c   
	
${OBJECTDIR}/_ext/517781785/usb_device.o: ..\..\..\v0_70_01b\framework\usb\src\dynamic\usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/517781785 
	@${RM} ${OBJECTDIR}/_ext/517781785/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/517781785/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/517781785/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/517781785/usb_device.o.d" -o ${OBJECTDIR}/_ext/517781785/usb_device.o ..\..\..\v0_70_01b\framework\usb\src\dynamic\usb_device.c   
	
${OBJECTDIR}/_ext/184712360/usb_device_generic.o: ../../framework/usb/src/dynamic/usb_device_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/184712360 
	@${RM} ${OBJECTDIR}/_ext/184712360/usb_device_generic.o.d 
	@${RM} ${OBJECTDIR}/_ext/184712360/usb_device_generic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/184712360/usb_device_generic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/_ext/184712360/usb_device_generic.o.d" -o ${OBJECTDIR}/_ext/184712360/usb_device_generic.o ../../framework/usb/src/dynamic/usb_device_generic.c   
	
${OBJECTDIR}/exceptions.o: exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/exceptions.o.d 
	@${RM} ${OBJECTDIR}/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/exceptions.o.d" -o ${OBJECTDIR}/exceptions.o exceptions.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/system.o.d" -o ${OBJECTDIR}/system.o system.c   
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/user.o.d 
	@${RM} ${OBJECTDIR}/user.o 
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/user.o.d" -o ${OBJECTDIR}/user.o user.c   
	
${OBJECTDIR}/HashTest.o: HashTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/HashTest.o.d 
	@${RM} ${OBJECTDIR}/HashTest.o 
	@${FIXDEPS} "${OBJECTDIR}/HashTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -DINLINE_API="static inline" -DINLINE="static inline" -DUSE_CRYPTO_HW -I"../../framework/system" -I"../../framework" -I"." -I"../../framework/usb" -MMD -MF "${OBJECTDIR}/HashTest.o.d" -o ${OBJECTDIR}/HashTest.o HashTest.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ..\\..\\bin\\framework\\peripheral\\PIC32MX250F128B_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\bin\framework\peripheral\PIC32MX250F128B_peripherals.a       -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=512,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ..\\..\\bin\\framework\\peripheral\\PIC32MX250F128B_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\bin\framework\peripheral\PIC32MX250F128B_peripherals.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Harmony4AvalonGen2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/XC32_PIC32MX250F128B
	${RM} -r dist/XC32_PIC32MX250F128B

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
