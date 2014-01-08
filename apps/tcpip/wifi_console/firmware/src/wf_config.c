/*******************************************************************************
  MRF24W Driver Customization

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    -Provides access to MRF24W WiFi controller
    -Reference: MRF24W Data sheet, IEEE 802.11 Standard
*******************************************************************************/

/*******************************************************************************
File Name: wf_config.c
Copyright © 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
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

#if defined(TCPIP_IF_MRF24W)

/*==========================================================================*/
/*                                  INCLUDES                                */
/*==========================================================================*/
#include "tcpip/tcpip.h"
#include "driver/wifi/mrf24w/src/drv_wifi_debug_output.h"
#include "wf_config.h"

#if defined ( EZ_CONFIG_SCAN )
#include "../framework/driver/wifi/mrf24w/src/drv_wifi_easy_config.h"
#endif /* EZ_CONFIG_SCAN */

#if defined(SAVE_WPS_CREDENTIALS)
bool g_Get_WPSCredentials = false;
#endif


/*==========================================================================*/
/*                                  DEFINES                                 */
/*==========================================================================*/


/*******************************************************************************
  Function:
    void DRV_WIFI_ProcessEvent(uint16_t event, uint16_t eventInfo);

  Summary:
    Processes WiFi event

  Description:
    This function is called to process a WiFi event,

  Precondition:
    TCPIP stack should be initialized.

  Parameters:
    event       - event code
    eventInfo   - additional information about the event.  Not all events
                  have associated info, in which case this value will be
                  set to DRV_WIFI_NO_ADDITIONAL_INFO (0xff)

  Returns:
    None

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_ProcessEvent(uint16_t event, uint16_t eventInfo)
{
    switch (event)
    {
        /*--------------------------------------*/
        case DRV_WIFI_EVENT_CONNECTION_SUCCESSFUL:
        /*--------------------------------------*/   
            SYS_CONSOLE_MESSAGE("Event: Connection Successful\r\n");
            #if defined(SAVE_WPS_CREDENTIALS)
                WF_SaveWPSCredentials();
            #endif

            #if defined(SYS_CONSOLE_ENABLE)
                WF_OutputConnectionContext();
            #endif
            break;
        
        /*--------------------------------------*/            
        case DRV_WIFI_EVENT_CONNECTION_FAILED:
        case DRV_WIFI_EVENT_CONNECTION_TEMPORARILY_LOST:
        case DRV_WIFI_EVENT_CONNECTION_PERMANENTLY_LOST:
        /*--------------------------------------*/
            #if defined(SYS_CONSOLE_ENABLE)
            WF_OutputConnectionDebugMsg(event, eventInfo);
            #endif
            break; 
            
        /*--------------------------------------*/    
        case DRV_WIFI_EVENT_CONNECTION_REESTABLISHED:
        /*--------------------------------------*/
            SYS_CONSOLE_MESSAGE("Event: Connection Reestablished\r\n");
            #if defined(SAVE_WPS_CREDENTIALS)
                WF_SaveWPSCredentials();
            #endif

            #if defined(SYS_CONSOLE_ENABLE)
                WF_OutputConnectionContext();
            #endif
            break;
            
        /*--------------------------------------*/    
        case DRV_WIFI_EVENT_SCAN_RESULTS_READY:
        /*--------------------------------------*/  
            SYS_CONSOLE_PRINT("Event: Scan Results Ready, %d results \r\n", eventInfo);
            #if defined ( EZ_CONFIG_SCAN )
            WFScanEventHandler(eventInfo);  
            #endif /* EZ_CONFIG_SCAN */
            break;

        /*--------------------------------------*/
        case DRV_WIFI_EVENT_DISCONNECT_DONE:
        /*--------------------------------------*/
            SYS_CONSOLE_MESSAGE("Event: Disconnect complete\r\n");
            break;

        /*--------------------------------------*/
        case DRV_WIFI_EVENT_KEY_CALCULATION_REQUEST:
        /*--------------------------------------*/
            SYS_CONSOLE_MESSAGE("Event: DRV_WIFI_EVENT_KEY_CALCULATION_REQUEST");
            break;

        /*--------------------------------------*/
        case DRV_WIFI_EVENT_ERROR:
        /*--------------------------------------*/
            SYS_CONSOLE_PRINT("Event: WiFi error occurred (%d) See DRV_WIFI_MGMT_ERRORS and DRV_WIFI_MGMT_ERRORS", eventInfo);
            break;

        default:
            SYS_ASSERT(false, "Event: Unknown WiFi Event");  /* unknown event */
            break;
    }        
    
}    

 

#endif /* TCPIP_IF_MRF24W */

