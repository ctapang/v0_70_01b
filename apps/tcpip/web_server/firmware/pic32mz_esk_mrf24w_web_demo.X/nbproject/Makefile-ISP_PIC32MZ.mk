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
ifeq "$(wildcard nbproject/Makefile-local-ISP_PIC32MZ.mk)" "nbproject/Makefile-local-ISP_PIC32MZ.mk"
include nbproject/Makefile-local-ISP_PIC32MZ.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=ISP_PIC32MZ
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_esk_mrf24w_web_demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_esk_mrf24w_web_demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/app.c ../src/mpfs_img2.c ../src/assert_to_ide.c ../src/wf_config.c ../src/system_config/pic32mz_ec_sk_int_dyn/bsp_sys_init.c ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c ../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_com.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_commands.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_config_data.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connect.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_algorithm.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_manager.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_profile.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_debug_output.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_easy_config.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_eint.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_event_handler.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_events.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_gpio.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_init.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac_pic32.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mgmt_msg.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_param_msg.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_pbkdf2.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_power_save.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_raw.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_scan.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi_init.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_tx_power.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_common.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_tcpclient.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_uart.c ../../../../../framework/tcpip/src/system/drivers/db_appio.c ../../../../../framework/tcpip/src/system/drivers/drv_media.c ../../../../../framework/tcpip/src/system/drivers/usart.c ../../../../../framework/peripheral/eth/src/plib_eth_legacy.c ../../../../../framework/system/clk/src/sys_clk.c ../../../../../framework/system/clk/src/sys_clk_pic32.c ../../../../../framework/tcpip/src/system/fs/mpfs2.c ../../../../../framework/tcpip/src/system/fs/sys_fs.c ../../../../../framework/system/ports/src/sys_ports.c ../../../../../framework/tcpip/src/common/big_int.c ../../../../../framework/tcpip/src/common/big_int_helper_c32.S ../../../../../framework/tcpip/src/common/hashes.c ../../../../../framework/tcpip/src/common/helpers.c ../../../../../framework/tcpip/src/common/lfsr.c ../src/custom_http_app.c ../src/custom_snmp_app.c ../src/custom_ssl_cert.c ../../../../../framework/tcpip/src/ddns.c ../../../../../framework/tcpip/src/dhcp.c ../../../../../framework/tcpip/src/dhcps.c ../../../../../framework/tcpip/src/dns.c ../../../../../framework/tcpip/src/dnss.c ../../../../../framework/tcpip/src/ftp.c ../../../../../framework/tcpip/src/hash_fnv.c ../../../../../framework/tcpip/src/http.c ../../../../../framework/tcpip/src/icmp.c ../../../../../framework/tcpip/src/icmpv6.c ../../../../../framework/tcpip/src/iperf.c ../../../../../framework/tcpip/src/ipv4.c ../../../../../framework/tcpip/src/ipv6.c ../../../../../framework/tcpip/src/nbns.c ../../../../../framework/tcpip/src/ndp.c ../../../../../framework/tcpip/src/oahash.c ../../../../../framework/tcpip/src/rsa.c ../../../../../framework/tcpip/src/smtp.c ../../../../../framework/tcpip/src/snmp.c ../../../../../framework/tcpip/src/snmpv3.c ../../../../../framework/tcpip/src/snmpv3_usm.c ../../../../../framework/tcpip/src/sntp.c ../../../../../framework/tcpip/src/ssl.c ../../../../../framework/tcpip/src/arcfour.c ../../../../../framework/tcpip/src/arp.c ../../../../../framework/tcpip/src/berkeley_api.c ../../../../../framework/tcpip/src/tcp.c ../../../../../framework/tcpip/src/tcpip_announce.c ../../../../../framework/tcpip/src/tcpip_commands.c ../../../../../framework/tcpip/src/tcpip_heap_alloc.c ../../../../../framework/tcpip/src/tcpip_helper_c32.S ../../../../../framework/tcpip/src/tcpip_helpers.c ../../../../../framework/tcpip/src/tcpip_mac_object.c ../../../../../framework/tcpip/src/tcpip_manager.c ../../../../../framework/tcpip/src/tcpip_notify.c ../../../../../framework/tcpip/src/tcpip_packet.c ../../../../../framework/tcpip/src/tcpip_reboot.c ../../../../../framework/tcpip/src/telnet.c ../../../../../framework/tcpip/src/udp.c ../../../../../framework/tcpip/src/zero_conf_helper.c ../../../../../framework/tcpip/src/zero_conf_link_local.c ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c ../../../../../framework/tcpip/src/system/cache.S ../../../../../framework/tcpip/src/system/pic32mz_ports.c ../../../../../framework/tcpip/src/system/system_command.c ../../../../../framework/tcpip/src/system/system_debug.c ../../../../../framework/tcpip/src/system/system_random.c ../../../../../framework/tcpip/src/system/system_services.c ../../../../../framework/tcpip/src/system/system_userio.c ../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ${OBJECTDIR}/_ext/1360937237/assert_to_ide.o ${OBJECTDIR}/_ext/1360937237/wf_config.o ${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o ${OBJECTDIR}/_ext/521481140/drv_ethphy.o ${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o ${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o ${OBJECTDIR}/_ext/2138650627/db_appio.o ${OBJECTDIR}/_ext/2138650627/drv_media.o ${OBJECTDIR}/_ext/2138650627/usart.o ${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o ${OBJECTDIR}/_ext/52938249/sys_clk.o ${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o ${OBJECTDIR}/_ext/478825179/mpfs2.o ${OBJECTDIR}/_ext/478825179/sys_fs.o ${OBJECTDIR}/_ext/826631961/sys_ports.o ${OBJECTDIR}/_ext/1886247299/big_int.o ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o ${OBJECTDIR}/_ext/1886247299/hashes.o ${OBJECTDIR}/_ext/1886247299/helpers.o ${OBJECTDIR}/_ext/1886247299/lfsr.o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o ${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o ${OBJECTDIR}/_ext/1164207549/ddns.o ${OBJECTDIR}/_ext/1164207549/dhcp.o ${OBJECTDIR}/_ext/1164207549/dhcps.o ${OBJECTDIR}/_ext/1164207549/dns.o ${OBJECTDIR}/_ext/1164207549/dnss.o ${OBJECTDIR}/_ext/1164207549/ftp.o ${OBJECTDIR}/_ext/1164207549/hash_fnv.o ${OBJECTDIR}/_ext/1164207549/http.o ${OBJECTDIR}/_ext/1164207549/icmp.o ${OBJECTDIR}/_ext/1164207549/icmpv6.o ${OBJECTDIR}/_ext/1164207549/iperf.o ${OBJECTDIR}/_ext/1164207549/ipv4.o ${OBJECTDIR}/_ext/1164207549/ipv6.o ${OBJECTDIR}/_ext/1164207549/nbns.o ${OBJECTDIR}/_ext/1164207549/ndp.o ${OBJECTDIR}/_ext/1164207549/oahash.o ${OBJECTDIR}/_ext/1164207549/rsa.o ${OBJECTDIR}/_ext/1164207549/smtp.o ${OBJECTDIR}/_ext/1164207549/snmp.o ${OBJECTDIR}/_ext/1164207549/snmpv3.o ${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o ${OBJECTDIR}/_ext/1164207549/sntp.o ${OBJECTDIR}/_ext/1164207549/ssl.o ${OBJECTDIR}/_ext/1164207549/arcfour.o ${OBJECTDIR}/_ext/1164207549/arp.o ${OBJECTDIR}/_ext/1164207549/berkeley_api.o ${OBJECTDIR}/_ext/1164207549/tcp.o ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o ${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o ${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o ${OBJECTDIR}/_ext/1164207549/telnet.o ${OBJECTDIR}/_ext/1164207549/udp.o ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o ${OBJECTDIR}/_ext/1418760511/cache.o ${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o ${OBJECTDIR}/_ext/1418760511/system_command.o ${OBJECTDIR}/_ext/1418760511/system_debug.o ${OBJECTDIR}/_ext/1418760511/system_random.o ${OBJECTDIR}/_ext/1418760511/system_services.o ${OBJECTDIR}/_ext/1418760511/system_userio.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d ${OBJECTDIR}/_ext/1360937237/assert_to_ide.o.d ${OBJECTDIR}/_ext/1360937237/wf_config.o.d ${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o.d ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d ${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d ${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o.d ${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o.d ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o.d ${OBJECTDIR}/_ext/2138650627/db_appio.o.d ${OBJECTDIR}/_ext/2138650627/drv_media.o.d ${OBJECTDIR}/_ext/2138650627/usart.o.d ${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o.d ${OBJECTDIR}/_ext/52938249/sys_clk.o.d ${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o.d ${OBJECTDIR}/_ext/478825179/mpfs2.o.d ${OBJECTDIR}/_ext/478825179/sys_fs.o.d ${OBJECTDIR}/_ext/826631961/sys_ports.o.d ${OBJECTDIR}/_ext/1886247299/big_int.o.d ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.d ${OBJECTDIR}/_ext/1886247299/hashes.o.d ${OBJECTDIR}/_ext/1886247299/helpers.o.d ${OBJECTDIR}/_ext/1886247299/lfsr.o.d ${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d ${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o.d ${OBJECTDIR}/_ext/1164207549/ddns.o.d ${OBJECTDIR}/_ext/1164207549/dhcp.o.d ${OBJECTDIR}/_ext/1164207549/dhcps.o.d ${OBJECTDIR}/_ext/1164207549/dns.o.d ${OBJECTDIR}/_ext/1164207549/dnss.o.d ${OBJECTDIR}/_ext/1164207549/ftp.o.d ${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d ${OBJECTDIR}/_ext/1164207549/http.o.d ${OBJECTDIR}/_ext/1164207549/icmp.o.d ${OBJECTDIR}/_ext/1164207549/icmpv6.o.d ${OBJECTDIR}/_ext/1164207549/iperf.o.d ${OBJECTDIR}/_ext/1164207549/ipv4.o.d ${OBJECTDIR}/_ext/1164207549/ipv6.o.d ${OBJECTDIR}/_ext/1164207549/nbns.o.d ${OBJECTDIR}/_ext/1164207549/ndp.o.d ${OBJECTDIR}/_ext/1164207549/oahash.o.d ${OBJECTDIR}/_ext/1164207549/rsa.o.d ${OBJECTDIR}/_ext/1164207549/smtp.o.d ${OBJECTDIR}/_ext/1164207549/snmp.o.d ${OBJECTDIR}/_ext/1164207549/snmpv3.o.d ${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o.d ${OBJECTDIR}/_ext/1164207549/sntp.o.d ${OBJECTDIR}/_ext/1164207549/ssl.o.d ${OBJECTDIR}/_ext/1164207549/arcfour.o.d ${OBJECTDIR}/_ext/1164207549/arp.o.d ${OBJECTDIR}/_ext/1164207549/berkeley_api.o.d ${OBJECTDIR}/_ext/1164207549/tcp.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o.d ${OBJECTDIR}/_ext/1164207549/telnet.o.d ${OBJECTDIR}/_ext/1164207549/udp.o.d ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d ${OBJECTDIR}/_ext/1418760511/cache.o.d ${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o.d ${OBJECTDIR}/_ext/1418760511/system_command.o.d ${OBJECTDIR}/_ext/1418760511/system_debug.o.d ${OBJECTDIR}/_ext/1418760511/system_random.o.d ${OBJECTDIR}/_ext/1418760511/system_services.o.d ${OBJECTDIR}/_ext/1418760511/system_userio.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ${OBJECTDIR}/_ext/1360937237/assert_to_ide.o ${OBJECTDIR}/_ext/1360937237/wf_config.o ${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o ${OBJECTDIR}/_ext/521481140/drv_ethphy.o ${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o ${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o ${OBJECTDIR}/_ext/2138650627/db_appio.o ${OBJECTDIR}/_ext/2138650627/drv_media.o ${OBJECTDIR}/_ext/2138650627/usart.o ${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o ${OBJECTDIR}/_ext/52938249/sys_clk.o ${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o ${OBJECTDIR}/_ext/478825179/mpfs2.o ${OBJECTDIR}/_ext/478825179/sys_fs.o ${OBJECTDIR}/_ext/826631961/sys_ports.o ${OBJECTDIR}/_ext/1886247299/big_int.o ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o ${OBJECTDIR}/_ext/1886247299/hashes.o ${OBJECTDIR}/_ext/1886247299/helpers.o ${OBJECTDIR}/_ext/1886247299/lfsr.o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o ${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o ${OBJECTDIR}/_ext/1164207549/ddns.o ${OBJECTDIR}/_ext/1164207549/dhcp.o ${OBJECTDIR}/_ext/1164207549/dhcps.o ${OBJECTDIR}/_ext/1164207549/dns.o ${OBJECTDIR}/_ext/1164207549/dnss.o ${OBJECTDIR}/_ext/1164207549/ftp.o ${OBJECTDIR}/_ext/1164207549/hash_fnv.o ${OBJECTDIR}/_ext/1164207549/http.o ${OBJECTDIR}/_ext/1164207549/icmp.o ${OBJECTDIR}/_ext/1164207549/icmpv6.o ${OBJECTDIR}/_ext/1164207549/iperf.o ${OBJECTDIR}/_ext/1164207549/ipv4.o ${OBJECTDIR}/_ext/1164207549/ipv6.o ${OBJECTDIR}/_ext/1164207549/nbns.o ${OBJECTDIR}/_ext/1164207549/ndp.o ${OBJECTDIR}/_ext/1164207549/oahash.o ${OBJECTDIR}/_ext/1164207549/rsa.o ${OBJECTDIR}/_ext/1164207549/smtp.o ${OBJECTDIR}/_ext/1164207549/snmp.o ${OBJECTDIR}/_ext/1164207549/snmpv3.o ${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o ${OBJECTDIR}/_ext/1164207549/sntp.o ${OBJECTDIR}/_ext/1164207549/ssl.o ${OBJECTDIR}/_ext/1164207549/arcfour.o ${OBJECTDIR}/_ext/1164207549/arp.o ${OBJECTDIR}/_ext/1164207549/berkeley_api.o ${OBJECTDIR}/_ext/1164207549/tcp.o ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o ${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o ${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o ${OBJECTDIR}/_ext/1164207549/telnet.o ${OBJECTDIR}/_ext/1164207549/udp.o ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o ${OBJECTDIR}/_ext/1418760511/cache.o ${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o ${OBJECTDIR}/_ext/1418760511/system_command.o ${OBJECTDIR}/_ext/1418760511/system_debug.o ${OBJECTDIR}/_ext/1418760511/system_random.o ${OBJECTDIR}/_ext/1418760511/system_services.o ${OBJECTDIR}/_ext/1418760511/system_userio.o ${OBJECTDIR}/_ext/1360937237/main.o

# Source Files
SOURCEFILES=../src/app.c ../src/mpfs_img2.c ../src/assert_to_ide.c ../src/wf_config.c ../src/system_config/pic32mz_ec_sk_int_dyn/bsp_sys_init.c ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c ../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_com.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_commands.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_config_data.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connect.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_algorithm.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_manager.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_profile.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_debug_output.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_easy_config.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_eint.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_event_handler.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_events.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_gpio.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_init.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac_pic32.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mgmt_msg.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_param_msg.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_pbkdf2.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_power_save.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_raw.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_scan.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi_init.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_tx_power.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_common.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_tcpclient.c ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_uart.c ../../../../../framework/tcpip/src/system/drivers/db_appio.c ../../../../../framework/tcpip/src/system/drivers/drv_media.c ../../../../../framework/tcpip/src/system/drivers/usart.c ../../../../../framework/peripheral/eth/src/plib_eth_legacy.c ../../../../../framework/system/clk/src/sys_clk.c ../../../../../framework/system/clk/src/sys_clk_pic32.c ../../../../../framework/tcpip/src/system/fs/mpfs2.c ../../../../../framework/tcpip/src/system/fs/sys_fs.c ../../../../../framework/system/ports/src/sys_ports.c ../../../../../framework/tcpip/src/common/big_int.c ../../../../../framework/tcpip/src/common/big_int_helper_c32.S ../../../../../framework/tcpip/src/common/hashes.c ../../../../../framework/tcpip/src/common/helpers.c ../../../../../framework/tcpip/src/common/lfsr.c ../src/custom_http_app.c ../src/custom_snmp_app.c ../src/custom_ssl_cert.c ../../../../../framework/tcpip/src/ddns.c ../../../../../framework/tcpip/src/dhcp.c ../../../../../framework/tcpip/src/dhcps.c ../../../../../framework/tcpip/src/dns.c ../../../../../framework/tcpip/src/dnss.c ../../../../../framework/tcpip/src/ftp.c ../../../../../framework/tcpip/src/hash_fnv.c ../../../../../framework/tcpip/src/http.c ../../../../../framework/tcpip/src/icmp.c ../../../../../framework/tcpip/src/icmpv6.c ../../../../../framework/tcpip/src/iperf.c ../../../../../framework/tcpip/src/ipv4.c ../../../../../framework/tcpip/src/ipv6.c ../../../../../framework/tcpip/src/nbns.c ../../../../../framework/tcpip/src/ndp.c ../../../../../framework/tcpip/src/oahash.c ../../../../../framework/tcpip/src/rsa.c ../../../../../framework/tcpip/src/smtp.c ../../../../../framework/tcpip/src/snmp.c ../../../../../framework/tcpip/src/snmpv3.c ../../../../../framework/tcpip/src/snmpv3_usm.c ../../../../../framework/tcpip/src/sntp.c ../../../../../framework/tcpip/src/ssl.c ../../../../../framework/tcpip/src/arcfour.c ../../../../../framework/tcpip/src/arp.c ../../../../../framework/tcpip/src/berkeley_api.c ../../../../../framework/tcpip/src/tcp.c ../../../../../framework/tcpip/src/tcpip_announce.c ../../../../../framework/tcpip/src/tcpip_commands.c ../../../../../framework/tcpip/src/tcpip_heap_alloc.c ../../../../../framework/tcpip/src/tcpip_helper_c32.S ../../../../../framework/tcpip/src/tcpip_helpers.c ../../../../../framework/tcpip/src/tcpip_mac_object.c ../../../../../framework/tcpip/src/tcpip_manager.c ../../../../../framework/tcpip/src/tcpip_notify.c ../../../../../framework/tcpip/src/tcpip_packet.c ../../../../../framework/tcpip/src/tcpip_reboot.c ../../../../../framework/tcpip/src/telnet.c ../../../../../framework/tcpip/src/udp.c ../../../../../framework/tcpip/src/zero_conf_helper.c ../../../../../framework/tcpip/src/zero_conf_link_local.c ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c ../../../../../framework/tcpip/src/system/cache.S ../../../../../framework/tcpip/src/system/pic32mz_ports.c ../../../../../framework/tcpip/src/system/system_command.c ../../../../../framework/tcpip/src/system/system_debug.c ../../../../../framework/tcpip/src/system/system_random.c ../../../../../framework/tcpip/src/system/system_services.c ../../../../../framework/tcpip/src/system/system_userio.c ../src/main.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-ISP_PIC32MZ.mk dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_esk_mrf24w_web_demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2048ECH144
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o: ../../../../../framework/tcpip/src/common/big_int_helper_c32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1886247299 
	@${RM} ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o 
	@${RM} ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.ok ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.d" "${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.d"  -o ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o ../../../../../framework/tcpip/src/common/big_int_helper_c32.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o: ../../../../../framework/tcpip/src/tcpip_helper_c32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.ok ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d" "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d"  -o ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o ../../../../../framework/tcpip/src/tcpip_helper_c32.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
${OBJECTDIR}/_ext/1418760511/cache.o: ../../../../../framework/tcpip/src/system/cache.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/cache.o 
	@${RM} ${OBJECTDIR}/_ext/1418760511/cache.o.ok ${OBJECTDIR}/_ext/1418760511/cache.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/cache.o.d" "${OBJECTDIR}/_ext/1418760511/cache.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1418760511/cache.o.d"  -o ${OBJECTDIR}/_ext/1418760511/cache.o ../../../../../framework/tcpip/src/system/cache.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1418760511/cache.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o: ../../../../../framework/tcpip/src/common/big_int_helper_c32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1886247299 
	@${RM} ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o 
	@${RM} ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.ok ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.d" "${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.d"  -o ${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o ../../../../../framework/tcpip/src/common/big_int_helper_c32.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1886247299/big_int_helper_c32.o.asm.d",--gdwarf-2
	
${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o: ../../../../../framework/tcpip/src/tcpip_helper_c32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.ok ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d" "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d"  -o ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o ../../../../../framework/tcpip/src/tcpip_helper_c32.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.asm.d",--gdwarf-2
	
${OBJECTDIR}/_ext/1418760511/cache.o: ../../../../../framework/tcpip/src/system/cache.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/cache.o 
	@${RM} ${OBJECTDIR}/_ext/1418760511/cache.o.ok ${OBJECTDIR}/_ext/1418760511/cache.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/cache.o.d" "${OBJECTDIR}/_ext/1418760511/cache.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1418760511/cache.o.d"  -o ${OBJECTDIR}/_ext/1418760511/cache.o ../../../../../framework/tcpip/src/system/cache.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1418760511/cache.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c   
	
${OBJECTDIR}/_ext/1360937237/mpfs_img2.o: ../src/mpfs_img2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" -o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ../src/mpfs_img2.c   
	
${OBJECTDIR}/_ext/1360937237/assert_to_ide.o: ../src/assert_to_ide.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/assert_to_ide.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/assert_to_ide.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/assert_to_ide.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/assert_to_ide.o.d" -o ${OBJECTDIR}/_ext/1360937237/assert_to_ide.o ../src/assert_to_ide.c   
	
${OBJECTDIR}/_ext/1360937237/wf_config.o: ../src/wf_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/wf_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/wf_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/wf_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/wf_config.o.d" -o ${OBJECTDIR}/_ext/1360937237/wf_config.o ../src/wf_config.c   
	
${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o: ../src/system_config/pic32mz_ec_sk_int_dyn/bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1789036259 
	@${RM} ${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o.d" -o ${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o ../src/system_config/pic32mz_ec_sk_int_dyn/bsp_sys_init.c   
	
${OBJECTDIR}/_ext/1697634946/drv_ethmac.o: ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1697634946 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d" -o ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c   
	
${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o: ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1697634946 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d" -o ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c   
	
${OBJECTDIR}/_ext/521481140/drv_ethphy.o: ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/521481140 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_ethphy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d" -o ${OBJECTDIR}/_ext/521481140/drv_ethphy.o ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c   
	
${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o: ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/521481140 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o.d 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o.d" -o ${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c   
	
${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o: ../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1324760662 
	@${RM} ${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o.d" -o ${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o ../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_com.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_commands.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_config_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_config_data.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connect.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connect.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_algorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_algorithm.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_manager.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_profile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_profile.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_debug_output.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_debug_output.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_easy_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_easy_config.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_eint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_eint.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_event_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_event_handler.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_events.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_gpio.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_init.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac_pic32.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mgmt_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mgmt_msg.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_param_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_param_msg.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_pbkdf2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_pbkdf2.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_power_save.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_power_save.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_raw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_raw.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_scan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_scan.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi_init.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_tx_power.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_tx_power.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_common.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_tcpclient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_tcpclient.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_uart.c   
	
${OBJECTDIR}/_ext/2138650627/db_appio.o: ../../../../../framework/tcpip/src/system/drivers/db_appio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2138650627 
	@${RM} ${OBJECTDIR}/_ext/2138650627/db_appio.o.d 
	@${RM} ${OBJECTDIR}/_ext/2138650627/db_appio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2138650627/db_appio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/2138650627/db_appio.o.d" -o ${OBJECTDIR}/_ext/2138650627/db_appio.o ../../../../../framework/tcpip/src/system/drivers/db_appio.c   
	
${OBJECTDIR}/_ext/2138650627/drv_media.o: ../../../../../framework/tcpip/src/system/drivers/drv_media.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2138650627 
	@${RM} ${OBJECTDIR}/_ext/2138650627/drv_media.o.d 
	@${RM} ${OBJECTDIR}/_ext/2138650627/drv_media.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2138650627/drv_media.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/2138650627/drv_media.o.d" -o ${OBJECTDIR}/_ext/2138650627/drv_media.o ../../../../../framework/tcpip/src/system/drivers/drv_media.c   
	
${OBJECTDIR}/_ext/2138650627/usart.o: ../../../../../framework/tcpip/src/system/drivers/usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2138650627 
	@${RM} ${OBJECTDIR}/_ext/2138650627/usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/2138650627/usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2138650627/usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/2138650627/usart.o.d" -o ${OBJECTDIR}/_ext/2138650627/usart.o ../../../../../framework/tcpip/src/system/drivers/usart.c   
	
${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o: ../../../../../framework/peripheral/eth/src/plib_eth_legacy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1104573755 
	@${RM} ${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o.d 
	@${RM} ${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o.d" -o ${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o ../../../../../framework/peripheral/eth/src/plib_eth_legacy.c   
	
${OBJECTDIR}/_ext/52938249/sys_clk.o: ../../../../../framework/system/clk/src/sys_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/52938249 
	@${RM} ${OBJECTDIR}/_ext/52938249/sys_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/52938249/sys_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/52938249/sys_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/52938249/sys_clk.o.d" -o ${OBJECTDIR}/_ext/52938249/sys_clk.o ../../../../../framework/system/clk/src/sys_clk.c   
	
${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o: ../../../../../framework/system/clk/src/sys_clk_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/52938249 
	@${RM} ${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o.d" -o ${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o ../../../../../framework/system/clk/src/sys_clk_pic32.c   
	
${OBJECTDIR}/_ext/478825179/mpfs2.o: ../../../../../framework/tcpip/src/system/fs/mpfs2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/478825179 
	@${RM} ${OBJECTDIR}/_ext/478825179/mpfs2.o.d 
	@${RM} ${OBJECTDIR}/_ext/478825179/mpfs2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/478825179/mpfs2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/478825179/mpfs2.o.d" -o ${OBJECTDIR}/_ext/478825179/mpfs2.o ../../../../../framework/tcpip/src/system/fs/mpfs2.c   
	
${OBJECTDIR}/_ext/478825179/sys_fs.o: ../../../../../framework/tcpip/src/system/fs/sys_fs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/478825179 
	@${RM} ${OBJECTDIR}/_ext/478825179/sys_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/478825179/sys_fs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/478825179/sys_fs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/478825179/sys_fs.o.d" -o ${OBJECTDIR}/_ext/478825179/sys_fs.o ../../../../../framework/tcpip/src/system/fs/sys_fs.c   
	
${OBJECTDIR}/_ext/826631961/sys_ports.o: ../../../../../framework/system/ports/src/sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/826631961 
	@${RM} ${OBJECTDIR}/_ext/826631961/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/826631961/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/826631961/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/826631961/sys_ports.o.d" -o ${OBJECTDIR}/_ext/826631961/sys_ports.o ../../../../../framework/system/ports/src/sys_ports.c   
	
${OBJECTDIR}/_ext/1886247299/big_int.o: ../../../../../framework/tcpip/src/common/big_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1886247299 
	@${RM} ${OBJECTDIR}/_ext/1886247299/big_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/big_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/big_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1886247299/big_int.o.d" -o ${OBJECTDIR}/_ext/1886247299/big_int.o ../../../../../framework/tcpip/src/common/big_int.c   
	
${OBJECTDIR}/_ext/1886247299/hashes.o: ../../../../../framework/tcpip/src/common/hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1886247299 
	@${RM} ${OBJECTDIR}/_ext/1886247299/hashes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/hashes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1886247299/hashes.o.d" -o ${OBJECTDIR}/_ext/1886247299/hashes.o ../../../../../framework/tcpip/src/common/hashes.c   
	
${OBJECTDIR}/_ext/1886247299/helpers.o: ../../../../../framework/tcpip/src/common/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1886247299 
	@${RM} ${OBJECTDIR}/_ext/1886247299/helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1886247299/helpers.o.d" -o ${OBJECTDIR}/_ext/1886247299/helpers.o ../../../../../framework/tcpip/src/common/helpers.c   
	
${OBJECTDIR}/_ext/1886247299/lfsr.o: ../../../../../framework/tcpip/src/common/lfsr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1886247299 
	@${RM} ${OBJECTDIR}/_ext/1886247299/lfsr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/lfsr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/lfsr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1886247299/lfsr.o.d" -o ${OBJECTDIR}/_ext/1886247299/lfsr.o ../../../../../framework/tcpip/src/common/lfsr.c   
	
${OBJECTDIR}/_ext/1360937237/custom_http_app.o: ../src/custom_http_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ../src/custom_http_app.c   
	
${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o: ../src/custom_snmp_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o ../src/custom_snmp_app.c   
	
${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o: ../src/custom_ssl_cert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o ../src/custom_ssl_cert.c   
	
${OBJECTDIR}/_ext/1164207549/ddns.o: ../../../../../framework/tcpip/src/ddns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ddns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ddns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ddns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ddns.o.d" -o ${OBJECTDIR}/_ext/1164207549/ddns.o ../../../../../framework/tcpip/src/ddns.c   
	
${OBJECTDIR}/_ext/1164207549/dhcp.o: ../../../../../framework/tcpip/src/dhcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dhcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dhcp.o.d" -o ${OBJECTDIR}/_ext/1164207549/dhcp.o ../../../../../framework/tcpip/src/dhcp.c   
	
${OBJECTDIR}/_ext/1164207549/dhcps.o: ../../../../../framework/tcpip/src/dhcps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcps.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dhcps.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dhcps.o.d" -o ${OBJECTDIR}/_ext/1164207549/dhcps.o ../../../../../framework/tcpip/src/dhcps.c   
	
${OBJECTDIR}/_ext/1164207549/dns.o: ../../../../../framework/tcpip/src/dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dns.o.d" -o ${OBJECTDIR}/_ext/1164207549/dns.o ../../../../../framework/tcpip/src/dns.c   
	
${OBJECTDIR}/_ext/1164207549/dnss.o: ../../../../../framework/tcpip/src/dnss.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dnss.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dnss.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dnss.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dnss.o.d" -o ${OBJECTDIR}/_ext/1164207549/dnss.o ../../../../../framework/tcpip/src/dnss.c   
	
${OBJECTDIR}/_ext/1164207549/ftp.o: ../../../../../framework/tcpip/src/ftp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ftp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ftp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ftp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ftp.o.d" -o ${OBJECTDIR}/_ext/1164207549/ftp.o ../../../../../framework/tcpip/src/ftp.c   
	
${OBJECTDIR}/_ext/1164207549/hash_fnv.o: ../../../../../framework/tcpip/src/hash_fnv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/hash_fnv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d" -o ${OBJECTDIR}/_ext/1164207549/hash_fnv.o ../../../../../framework/tcpip/src/hash_fnv.c   
	
${OBJECTDIR}/_ext/1164207549/http.o: ../../../../../framework/tcpip/src/http.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/http.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/http.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/http.o.d" -o ${OBJECTDIR}/_ext/1164207549/http.o ../../../../../framework/tcpip/src/http.c   
	
${OBJECTDIR}/_ext/1164207549/icmp.o: ../../../../../framework/tcpip/src/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/icmp.o.d" -o ${OBJECTDIR}/_ext/1164207549/icmp.o ../../../../../framework/tcpip/src/icmp.c   
	
${OBJECTDIR}/_ext/1164207549/icmpv6.o: ../../../../../framework/tcpip/src/icmpv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmpv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmpv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/icmpv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/icmpv6.o.d" -o ${OBJECTDIR}/_ext/1164207549/icmpv6.o ../../../../../framework/tcpip/src/icmpv6.c   
	
${OBJECTDIR}/_ext/1164207549/iperf.o: ../../../../../framework/tcpip/src/iperf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/iperf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/iperf.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/iperf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/iperf.o.d" -o ${OBJECTDIR}/_ext/1164207549/iperf.o ../../../../../framework/tcpip/src/iperf.c   
	
${OBJECTDIR}/_ext/1164207549/ipv4.o: ../../../../../framework/tcpip/src/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ipv4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ipv4.o.d" -o ${OBJECTDIR}/_ext/1164207549/ipv4.o ../../../../../framework/tcpip/src/ipv4.c   
	
${OBJECTDIR}/_ext/1164207549/ipv6.o: ../../../../../framework/tcpip/src/ipv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ipv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ipv6.o.d" -o ${OBJECTDIR}/_ext/1164207549/ipv6.o ../../../../../framework/tcpip/src/ipv6.c   
	
${OBJECTDIR}/_ext/1164207549/nbns.o: ../../../../../framework/tcpip/src/nbns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/nbns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/nbns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/nbns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/nbns.o.d" -o ${OBJECTDIR}/_ext/1164207549/nbns.o ../../../../../framework/tcpip/src/nbns.c   
	
${OBJECTDIR}/_ext/1164207549/ndp.o: ../../../../../framework/tcpip/src/ndp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ndp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ndp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ndp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ndp.o.d" -o ${OBJECTDIR}/_ext/1164207549/ndp.o ../../../../../framework/tcpip/src/ndp.c   
	
${OBJECTDIR}/_ext/1164207549/oahash.o: ../../../../../framework/tcpip/src/oahash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/oahash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/oahash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/oahash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/oahash.o.d" -o ${OBJECTDIR}/_ext/1164207549/oahash.o ../../../../../framework/tcpip/src/oahash.c   
	
${OBJECTDIR}/_ext/1164207549/rsa.o: ../../../../../framework/tcpip/src/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/rsa.o.d" -o ${OBJECTDIR}/_ext/1164207549/rsa.o ../../../../../framework/tcpip/src/rsa.c   
	
${OBJECTDIR}/_ext/1164207549/smtp.o: ../../../../../framework/tcpip/src/smtp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/smtp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/smtp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/smtp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/smtp.o.d" -o ${OBJECTDIR}/_ext/1164207549/smtp.o ../../../../../framework/tcpip/src/smtp.c   
	
${OBJECTDIR}/_ext/1164207549/snmp.o: ../../../../../framework/tcpip/src/snmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/snmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/snmp.o.d" -o ${OBJECTDIR}/_ext/1164207549/snmp.o ../../../../../framework/tcpip/src/snmp.c   
	
${OBJECTDIR}/_ext/1164207549/snmpv3.o: ../../../../../framework/tcpip/src/snmpv3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/snmpv3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/snmpv3.o.d" -o ${OBJECTDIR}/_ext/1164207549/snmpv3.o ../../../../../framework/tcpip/src/snmpv3.c   
	
${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o: ../../../../../framework/tcpip/src/snmpv3_usm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o.d" -o ${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o ../../../../../framework/tcpip/src/snmpv3_usm.c   
	
${OBJECTDIR}/_ext/1164207549/sntp.o: ../../../../../framework/tcpip/src/sntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/sntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/sntp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/sntp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/sntp.o.d" -o ${OBJECTDIR}/_ext/1164207549/sntp.o ../../../../../framework/tcpip/src/sntp.c   
	
${OBJECTDIR}/_ext/1164207549/ssl.o: ../../../../../framework/tcpip/src/ssl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ssl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ssl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ssl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ssl.o.d" -o ${OBJECTDIR}/_ext/1164207549/ssl.o ../../../../../framework/tcpip/src/ssl.c   
	
${OBJECTDIR}/_ext/1164207549/arcfour.o: ../../../../../framework/tcpip/src/arcfour.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arcfour.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arcfour.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/arcfour.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/arcfour.o.d" -o ${OBJECTDIR}/_ext/1164207549/arcfour.o ../../../../../framework/tcpip/src/arcfour.c   
	
${OBJECTDIR}/_ext/1164207549/arp.o: ../../../../../framework/tcpip/src/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/arp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/arp.o.d" -o ${OBJECTDIR}/_ext/1164207549/arp.o ../../../../../framework/tcpip/src/arp.c   
	
${OBJECTDIR}/_ext/1164207549/berkeley_api.o: ../../../../../framework/tcpip/src/berkeley_api.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/berkeley_api.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/berkeley_api.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/berkeley_api.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/berkeley_api.o.d" -o ${OBJECTDIR}/_ext/1164207549/berkeley_api.o ../../../../../framework/tcpip/src/berkeley_api.c   
	
${OBJECTDIR}/_ext/1164207549/tcp.o: ../../../../../framework/tcpip/src/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcp.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcp.o ../../../../../framework/tcpip/src/tcp.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_announce.o: ../../../../../framework/tcpip/src/tcpip_announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o ../../../../../framework/tcpip/src/tcpip_announce.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_commands.o: ../../../../../framework/tcpip/src/tcpip_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o ../../../../../framework/tcpip/src/tcpip_commands.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o: ../../../../../framework/tcpip/src/tcpip_heap_alloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o ../../../../../framework/tcpip/src/tcpip_heap_alloc.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o: ../../../../../framework/tcpip/src/tcpip_helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o ../../../../../framework/tcpip/src/tcpip_helpers.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o: ../../../../../framework/tcpip/src/tcpip_mac_object.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o ../../../../../framework/tcpip/src/tcpip_mac_object.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_manager.o: ../../../../../framework/tcpip/src/tcpip_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o ../../../../../framework/tcpip/src/tcpip_manager.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_notify.o: ../../../../../framework/tcpip/src/tcpip_notify.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o ../../../../../framework/tcpip/src/tcpip_notify.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_packet.o: ../../../../../framework/tcpip/src/tcpip_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o ../../../../../framework/tcpip/src/tcpip_packet.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o: ../../../../../framework/tcpip/src/tcpip_reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o ../../../../../framework/tcpip/src/tcpip_reboot.c   
	
${OBJECTDIR}/_ext/1164207549/telnet.o: ../../../../../framework/tcpip/src/telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/telnet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/telnet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/telnet.o.d" -o ${OBJECTDIR}/_ext/1164207549/telnet.o ../../../../../framework/tcpip/src/telnet.c   
	
${OBJECTDIR}/_ext/1164207549/udp.o: ../../../../../framework/tcpip/src/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/udp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/udp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/udp.o.d" -o ${OBJECTDIR}/_ext/1164207549/udp.o ../../../../../framework/tcpip/src/udp.c   
	
${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o: ../../../../../framework/tcpip/src/zero_conf_helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o ../../../../../framework/tcpip/src/zero_conf_helper.c   
	
${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o: ../../../../../framework/tcpip/src/zero_conf_link_local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o ../../../../../framework/tcpip/src/zero_conf_link_local.c   
	
${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o: ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c   
	
${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o: ../../../../../framework/tcpip/src/system/pic32mz_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o.d" -o ${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o ../../../../../framework/tcpip/src/system/pic32mz_ports.c   
	
${OBJECTDIR}/_ext/1418760511/system_command.o: ../../../../../framework/tcpip/src/system/system_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_command.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/system_command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/system_command.o.d" -o ${OBJECTDIR}/_ext/1418760511/system_command.o ../../../../../framework/tcpip/src/system/system_command.c   
	
${OBJECTDIR}/_ext/1418760511/system_debug.o: ../../../../../framework/tcpip/src/system/system_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/system_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/system_debug.o.d" -o ${OBJECTDIR}/_ext/1418760511/system_debug.o ../../../../../framework/tcpip/src/system/system_debug.c   
	
${OBJECTDIR}/_ext/1418760511/system_random.o: ../../../../../framework/tcpip/src/system/system_random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/system_random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/system_random.o.d" -o ${OBJECTDIR}/_ext/1418760511/system_random.o ../../../../../framework/tcpip/src/system/system_random.c   
	
${OBJECTDIR}/_ext/1418760511/system_services.o: ../../../../../framework/tcpip/src/system/system_services.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_services.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_services.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/system_services.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/system_services.o.d" -o ${OBJECTDIR}/_ext/1418760511/system_services.o ../../../../../framework/tcpip/src/system/system_services.c   
	
${OBJECTDIR}/_ext/1418760511/system_userio.o: ../../../../../framework/tcpip/src/system/system_userio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_userio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_userio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/system_userio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/system_userio.o.d" -o ${OBJECTDIR}/_ext/1418760511/system_userio.o ../../../../../framework/tcpip/src/system/system_userio.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
else
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c   
	
${OBJECTDIR}/_ext/1360937237/mpfs_img2.o: ../src/mpfs_img2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" -o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ../src/mpfs_img2.c   
	
${OBJECTDIR}/_ext/1360937237/assert_to_ide.o: ../src/assert_to_ide.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/assert_to_ide.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/assert_to_ide.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/assert_to_ide.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/assert_to_ide.o.d" -o ${OBJECTDIR}/_ext/1360937237/assert_to_ide.o ../src/assert_to_ide.c   
	
${OBJECTDIR}/_ext/1360937237/wf_config.o: ../src/wf_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/wf_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/wf_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/wf_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/wf_config.o.d" -o ${OBJECTDIR}/_ext/1360937237/wf_config.o ../src/wf_config.c   
	
${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o: ../src/system_config/pic32mz_ec_sk_int_dyn/bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1789036259 
	@${RM} ${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o.d" -o ${OBJECTDIR}/_ext/1789036259/bsp_sys_init.o ../src/system_config/pic32mz_ec_sk_int_dyn/bsp_sys_init.c   
	
${OBJECTDIR}/_ext/1697634946/drv_ethmac.o: ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1697634946 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d" -o ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c   
	
${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o: ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1697634946 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d" -o ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c   
	
${OBJECTDIR}/_ext/521481140/drv_ethphy.o: ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/521481140 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_ethphy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d" -o ${OBJECTDIR}/_ext/521481140/drv_ethphy.o ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c   
	
${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o: ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/521481140 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o.d 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o.d" -o ${OBJECTDIR}/_ext/521481140/drv_extphy_smsc8740.o ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c   
	
${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o: ../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1324760662 
	@${RM} ${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o.d" -o ${OBJECTDIR}/_ext/1324760662/drv_spi_dynamic.o ../../../../../framework/driver/spi/src/dynamic/drv_spi_dynamic.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_com.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_com.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_commands.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_commands.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_config_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_config_data.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_config_data.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connect.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connect.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connect.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_algorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_algorithm.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_algorithm.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_manager.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_manager.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_profile.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_connection_profile.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_connection_profile.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_debug_output.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_debug_output.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_debug_output.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_easy_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_easy_config.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_easy_config.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_eint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_eint.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_eint.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_event_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_event_handler.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_event_handler.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_events.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_events.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_gpio.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_gpio.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_init.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_init.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mac_pic32.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mac_pic32.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mgmt_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_mgmt_msg.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_mgmt_msg.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_param_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_param_msg.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_param_msg.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_pbkdf2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_pbkdf2.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_pbkdf2.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_power_save.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_power_save.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_power_save.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_raw.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_raw.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_raw.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_scan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_scan.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_scan.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_spi_init.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_spi_init.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_tx_power.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_tx_power.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_tx_power.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_common.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_common.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_tcpclient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_tcpclient.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_tcpclient.c   
	
${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o: ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1023149444 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o.d" -o ${OBJECTDIR}/_ext/1023149444/drv_wifi_update_firmware_uart.o ../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_update_firmware_uart.c   
	
${OBJECTDIR}/_ext/2138650627/db_appio.o: ../../../../../framework/tcpip/src/system/drivers/db_appio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2138650627 
	@${RM} ${OBJECTDIR}/_ext/2138650627/db_appio.o.d 
	@${RM} ${OBJECTDIR}/_ext/2138650627/db_appio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2138650627/db_appio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/2138650627/db_appio.o.d" -o ${OBJECTDIR}/_ext/2138650627/db_appio.o ../../../../../framework/tcpip/src/system/drivers/db_appio.c   
	
${OBJECTDIR}/_ext/2138650627/drv_media.o: ../../../../../framework/tcpip/src/system/drivers/drv_media.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2138650627 
	@${RM} ${OBJECTDIR}/_ext/2138650627/drv_media.o.d 
	@${RM} ${OBJECTDIR}/_ext/2138650627/drv_media.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2138650627/drv_media.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/2138650627/drv_media.o.d" -o ${OBJECTDIR}/_ext/2138650627/drv_media.o ../../../../../framework/tcpip/src/system/drivers/drv_media.c   
	
${OBJECTDIR}/_ext/2138650627/usart.o: ../../../../../framework/tcpip/src/system/drivers/usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2138650627 
	@${RM} ${OBJECTDIR}/_ext/2138650627/usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/2138650627/usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2138650627/usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/2138650627/usart.o.d" -o ${OBJECTDIR}/_ext/2138650627/usart.o ../../../../../framework/tcpip/src/system/drivers/usart.c   
	
${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o: ../../../../../framework/peripheral/eth/src/plib_eth_legacy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1104573755 
	@${RM} ${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o.d 
	@${RM} ${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o.d" -o ${OBJECTDIR}/_ext/1104573755/plib_eth_legacy.o ../../../../../framework/peripheral/eth/src/plib_eth_legacy.c   
	
${OBJECTDIR}/_ext/52938249/sys_clk.o: ../../../../../framework/system/clk/src/sys_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/52938249 
	@${RM} ${OBJECTDIR}/_ext/52938249/sys_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/52938249/sys_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/52938249/sys_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/52938249/sys_clk.o.d" -o ${OBJECTDIR}/_ext/52938249/sys_clk.o ../../../../../framework/system/clk/src/sys_clk.c   
	
${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o: ../../../../../framework/system/clk/src/sys_clk_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/52938249 
	@${RM} ${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o.d" -o ${OBJECTDIR}/_ext/52938249/sys_clk_pic32.o ../../../../../framework/system/clk/src/sys_clk_pic32.c   
	
${OBJECTDIR}/_ext/478825179/mpfs2.o: ../../../../../framework/tcpip/src/system/fs/mpfs2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/478825179 
	@${RM} ${OBJECTDIR}/_ext/478825179/mpfs2.o.d 
	@${RM} ${OBJECTDIR}/_ext/478825179/mpfs2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/478825179/mpfs2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/478825179/mpfs2.o.d" -o ${OBJECTDIR}/_ext/478825179/mpfs2.o ../../../../../framework/tcpip/src/system/fs/mpfs2.c   
	
${OBJECTDIR}/_ext/478825179/sys_fs.o: ../../../../../framework/tcpip/src/system/fs/sys_fs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/478825179 
	@${RM} ${OBJECTDIR}/_ext/478825179/sys_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/478825179/sys_fs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/478825179/sys_fs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/478825179/sys_fs.o.d" -o ${OBJECTDIR}/_ext/478825179/sys_fs.o ../../../../../framework/tcpip/src/system/fs/sys_fs.c   
	
${OBJECTDIR}/_ext/826631961/sys_ports.o: ../../../../../framework/system/ports/src/sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/826631961 
	@${RM} ${OBJECTDIR}/_ext/826631961/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/826631961/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/826631961/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/826631961/sys_ports.o.d" -o ${OBJECTDIR}/_ext/826631961/sys_ports.o ../../../../../framework/system/ports/src/sys_ports.c   
	
${OBJECTDIR}/_ext/1886247299/big_int.o: ../../../../../framework/tcpip/src/common/big_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1886247299 
	@${RM} ${OBJECTDIR}/_ext/1886247299/big_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/big_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/big_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1886247299/big_int.o.d" -o ${OBJECTDIR}/_ext/1886247299/big_int.o ../../../../../framework/tcpip/src/common/big_int.c   
	
${OBJECTDIR}/_ext/1886247299/hashes.o: ../../../../../framework/tcpip/src/common/hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1886247299 
	@${RM} ${OBJECTDIR}/_ext/1886247299/hashes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/hashes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1886247299/hashes.o.d" -o ${OBJECTDIR}/_ext/1886247299/hashes.o ../../../../../framework/tcpip/src/common/hashes.c   
	
${OBJECTDIR}/_ext/1886247299/helpers.o: ../../../../../framework/tcpip/src/common/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1886247299 
	@${RM} ${OBJECTDIR}/_ext/1886247299/helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1886247299/helpers.o.d" -o ${OBJECTDIR}/_ext/1886247299/helpers.o ../../../../../framework/tcpip/src/common/helpers.c   
	
${OBJECTDIR}/_ext/1886247299/lfsr.o: ../../../../../framework/tcpip/src/common/lfsr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1886247299 
	@${RM} ${OBJECTDIR}/_ext/1886247299/lfsr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/lfsr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/lfsr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1886247299/lfsr.o.d" -o ${OBJECTDIR}/_ext/1886247299/lfsr.o ../../../../../framework/tcpip/src/common/lfsr.c   
	
${OBJECTDIR}/_ext/1360937237/custom_http_app.o: ../src/custom_http_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ../src/custom_http_app.c   
	
${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o: ../src/custom_snmp_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o ../src/custom_snmp_app.c   
	
${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o: ../src/custom_ssl_cert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_ssl_cert.o ../src/custom_ssl_cert.c   
	
${OBJECTDIR}/_ext/1164207549/ddns.o: ../../../../../framework/tcpip/src/ddns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ddns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ddns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ddns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ddns.o.d" -o ${OBJECTDIR}/_ext/1164207549/ddns.o ../../../../../framework/tcpip/src/ddns.c   
	
${OBJECTDIR}/_ext/1164207549/dhcp.o: ../../../../../framework/tcpip/src/dhcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dhcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dhcp.o.d" -o ${OBJECTDIR}/_ext/1164207549/dhcp.o ../../../../../framework/tcpip/src/dhcp.c   
	
${OBJECTDIR}/_ext/1164207549/dhcps.o: ../../../../../framework/tcpip/src/dhcps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcps.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dhcps.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dhcps.o.d" -o ${OBJECTDIR}/_ext/1164207549/dhcps.o ../../../../../framework/tcpip/src/dhcps.c   
	
${OBJECTDIR}/_ext/1164207549/dns.o: ../../../../../framework/tcpip/src/dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dns.o.d" -o ${OBJECTDIR}/_ext/1164207549/dns.o ../../../../../framework/tcpip/src/dns.c   
	
${OBJECTDIR}/_ext/1164207549/dnss.o: ../../../../../framework/tcpip/src/dnss.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dnss.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dnss.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dnss.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dnss.o.d" -o ${OBJECTDIR}/_ext/1164207549/dnss.o ../../../../../framework/tcpip/src/dnss.c   
	
${OBJECTDIR}/_ext/1164207549/ftp.o: ../../../../../framework/tcpip/src/ftp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ftp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ftp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ftp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ftp.o.d" -o ${OBJECTDIR}/_ext/1164207549/ftp.o ../../../../../framework/tcpip/src/ftp.c   
	
${OBJECTDIR}/_ext/1164207549/hash_fnv.o: ../../../../../framework/tcpip/src/hash_fnv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/hash_fnv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d" -o ${OBJECTDIR}/_ext/1164207549/hash_fnv.o ../../../../../framework/tcpip/src/hash_fnv.c   
	
${OBJECTDIR}/_ext/1164207549/http.o: ../../../../../framework/tcpip/src/http.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/http.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/http.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/http.o.d" -o ${OBJECTDIR}/_ext/1164207549/http.o ../../../../../framework/tcpip/src/http.c   
	
${OBJECTDIR}/_ext/1164207549/icmp.o: ../../../../../framework/tcpip/src/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/icmp.o.d" -o ${OBJECTDIR}/_ext/1164207549/icmp.o ../../../../../framework/tcpip/src/icmp.c   
	
${OBJECTDIR}/_ext/1164207549/icmpv6.o: ../../../../../framework/tcpip/src/icmpv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmpv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmpv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/icmpv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/icmpv6.o.d" -o ${OBJECTDIR}/_ext/1164207549/icmpv6.o ../../../../../framework/tcpip/src/icmpv6.c   
	
${OBJECTDIR}/_ext/1164207549/iperf.o: ../../../../../framework/tcpip/src/iperf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/iperf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/iperf.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/iperf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/iperf.o.d" -o ${OBJECTDIR}/_ext/1164207549/iperf.o ../../../../../framework/tcpip/src/iperf.c   
	
${OBJECTDIR}/_ext/1164207549/ipv4.o: ../../../../../framework/tcpip/src/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ipv4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ipv4.o.d" -o ${OBJECTDIR}/_ext/1164207549/ipv4.o ../../../../../framework/tcpip/src/ipv4.c   
	
${OBJECTDIR}/_ext/1164207549/ipv6.o: ../../../../../framework/tcpip/src/ipv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ipv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ipv6.o.d" -o ${OBJECTDIR}/_ext/1164207549/ipv6.o ../../../../../framework/tcpip/src/ipv6.c   
	
${OBJECTDIR}/_ext/1164207549/nbns.o: ../../../../../framework/tcpip/src/nbns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/nbns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/nbns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/nbns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/nbns.o.d" -o ${OBJECTDIR}/_ext/1164207549/nbns.o ../../../../../framework/tcpip/src/nbns.c   
	
${OBJECTDIR}/_ext/1164207549/ndp.o: ../../../../../framework/tcpip/src/ndp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ndp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ndp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ndp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ndp.o.d" -o ${OBJECTDIR}/_ext/1164207549/ndp.o ../../../../../framework/tcpip/src/ndp.c   
	
${OBJECTDIR}/_ext/1164207549/oahash.o: ../../../../../framework/tcpip/src/oahash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/oahash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/oahash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/oahash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/oahash.o.d" -o ${OBJECTDIR}/_ext/1164207549/oahash.o ../../../../../framework/tcpip/src/oahash.c   
	
${OBJECTDIR}/_ext/1164207549/rsa.o: ../../../../../framework/tcpip/src/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/rsa.o.d" -o ${OBJECTDIR}/_ext/1164207549/rsa.o ../../../../../framework/tcpip/src/rsa.c   
	
${OBJECTDIR}/_ext/1164207549/smtp.o: ../../../../../framework/tcpip/src/smtp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/smtp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/smtp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/smtp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/smtp.o.d" -o ${OBJECTDIR}/_ext/1164207549/smtp.o ../../../../../framework/tcpip/src/smtp.c   
	
${OBJECTDIR}/_ext/1164207549/snmp.o: ../../../../../framework/tcpip/src/snmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/snmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/snmp.o.d" -o ${OBJECTDIR}/_ext/1164207549/snmp.o ../../../../../framework/tcpip/src/snmp.c   
	
${OBJECTDIR}/_ext/1164207549/snmpv3.o: ../../../../../framework/tcpip/src/snmpv3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/snmpv3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/snmpv3.o.d" -o ${OBJECTDIR}/_ext/1164207549/snmpv3.o ../../../../../framework/tcpip/src/snmpv3.c   
	
${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o: ../../../../../framework/tcpip/src/snmpv3_usm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o.d" -o ${OBJECTDIR}/_ext/1164207549/snmpv3_usm.o ../../../../../framework/tcpip/src/snmpv3_usm.c   
	
${OBJECTDIR}/_ext/1164207549/sntp.o: ../../../../../framework/tcpip/src/sntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/sntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/sntp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/sntp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/sntp.o.d" -o ${OBJECTDIR}/_ext/1164207549/sntp.o ../../../../../framework/tcpip/src/sntp.c   
	
${OBJECTDIR}/_ext/1164207549/ssl.o: ../../../../../framework/tcpip/src/ssl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ssl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ssl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ssl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ssl.o.d" -o ${OBJECTDIR}/_ext/1164207549/ssl.o ../../../../../framework/tcpip/src/ssl.c   
	
${OBJECTDIR}/_ext/1164207549/arcfour.o: ../../../../../framework/tcpip/src/arcfour.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arcfour.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arcfour.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/arcfour.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/arcfour.o.d" -o ${OBJECTDIR}/_ext/1164207549/arcfour.o ../../../../../framework/tcpip/src/arcfour.c   
	
${OBJECTDIR}/_ext/1164207549/arp.o: ../../../../../framework/tcpip/src/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/arp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/arp.o.d" -o ${OBJECTDIR}/_ext/1164207549/arp.o ../../../../../framework/tcpip/src/arp.c   
	
${OBJECTDIR}/_ext/1164207549/berkeley_api.o: ../../../../../framework/tcpip/src/berkeley_api.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/berkeley_api.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/berkeley_api.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/berkeley_api.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/berkeley_api.o.d" -o ${OBJECTDIR}/_ext/1164207549/berkeley_api.o ../../../../../framework/tcpip/src/berkeley_api.c   
	
${OBJECTDIR}/_ext/1164207549/tcp.o: ../../../../../framework/tcpip/src/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcp.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcp.o ../../../../../framework/tcpip/src/tcp.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_announce.o: ../../../../../framework/tcpip/src/tcpip_announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o ../../../../../framework/tcpip/src/tcpip_announce.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_commands.o: ../../../../../framework/tcpip/src/tcpip_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o ../../../../../framework/tcpip/src/tcpip_commands.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o: ../../../../../framework/tcpip/src/tcpip_heap_alloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o ../../../../../framework/tcpip/src/tcpip_heap_alloc.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o: ../../../../../framework/tcpip/src/tcpip_helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o ../../../../../framework/tcpip/src/tcpip_helpers.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o: ../../../../../framework/tcpip/src/tcpip_mac_object.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_mac_object.o ../../../../../framework/tcpip/src/tcpip_mac_object.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_manager.o: ../../../../../framework/tcpip/src/tcpip_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o ../../../../../framework/tcpip/src/tcpip_manager.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_notify.o: ../../../../../framework/tcpip/src/tcpip_notify.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o ../../../../../framework/tcpip/src/tcpip_notify.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_packet.o: ../../../../../framework/tcpip/src/tcpip_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o ../../../../../framework/tcpip/src/tcpip_packet.c   
	
${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o: ../../../../../framework/tcpip/src/tcpip_reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_reboot.o ../../../../../framework/tcpip/src/tcpip_reboot.c   
	
${OBJECTDIR}/_ext/1164207549/telnet.o: ../../../../../framework/tcpip/src/telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/telnet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/telnet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/telnet.o.d" -o ${OBJECTDIR}/_ext/1164207549/telnet.o ../../../../../framework/tcpip/src/telnet.c   
	
${OBJECTDIR}/_ext/1164207549/udp.o: ../../../../../framework/tcpip/src/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/udp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/udp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/udp.o.d" -o ${OBJECTDIR}/_ext/1164207549/udp.o ../../../../../framework/tcpip/src/udp.c   
	
${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o: ../../../../../framework/tcpip/src/zero_conf_helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o ../../../../../framework/tcpip/src/zero_conf_helper.c   
	
${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o: ../../../../../framework/tcpip/src/zero_conf_link_local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o ../../../../../framework/tcpip/src/zero_conf_link_local.c   
	
${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o: ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1164207549 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c   
	
${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o: ../../../../../framework/tcpip/src/system/pic32mz_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o.d" -o ${OBJECTDIR}/_ext/1418760511/pic32mz_ports.o ../../../../../framework/tcpip/src/system/pic32mz_ports.c   
	
${OBJECTDIR}/_ext/1418760511/system_command.o: ../../../../../framework/tcpip/src/system/system_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_command.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/system_command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/system_command.o.d" -o ${OBJECTDIR}/_ext/1418760511/system_command.o ../../../../../framework/tcpip/src/system/system_command.c   
	
${OBJECTDIR}/_ext/1418760511/system_debug.o: ../../../../../framework/tcpip/src/system/system_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/system_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/system_debug.o.d" -o ${OBJECTDIR}/_ext/1418760511/system_debug.o ../../../../../framework/tcpip/src/system/system_debug.c   
	
${OBJECTDIR}/_ext/1418760511/system_random.o: ../../../../../framework/tcpip/src/system/system_random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/system_random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/system_random.o.d" -o ${OBJECTDIR}/_ext/1418760511/system_random.o ../../../../../framework/tcpip/src/system/system_random.c   
	
${OBJECTDIR}/_ext/1418760511/system_services.o: ../../../../../framework/tcpip/src/system/system_services.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_services.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_services.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/system_services.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/system_services.o.d" -o ${OBJECTDIR}/_ext/1418760511/system_services.o ../../../../../framework/tcpip/src/system/system_services.c   
	
${OBJECTDIR}/_ext/1418760511/system_userio.o: ../../../../../framework/tcpip/src/system/system_userio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1418760511 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_userio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1418760511/system_userio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1418760511/system_userio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1418760511/system_userio.o.d" -o ${OBJECTDIR}/_ext/1418760511/system_userio.o ../../../../../framework/tcpip/src/system/system_userio.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -ffunction-sections -DPIC32_STARTER_KIT -DINLINE="static inline" -DINLINE_API="static inline" -DTCPIP_IF_MRF24W -I"../src" -I"../src/system_config/pic32mz_esk_mrf24w" -I"../src/system_config/pic32mz_esk_mrf24w/tcpip_profile" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_esk_mrf24w_web_demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_esk_mrf24w_web_demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x27F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=44960,--defsym=_min_stack_size=2048,--gc-sections
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_esk_mrf24w_web_demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_esk_mrf24w_web_demo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=44960,--defsym=_min_stack_size=2048,--gc-sections
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_esk_mrf24w_web_demo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/ISP_PIC32MZ
	${RM} -r dist/ISP_PIC32MZ

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
