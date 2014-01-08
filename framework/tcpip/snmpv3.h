/*******************************************************************************
 Simple Mail Transfer Protocol (SMTP) v3 API Header File

  Company:
    Microchip Technology Inc.
    
  File Name:
    snmpv3.h

  Summary:

  Description:
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

#ifndef _SNMPV3_H_
#define _SNMPV3_H_

#include "tcpip/tcpip.h"
#include "snmpv3_config.h"
#include "tcpip/src/snmpv3_private.h"
#include "tcpip/snmp.h"

// SNMPv3 Descriptor Structure Typedef
typedef struct
{
    uint16_t UserInfoDataBaseIndx;

    uint8_t SnmpEngineID[32]; //Reserving 32 bytes for the snmpEngineID as the octet string length can vary form 5 to 32 //**
    uint8_t SnmpEngnIDLength;//**

    uint16_t SnmpMsgBufSeekPos;
    uint16_t ScopedPduDataPos;//**

    uint32_t SnmpEngineTimeOffset;//**
    uint32_t SnmpEngineBoots;//The number of times that the SNMP engine has (re-)initialized itself since snmpEngineID was last configured.//**

    TCPIP_UINT16_VAL UsmStatsEngineID;  //**
    TCPIP_UINT32_VAL AuthoritativeSnmpEngineBoots;//**
    TCPIP_UINT32_VAL AuthoritativeSnmpEngnTime;//**
    TCPIP_UINT32_VAL IncmngSnmpPduMsgID;//**
    TCPIP_UINT32_VAL SnmpEngineTime;//The number of seconds since the value of the SnmpEngineBoots object last changed//**
    TCPIP_UINT32_VAL SnmpEngnMaxMsgSize;//**

    SNMPV3_REQUEST_WHOLEMSG InPduWholeMsgBuf;//**
    SNMPV3_RESPONSE_WHOLEMSG OUTPduWholeMsgBuf;//**
    SNMPV3_RESPONSE_WHOLEMSG TrapOUTPduWholeMsgBuf;

    //snmv3 global database for trap table
    snmpV3TrapConfigDataBase Snmpv3TrapConfigData[SNMPV3_USM_MAX_USER];

    SNMPV3MSGDATA ScopedPduRequstBuf;
    SNMPV3MSGDATA ScopedPduRespnsBuf;
    SNMPV3MSGDATA PduHeaderBuf;
    SNMPV3MSGDATA TrapMsgHeaderBuf;
    SNMPV3MSGDATA TrapScopdPduRespnsBuf;

    dispatcherProcessPdu incomingPdu;

    uint8_t  SnmpSecurityLevel;
    uint8_t  SnmpRespnsSecrtyFlg;

    uint8_t SnmpInMsgAuthParmStrng[12+1];
    uint8_t SnmpInMsgAuthParamLen;
    uint8_t snmpInMsgPrvParamStrng[8+1];
    uint8_t SnmpInMsgPrivParmLen;

    uint8_t SnmpOutMsgAuthParaStrng[12+1];
    uint8_t SnmpOutMsgAuthParmLen;
    uint8_t SnmpOutMsgPrvParmStrng[8+1];
    uint8_t SnmpOutMsgPrivParmLen;

    uint32_t SnmpEngnSecurityModel;//Maximum range (2^31-1), RFC3411
    uint32_t SnmpEngnMsgProcessModel;//Maximum range (2^31-1), RFC3411

    SecuritySysProcessIncomingMsg SecurtyPrimtvesOfIncmngPdu;//**

    snmpV3EngnUserDataBase UserInfoDataBase[SNMPV3_USM_MAX_USER];//**

} SNMPV3_STACK_DCPT_STUB;


// SNMPv3 Processing Memory Pointers
typedef struct
{
    SNMPV3_STACK_DCPT_STUB * snmpv3StkProcessingDynMemStubPtr;
    const void* snmpHeapMemHandler;

} SNMPV3_PROCESSING_MEM_INFO_PTRS;


/****************************************************************************
  Function:
    void SNMPv3ComputeHMACIpadOpadForAuthLoclzedKey(uint8_t userDBIndex)

  Summary:
    Compute HMAC inner and outer pad for authorization localized key.

  Description:
    This routine computes HMAC inner and outer pad strings for authorization localized key.
    RFC - 2104.

  Precondition:
    TCPIP_SNMPv3_Initialize() and ProcessVariabels() are called.

  Parameters:
    userDBIndex -  password storage poniter

  Return Values:
    None

  Remarks:
    None
 */
void SNMPv3ComputeHMACIpadOpadForAuthLoclzedKey(uint8_t userDBIndex);


/****************************************************************************
  Function:
    bool TCPIP_SNMPv3_CmprTrapSecNameAndSecLvlWithUSMDb(
                uint8_t tragetIndex,
                uint8_t userTrapSecLen,
                uint8_t *userTrapSecurityName,
                STD_BASED_SNMPV3_SECURITY_LEVEL securityLevel)

  Summary:
    Routine to find the index of the user name in the user data base table.

  Description:
    There are two different data base tables defined with SNMPv3 stack,
    like 'UserInfoDataBase' and 'Snmpv3TrapConfigData'.
    This routine is used to validte the trap user security level setting with
    SET request.


  Precondition:
    SET operation would be allowed if the USM security conditions and
    user security name in the request is matched to one of the user security
    name stored in the usm user database.

  Parameters:
    targetIndex -index of the 'Snmpv3TrapConfigData' table to match the
                 'userSecurityName' with the user data base
    userTrapSecLen - user sec name length in the SET request
    userTrapSecurityName - pointer to user sec name in the SET request
    securityLevel - trap security level to be SET on the agent

  Return Values:
    true - if the trap target user sec level setting is successful
    FLASE - If the SET failed due to non matching of the security parameters

  Remarks:
    None.
 */
bool TCPIP_SNMPv3_CmprTrapSecNameAndSecLvlWithUSMDb(uint8_t tragetIndex,
                                                    uint8_t userTrapSecLen,
                                                    uint8_t *userTrapSecurityName,
                                                    STD_BASED_SNMPV3_SECURITY_LEVEL securityLevel);

/****************************************************************************
  Function:
    void SNMPv3USMAuthPrivPswdLocalization(uint8_t userDBIndex)

  Summary:
    Convert Auth and Priv  password to the localized Key using SNMPEngineID.

  Description:
    This routine converts MD5 or SHA1 and AES privacy password key
    to localized key using snmpSngineID(RFC- 3414 - section 6).

  Precondition:
    TCPIP_SNMPv3_Initialize() and ProcessVariabels() are called.

  Parameters:
    userDBIndex  - authentication protocol type

  Return Values:
    None

  Remarks:
    None
 */
void SNMPv3USMAuthPrivPswdLocalization(uint8_t userDBIndex);


/****************************************************************************
  Function:
    bool TCPIP_SNMPv3_Notify(SNMP_ID var, SNMP_VAL val, SNMP_INDEX index,uint8_t targetIndex)

  Summary:
    Creates and Sends SNMPv3 TRAP pdu.

  Description:
    This function creates SNMPv3 trap PDU and sends it to previously specified
    remoteHost.

  Precondition:
    TRAP event is triggered.

  Parameters:
    var     - SNMP var ID that is to be used in notification
    val     - Value of var. Only value of uint8_t, uint16_t or uint32_t can be sent.
    index   - Index of var. If this var is a single,index would be 0, or else
              if this var Is a sequence, index could be any value
              from 0 to 127
    targetIndex -index of the 'Snmpv3TrapConfigData' table's security user name
                 for which the TRAP PDU message header to constructed.

  Return Values:
    true    -   if SNMP notification was successful sent.
                This does not guarantee that remoteHost recieved it.
    false   -   Notification sent failed.
                This would fail under following contions:
                1) Given SNMP_BIB_FILE does not exist in file system
                2) Given var does not exist.
                3) Previously given agentID does not exist
                4) Data type of given var is unknown - only
                   possible if file system itself was corrupted.
    SNMPV3_MSG_PRIV_FAIL -encryption of the trap msg failed
    SNMPV3_MSG_AUTH_FAIL - HAMC of the trap msg failed

  Remarks:
    None
  */
bool TCPIP_SNMPv3_Notify(SNMP_ID var, SNMP_VAL val, SNMP_INDEX index,uint8_t targetIndex);


/****************************************************************************
  Function:
    void TCPIP_SNMPV3_PacketProcStubPtrsGet( SNMPV3_PROCESSING_MEM_INFO_PTRS * dynMemInfoPtr);

  Summary:
    Get SNMPv3 packet processing memory pointer.

  Description:
    This function is used to get dynamic memory allocation pointer details which is used for
    SNMPv3 packet processing.

  Precondition:
    TCPIP_SNMP_Initialize() is already called.

  Parameters:
    dynMemInfoPtr  - Dynamic memory pointer for packet processing

  Return Values:
    None.

  Remarks:
    The source code for this routine is found in snmp.c, not snmpv3.c.
*/
void TCPIP_SNMPV3_PacketProcStubPtrsGet( SNMPV3_PROCESSING_MEM_INFO_PTRS * dynMemInfoPtr);

#endif//#ifndef _SNMPV3_H_

