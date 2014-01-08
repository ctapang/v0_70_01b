/*******************************************************************************
  MRF24W Config Data

  File Name: 
    drv_wifi_config_data.c  
  
  Summary:

  Description:
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/


#include <string.h>

#include "tcpip/src/tcpip_private.h"

#if defined(TCPIP_IF_MRF24W)

#include "tcpip/src/system/drivers/xeeprom.h"

extern const TCPIP_MAC_MODULE_CTRL * GetStackData();

DRV_WIFI_CONFIG_DATA *p_wifi_ConfigData;


/****************************************************************************
  Section:
    Stack-Level Functions
  ***************************************************************************/
#if defined(WF_SAVE_CONFIG_TO_MEMORY)
	
	#if defined(WF_MEMORY_EXTERN_EEPROM)
			/*	********************************************* 
		#define WIFI_STORAGET_PARTITION_SIZE    (140)
			This setting "WIFI_STORAGET_PARTITION_SIZE" is the memory size for WiFi setting. 
			***************************************************/
			void WiFi_WriteConfigToMemory(void)
			{
	        #if defined(MEDIA_STORAGE_EEPROM)
				XEEBeginWrite(0);
				XEEWriteArray((uint8_t*)p_wifi_ConfigData, sizeof(DRV_WIFI_CONFIG_DATA));
			#endif
			}
			void WiFi_ReadConfigFromMemory(void)
			{
		    #if defined(MEDIA_STORAGE_EEPROM)
				XEEReadArray(0,(uint8_t*)p_wifi_ConfigData, sizeof(DRV_WIFI_CONFIG_DATA));
			#endif
			}
			void WiFi_EraseConfigFromMemory(void)
			{
				DRV_WIFI_CONFIG_DATA tmp_wifi_ConfigData;
				memset(&tmp_wifi_ConfigData,0x00,sizeof(DRV_WIFI_CONFIG_DATA));
				
			#if defined(MEDIA_STORAGE_EEPROM)
				XEEBeginWrite(0);
				XEEWriteArray((uint8_t*)&tmp_wifi_ConfigData, sizeof(DRV_WIFI_CONFIG_DATA));
			#endif
			}
	
    #elif defined(WF_MEMORY_INSIDE_FLASH)
	    #define NVM_PROGRAM_PAGE 0xbd070000
			uint8_t buf_flash[100];
	
	
			//NVMErasePage((void*)NVM_PROGRAM_PAGE);
			//NVMWriteRow((void*)NVM_PROGRAM_PAGE, (void*)buf_flash);
			//p_data = (void*)NVM_PROGRAM_PAGE;
	
		
			void WiFi_WriteConfigToMemory(void)
			{
				if(sizeof(DRV_WIFI_CONFIG_DATA) > 512) 
					SYS_ASSERT(true, "p_wifi_ConfigData > 512");
				
				NVMErasePage((void*)NVM_PROGRAM_PAGE);
				NVMWriteRow((void*)NVM_PROGRAM_PAGE, (void*)p_wifi_ConfigData);
			}
			void WiFi_ReadConfigFromMemory(void)
			{
				int i;
				uint8_t *p_data1, *p_data2;
				p_data1 = (void*)NVM_PROGRAM_PAGE;
				p_data2 = (void*)p_wifi_ConfigData; 
				for(i=0;i<sizeof(DRV_WIFI_CONFIG_DATA);i++)
				{
					p_data2[i] = p_data1[i];
				}
			}
			void WiFi_EraseConfigFromMemory(void)
			{
				NVMErasePage((void*)NVM_PROGRAM_PAGE);
			}
		
    #endif     //WF_MEMORY_INSIDE_FLASH
	
#else   //WF_SAVE_CONFIG_TO_MEMORY
    DRV_WIFI_CONFIG_DATA SaveWiFiConf_in_memory={0};
    void WiFi_WriteConfigToMemory(void)
    {
        int i;
        uint8_t *p_data1, *p_data2;
        p_data1 = (void*)p_wifi_ConfigData;
        p_data2 = (void*)&SaveWiFiConf_in_memory; 
        for(i=0;i<sizeof(DRV_WIFI_CONFIG_DATA);i++)
        {
            p_data2[i] = p_data1[i];
        }
    }
    void WiFi_ReadConfigFromMemory(void)
    {
        int i;
        uint8_t *p_data1, *p_data2;
        p_data1 = (void*)&SaveWiFiConf_in_memory;
        p_data2 = (void*)p_wifi_ConfigData; 
        for(i=0;i<sizeof(DRV_WIFI_CONFIG_DATA);i++)
        {
            p_data2[i] = p_data1[i];
        }        
    }
	void WiFi_EraseConfigFromMemory(void)
    {
        memset(&SaveWiFiConf_in_memory, 0, sizeof(SaveWiFiConf_in_memory));
    }

#endif  //WF_SAVE_CONFIG_TO_MEMORY
	
	
DRV_WIFI_CONFIG_DATA wifi_ConfigData;
DRV_WIFI_CONFIG_DATA *p_wifi_ConfigData = &wifi_ConfigData;


/*******************************************************************************
  Function:
    void DRV_WIFI_ConfigDataPrint(void);

  Summary:
    Outputs to console the configuration data from the board EEPROM.

  Description:
    This function outputs configuration data from the board EEPROM.

  Precondition:
    TCPIP stack should be initialized.

  Parameters:
    None

  Returns:
    None

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_ConfigDataPrint(void)
{
    int i; 
    char buf[10];
    //const TCPIP_MAC_MODULE_CTRL *p_ctrl = GetStackData();

    SYS_CONSOLE_PRINT("Size of Configdata:  %lu\r\n", sizeof(wifi_ConfigData));
    SYS_CONSOLE_PRINT("networkType:         %d\r\n",  wifi_ConfigData.networkType);
    SYS_CONSOLE_PRINT("netSSID:             %s\r\n",  wifi_ConfigData.netSSID);
    SYS_CONSOLE_PRINT("SsidLength:          %d\r\n",  wifi_ConfigData.SsidLength);
    SYS_CONSOLE_PRINT("SecurityMode:        %d\r\n",  wifi_ConfigData.SecurityMode);
    //SYS_CONSOLE_PRINT("SecurityKey:         %s\r\n",  wifi_ConfigData.SecurityKey);
    {
        for ( i=0; i < wifi_ConfigData.SecurityKeyLength ; i++ )
        {
            sprintf(buf,"%.2x", wifi_ConfigData.SecurityKey[i]);
            SYS_CONSOLE_MESSAGE(buf);
        }
        SYS_CONSOLE_MESSAGE("\r\n");
    }
    SYS_CONSOLE_PRINT("SecurityKeyLength:   %d\r\n",  wifi_ConfigData.SecurityKeyLength);
    #if 0  // todo: jw:  will remove this un-used lines
    SYS_CONSOLE_PRINT("DHCP mode:           %d\r\n",  wifi_ConfigData.Flags.bIsDHCPEnabled);
    SYS_CONSOLE_PRINT("IP Address:          %d.%d.%d.%d\r\n",  wifi_ConfigData.netIPAddr.v[0],
                                                               wifi_ConfigData.netIPAddr.v[1],
                                                               wifi_ConfigData.netIPAddr.v[2],
                                                               wifi_ConfigData.netIPAddr.v[3]);

    SYS_CONSOLE_PRINT("netMask:             %d.%d.%d.%d\r\n",  wifi_ConfigData.netMask.v[0],
                                                               wifi_ConfigData.netMask.v[1],
                                                               wifi_ConfigData.netMask.v[2],
                                                               wifi_ConfigData.netMask.v[3]);
    SYS_CONSOLE_PRINT("Gateway:             %d.%d.%d.%d\r\n",  wifi_ConfigData.netGateway.v[0],
                                                               wifi_ConfigData.netGateway.v[1],
                                                               wifi_ConfigData.netGateway.v[2],
                                                               wifi_ConfigData.netGateway.v[3]);

    SYS_CONSOLE_PRINT("Primary DNS Server:  %d.%d.%d.%d\r\n",  wifi_ConfigData.PrimaryDNSServer.v[0],
                                                               wifi_ConfigData.PrimaryDNSServer.v[1],
                                                               wifi_ConfigData.PrimaryDNSServer.v[2],
                                                               wifi_ConfigData.PrimaryDNSServer.v[3]);

    SYS_CONSOLE_PRINT("NetBIOSName:         %s\r\n", wifi_ConfigData.NetBIOSName);
    SYS_CONSOLE_PRINT("IF->NetBIOSName:     %s\r\n", TCPIP_STACK_NetBIOSName(TCPIP_STACK_IndexToNet(p_ctrl->netIx)));
    #endif
}


/*******************************************************************************
  Function:
    bool DRV_WIFI_ConfigDataErase(void);

  Summary:
    Erases configuration data from the board EEPROM.

  Description:
    This function erases configuration data from the board EEPROM.

 Parameters:
    None

  Returns:
    None
 *****************************************************************************/
bool DRV_WIFI_ConfigDataErase(void)
{
    WiFi_EraseConfigFromMemory();
    return true;
}

#endif // TCPIP_IF_MRF24W

//DOM-IGNORE-END

