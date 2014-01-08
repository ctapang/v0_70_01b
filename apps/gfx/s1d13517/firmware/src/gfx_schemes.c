/*****************************************************************************
 * Microchip Graphics Library Demo Application
 * This program shows how to use the Graphics Objects Layer.
 *****************************************************************************
 * File Name:       main_screen.c
 * Dependencies:    See Includes Section
 * Processor:       PIC24, PIC32
 * Compiler:       	MPLAB C30 V3.00, MPLAB C32
 * Linker:          MPLAB LINK30, MPLAB LINK32
 * Company:         Microchip Technology Incorporated
 *
 *
 * Copyright © 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 *****************************************************************************/

/*****************************************************************************
 * SECTION: Includes
 *****************************************************************************/
#include "app.h"
#include "gfx_schemes.h"
/*****************************************************************************
 * SECTION: Defines
 *****************************************************************************/
#define RED4        GFX_RGBConvert(139, 0, 0)
#define FIREBRICK1  GFX_RGBConvert(255, 48, 48)

#define ALPHA_VAL   50
/*****************************************************************************
 * SECTION: Variables
 *****************************************************************************/
static GFX_GOL_OBJ_SCHEME      *altScheme;                                 // alternative style scheme
static GFX_GOL_OBJ_SCHEME      *altTScheme;                                // alternative style scheme
       GFX_GOL_OBJ_SCHEME      *altBTScheme;                                // alternative style scheme
static GFX_GOL_OBJ_SCHEME      *navScheme;                                 // style scheme for the navigation
static GFX_GOL_OBJ_SCHEME      *redScheme;                                 // alternative red style scheme
static GFX_GOL_OBJ_SCHEME      *greenScheme;                               // alternative green style scheme
static GFX_GOL_OBJ_SCHEME      *yellowScheme;                              // alternative yellow style scheme
static GFX_GOL_OBJ_SCHEME      *redTScheme;                                // alternative red style scheme
static GFX_GOL_OBJ_SCHEME      *greenTScheme;                              // alternative green style scheme
static GFX_GOL_OBJ_SCHEME      *yellowTScheme;                             // alternative yellow style scheme


static GFX_SCHEMES selectedScheme = GFX_SCHEME_1;
static GFX_GOL_OBJ_SCHEME *selectableSchemes[NUM_GFX_SCHEMES];
static GFX_GOL_OBJ_SCHEME *selectableTSchemes[NUM_GFX_SCHEMES];
/*****************************************************************************
 * void GFX_SchemeInit(void)
 *****************************************************************************/
void GFX_SchemeInit(void)
{
    // create the the style schemes
    navScheme = GFX_GOL_SchemeCreate();      // alternative scheme for the navigate buttons
    altScheme = GFX_GOL_SchemeCreate();      // create alternative 1 style scheme
    altTScheme = GFX_GOL_SchemeCreate();     // create alternative 5 style scheme
    redScheme = GFX_GOL_SchemeCreate();      // create red style scheme
    greenScheme = GFX_GOL_SchemeCreate();    // create green style scheme
    yellowScheme = GFX_GOL_SchemeCreate();   // create yellow style scheme
    redTScheme = GFX_GOL_SchemeCreate();      // create red style scheme
    greenTScheme = GFX_GOL_SchemeCreate();    // create green style scheme
    yellowTScheme = GFX_GOL_SchemeCreate();   // create yellow style schemeavigate buttons
    altBTScheme =GFX_GOL_SchemeCreate();

    navScheme->AlphaValue = ALPHA_VAL;
	
    altScheme->Color0 = GFX_RGBConvert(0x4C, 0x8E, 0xFF);
    altScheme->Color1 = GFX_RGBConvert(255, 102, 0);
    altScheme->EmbossDkColor = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altScheme->EmbossLtColor = GFX_RGBConvert(0xA9, 0xDB, 0xEF);
    altScheme->ColorDisabled = GFX_RGBConvert(0xD4, 0xE1, 0xF7);
    altScheme->TextColor1 = BLUE;
    altScheme->TextColor0 = GFX_RGBConvert(255, 102, 0);
    altScheme->TextColorDisabled = GFX_RGBConvert(0xB8, 0xB9, 0xBC);
    altScheme->fillStyle = GFX_FILL_STYLE_GRADIENT_DOWN;
    altScheme->gradientStartColor = WHITE;
    altScheme->gradientEndColor = GFX_RGBConvert(0x4C, 0x8E, 0xFF);
    //altScheme->gradientScheme.length = 100;
    altScheme->AlphaValue = ALPHA_VAL;
    altScheme->pFont = (GFX_RESOURCE_HDR*)&GOLSmallFont;

    altTScheme->Color0 = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altTScheme->Color1 = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altTScheme->EmbossDkColor = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altTScheme->EmbossLtColor = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altTScheme->ColorDisabled = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altTScheme->CommonBkColor = BLUE;
    altTScheme->TextColor1 = BLUE;
    altTScheme->TextColor0 = GFX_RGBConvert(255, 102, 0);
    altTScheme->TextColorDisabled = GFX_RGBConvert(0xB8, 0xB9, 0xBC);
    altTScheme->AlphaValue = ALPHA_VAL;
    altTScheme->pFont = (GFX_RESOURCE_HDR*)&GOLSmallFont;

    altBTScheme->Color0 = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altBTScheme->Color1 = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altBTScheme->EmbossDkColor = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altBTScheme->EmbossLtColor = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altBTScheme->ColorDisabled = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altBTScheme->CommonBkColor = BLUE;
    altBTScheme->TextColor1 = BLUE;
    altBTScheme->TextColor0 = GFX_RGBConvert(255, 102, 0);
    altBTScheme->TextColorDisabled = GFX_RGBConvert(0xB8, 0xB9, 0xBC);
    altBTScheme->AlphaValue = ALPHA_VAL;
    altBTScheme->pFont = (GFX_RESOURCE_HDR*)&Large;

    redScheme->Color0 = GFX_RGBConvert(0xCC, 0x00, 0x00);
    redScheme->Color1 = RED;
    redScheme->EmbossDkColor = RED4;
    redScheme->EmbossLtColor = FIREBRICK1;
    redScheme->TextColor0 = GFX_RGBConvert(0xC8, 0xD5, 0x85);
    redScheme->TextColor1 = BLACK;
    redScheme->AlphaValue = ALPHA_VAL;
    redScheme->gradientStartColor = WHITE;
    redScheme->gradientEndColor = GFX_RGBConvert(0xCC, 0x00, 0x00);
//    redScheme->gradientScheme.length = 50;
    redScheme->pFont = (GFX_RESOURCE_HDR*)&GOLSmallFont;
 
    redTScheme->Color0 = RED4;
    redTScheme->Color1 = RED4;
    redTScheme->EmbossDkColor = RED4;
    redTScheme->EmbossLtColor = RED4;
    redTScheme->TextColor0 = RED4;
    redTScheme->TextColor1 = RED4;
    redTScheme->gradientStartColor = WHITE;
    redTScheme->gradientEndColor = GFX_RGBConvert(0xCC, 0x00, 0x00);
  //  redTScheme->gradientScheme.length = 50;
    redTScheme->AlphaValue = ALPHA_VAL;
    redTScheme->pFont = (GFX_RESOURCE_HDR*)&GOLSmallFont;
       
    greenScheme->Color0 = GFX_RGBConvert(0x23, 0x9E, 0x0A);
    greenScheme->Color1 =  BRIGHTGREEN;
    greenScheme->EmbossDkColor = GREEN;
    greenScheme->EmbossLtColor = GREEN;
    greenScheme->TextColor0 = GFX_RGBConvert(0xDF, 0xAC, 0x83);
    greenScheme->TextColor1 = BLACK;
    greenScheme->AlphaValue = ALPHA_VAL;
    greenScheme->gradientStartColor = WHITE;
    greenScheme->gradientEndColor = GFX_RGBConvert(0x23, 0x9E, 0x0A);
 //   greenScheme->gradientScheme.length = 50;
    greenScheme->pFont = (GFX_RESOURCE_HDR*)&GOLSmallFont;

    greenTScheme->Color0 = GREEN;
    greenTScheme->Color1 = GREEN;
    greenTScheme->EmbossDkColor = GREEN;
    greenTScheme->EmbossLtColor = GREEN;
    greenTScheme->TextColor0 = GREEN;
    greenTScheme->TextColor1 = GREEN;
    greenTScheme->AlphaValue = ALPHA_VAL;
    greenTScheme->pFont = (GFX_RESOURCE_HDR*)&GOLSmallFont;
        
    yellowScheme->Color0 = YELLOW;
    yellowScheme->Color1 = YELLOW;
    yellowScheme->EmbossDkColor = GFX_RGBConvert(0xFF, 0x94, 0x4C);
    yellowScheme->EmbossLtColor = GFX_RGBConvert(0xFD, 0xFF, 0xB2);
    yellowScheme->TextColor0 = GFX_RGBConvert(0xAF, 0x34, 0xF3);
    yellowScheme->TextColor1 = RED;
    yellowScheme->AlphaValue = ALPHA_VAL;
    yellowScheme->gradientStartColor = WHITE;
    yellowScheme->gradientEndColor = YELLOW;
//    yellowScheme->gradientScheme.length = 50;
    yellowScheme->pFont = (GFX_RESOURCE_HDR*)&GOLSmallFont;

    yellowTScheme->Color0 = GFX_RGBConvert(0xFF, 0x94, 0x4C);
    yellowTScheme->Color1 = GFX_RGBConvert(0xFF, 0x94, 0x4C);
    yellowTScheme->EmbossDkColor = GFX_RGBConvert(0xFF, 0x94, 0x4C);
    yellowTScheme->EmbossLtColor = GFX_RGBConvert(0xFF, 0x94, 0x4C);
    yellowTScheme->TextColor0 = GFX_RGBConvert(0xFF, 0x94, 0x4C);
    yellowTScheme->TextColor1 = GFX_RGBConvert(0xFF, 0x94, 0x4C);
    yellowTScheme->AlphaValue = ALPHA_VAL;
    yellowTScheme->pFont = (GFX_RESOURCE_HDR*)&GOLSmallFont;
    
    selectableSchemes[GFX_SCHEME_1] = altScheme;
    selectableSchemes[GFX_SCHEME_2] = redScheme;
    selectableSchemes[GFX_SCHEME_3] = greenScheme;
    selectableSchemes[GFX_SCHEME_4] = yellowScheme;

    selectableTSchemes[GFX_SCHEME_1] = altTScheme;
    selectableTSchemes[GFX_SCHEME_2] = redTScheme;
    selectableTSchemes[GFX_SCHEME_3] = greenTScheme;
    selectableTSchemes[GFX_SCHEME_4] = yellowTScheme;
}
/*****************************************************************************
 * void GFX_SchemeSetCurrentScheme(GFX_SCHEMES scheme)
 *****************************************************************************/
void GFX_SchemeSetCurrentSchemeIdx(GFX_SCHEMES scheme)
{
    selectedScheme = scheme;
}
/*****************************************************************************
 * GFX_SCHEMES GFX_SchemeGetCurrentSchemeIdx(void)
 *****************************************************************************/
GFX_SCHEMES GFX_SchemeGetCurrentSchemeIdx(void)
{
    return selectedScheme;
}
/*****************************************************************************
 * GFX_GOL_SCHEME *GFX_SchemeGetCurrentScheme(void)
 *****************************************************************************/
GFX_GOL_OBJ_SCHEME *GFX_SchemeGetCurrentScheme(void)
{
    return selectableSchemes[selectedScheme];
}
/*****************************************************************************
 * GFX_GOL_SCHEME *GFX_SchemeGetCurrentTScheme(void)
 *****************************************************************************/
GFX_GOL_OBJ_SCHEME *GFX_SchemeGetCurrentTScheme(void)
{
    return selectableTSchemes[selectedScheme];
}
/*****************************************************************************
 * GFX_GOL_SCHEME *GFX_SchemeGetDefaultScheme(void)
 *****************************************************************************/
GFX_GOL_OBJ_SCHEME *GFX_SchemeGetDefaultScheme(void)
{
    return altScheme;
}
/*****************************************************************************
 * GFX_GOL_SCHEME *GFX_SchemeGetDefaultScheme(void)
 *****************************************************************************/
void GFX_SchemeSetAlpha(short level)
{
    GFX_SCHEMES idx;

    level = Percentage2Alpha(level);

   for(idx = GFX_SCHEME_1; idx < NUM_GFX_SCHEMES; idx++)
   {
        selectableSchemes[idx]->AlphaValue = level;
        selectableTSchemes[idx]->AlphaValue = level;
   }
}
