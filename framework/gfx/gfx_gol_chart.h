/**********************************************************************************
    * Module for Microchip Graphics Library
    * GOL Layer
    * Chart
  * *************************************************************************** *
    * File Name: gfx_chart.h
    * Dependencies: None
    * Processor: PIC24F, PIC24H, dsPIC, PIC32
    * Compiler: MPLAB C30, MPLAB C32
    * Linker: MPLAB LINK30, MPLAB LINK32
    * Company: Microchip Technology Inc.
  &#42;
    * Software License Agreement
  &#42;
    * Copyright © 2008 Microchip Technology Inc. All rights reserved.
    * Microchip licenses to you the right to use, modify, copy and
      distribute
    * Software only when embedded on a Microchip microcontroller or
      digital
    * signal controller, which is integrated into your product or third
      party
    * product (pursuant to the sublicense terms in the accompanying
      license
    * agreement).
  &#42;
    * You should refer to the license agreement accompanying this
      Software
    * for additional information regarding your rights and obligations.
  &#42;
    * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF
      ANY
    * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
      WARRANTY
    * OF MERCHANTABILITY, TITLE, NON&#45;INFRINGEMENT AND FITNESS FOR A
      PARTICULAR
    * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
    * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY,
      CONTRIBUTION,
    * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR
      INDIRECT
    * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL,
      SPECIAL,
    * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST
      DATA,
    * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR
      ANY
    * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
      THEREOF),
    * OR OTHER SIMILAR COSTS.
  &#42;
    * Date Comment
  &#42;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    * 4/8/08 ...
  \ \                                                                              
  **********************************************************************************/
#ifndef _CHART_H
    #define _CHART_H

    #include <gfx/gfx_gol.h>
    #include "GenericTypeDefs.h"

/* 
		Chart Terminologies 

Value Axis - This is the vertical range of a chart for normal bar charts and 
			 horizontal range of the chart for horizontally drawn bar charts. 
			 In most cases this axis will represent values ($ amounts), temperatures, 
			 or other numeric data. Definition for Value Axis and Sample Axis 
			 are flipped when chart is drawn horizontally.
Sample Axis - This is the horizontal range of a chart for normal bar charts and 
			  vertical range of the chart for horizontally drawn bar charts.
			  In most cases this axis will represent categories, such as months, 
			  sample segments, or other non-numeric data. Definition for Value Axis 
			  and Sample Axis are flipped when chart is drawn horizontally.
Title  - The text used to define the Title of the chart.
Data Points (or the sample points) These are the individual points where a value 
			 is graphed, as a point on a line, a bar, or a pie slice. 
Data Series - A complete series of data, distinguished by the same color and type of sample point.
Legend - Labels that indicate how each data series is displayed on the chart. 
		 Each color represents a different data series. For pie charts with only one data
		 series shown, each color represent one sector or one one sample point.
Data Sample Range - The scale for the data sample axis. Example: months from 
		January to December. Internally, this range is represented by:
			 Numeric Sequence 1, 2, 3, ... and so on 
			 Alphabet Sequence A, B, C, .. and so on.
Value Range - The scale for the value axis. 
			  Example: range of numbers from the lowest to the highest to be charted. 

*/

/*********************************************************************
* Object States Definition: 
*********************************************************************/
    #define GFX_GOL_CHART_DISABLED 	0x0002      // Bit for disabled state.
    #define GFX_GOL_CHART_LEGEND   	0x0001      // Bit to indicate that legend is to be shown. Usable only when seriesCount > 1.
    #define GFX_GOL_CHART_VALUE    	0x0004      // Bit to indicate that the values of the bar chart data or pie chart data are to be shown
    #define GFX_GOL_CHART_3D_ENABLE    0x0008      // Bit to indicate that bar charts are to be drawn with 3-D effect
    #define GFX_GOL_CHART_PIE          0x0100      // Bit to indicate the chart is type pie. If both PIE and BAR types are set BAR type has higher priority.
    #define GFX_GOL_CHART_BAR  		0x0200      // Bit to indicate the chart is type bar. If both PIE and BAR types are set BAR type has higher priority.
    #define GFX_GOL_CHART_PERCENT  	0x0010      // Bit to indicate that the pie chart will be drawn with percentage values shown for the sample data.
										// For bar chart, if CH_VALUE is set, it toggles the value shown to percentage.
    #define GFX_GOL_CHART_BAR_HOR  	0x0240      // These bits (with CH_BAR bit set), sets the bar chart to be drawn horizontally.
    #define GFX_GOL_CHART_DONUT    	0x0140      // These bits (with CH_PIE bit set), sets the pie chart to be drawn in a donut shape.
    #define GFX_GOL_CHART_NUMERIC  	0x0080      // This bit is used only for bar charts. If this bit is set, it indicates that the
										// bar chart labels for variables are numeric. If this bit is not set, it indicates
										// that the bar chart labels for variables are alphabets.
    #define GFX_GOL_CHART_DRAW_DATA    0x2000      // Bit to indicate data portion of the chart must be redrawn.
    #define GFX_GOL_CHART_DRAW         0x4000      // Bit to indicate chart must be redrawn.
    #define GFX_GOL_CHART_HIDE         0x8000      // Bit to indicate chart must be removed from screen.

/*********************************************************************
* Data Series Show Flag Definitions: 
*********************************************************************/
    #define SHOW_DATA   1               // Macro used to set the data series show flag or indicate that the data series will be shown when the chart is drawn.
    #define HIDE_DATA   0               // Macro used to reset the data series show flag or indicate that the data series will be not be shown when the chart is drawn.

/* Internal Definitions - used to modify some specific rendering characteristics */
    #define CHART_MARGIN       2           // Margin from the edges.
    #define CHART_YGRIDCOUNT   6           // defines the number of grids to be drawn on the y-axis (includes the origin at y).
    #define USE_HORZ_ASCENDING_ORDER    // use ascending order when displaying variables on horizontal mode (bar chart only)
    #define USE_PIE_ENABLE_LABEL        // use labels:  A:10%,30 where each sample is labeled A-Z followed by a colon.

/*********************************************************************
* Overview: Defines a variable for the CHART object. It specifies
*			the number of samples, pointer to the array of samples
*			for the data series and pointer to the next data series. 
*			A member of this structure (show) is used as a flag to 
*			determine if the series is to be drawn or not. Together with
*			the smplStart and smplEnd it will determine what kind of 
*			chart will be drawn.
*
*********************************************************************/
typedef struct
{
    XCHAR   *pSData;    // Pointer to the data series name.
    uint16_t    samples;    // Indicates the number of data samples (or data points) contained in the array specified by pData.
    BYTE    show;       // The flag to indicate if the data series will be shown or not. If this flag is set to SHOW_DATA, the data series will be shown. If HIDE_DATA, the data series will not be shown.
    uint16_t    *pData;     // Pointer to the array of data samples.
    void    *pNextData; // Pointer to the next data series. NULL if no other data series follows.
} DATASERIES;

/*********************************************************************
* Overview: Defines the parameters for the CHART object. 
*							 
*********************************************************************/
typedef struct
{
    XCHAR   *pTitle;            // Pointer to the Title of the chart.
    XCHAR   *pSmplLabel;        // Pointer to the bar chart sample axis label. Depending

    // if the bar chart is drawn vertically or horizontally, the
    // location of the sample will be in the x-axis or y-axis.
    XCHAR   *pValLabel;         // Pointer to the bar chart value axis label. Depending

    // if the bar chart is drawn vertically or horizontally, the
    // location of the sample will be in the x-axis or y-axis.
    short       seriesCount;        // Number of data series that will be displayed when chart is drawn.
    uint16_t        smplStart;          // Start point of data sample range to be displayed (minimum/default value = 1)
    uint16_t        smplEnd;            // End point of data sample range to be displayed.
    uint16_t        valMax;             // Maximum value of a sample that can be displayed.
    uint16_t        valMin;             // Minimum value of a sample that can be displayed.
    uint16_t        perMax;             // Maximum value of the percentage range that can be displayed.
    uint16_t        perMin;             // Minimum value of the percentage range that can be displayed.
    GFX_COLOR   *pColor;            // Pointer to the color table used to draw the chart data.
    void        *pTitleFont;        // Pointer to the font used for the title label of the chart.
    void        *pAxisLabelsFont;   // Pointer to the font used for X and Y axis labels.
    void        *pGridLabelsFont;   // Pointer to the font used for X and Y axis grid labels.
} CHARTPARAM;

/*********************************************************************
* Overview: Defines the parameters required for a chart Object.
*
*********************************************************************/
typedef struct
{
    GFX_GOL_OBJ_HEADER  hdr;                    // Generic header for all Objects (see GFX_OBJ_HEADER).
    CHARTPARAM  prm;                    // Structure for the parameters of the chart.
    DATASERIES  *pChData;               // Pointer to the first chart data series in the link list of data series.	
} GFX_GOL_CHART;

/*********************************************************************
* 	Data Color Table 												
*	- The following macroses defines the default colors used when 
*	  rendering chart data.  
*********************************************************************/
#ifdef USE_PALETTE

    #include "PaletteColorDefines.h"

#else

#if(COLOR_DEPTH >= 8)
    #define CH_CLR0     BRIGHTBLUE()      // Bright Blue
    #define CH_CLR1     BRIGHTRED()       // Bright Red
    #define CH_CLR2     BRIGHTGREEN()     // Bright Green
    #define CH_CLR3     BRIGHTYELLOW()    // Bright Yellow
    #define CH_CLR4     ORANGE()          // Orange
    #define CH_CLR5     BLUE()            // Blue
    #define CH_CLR6     RED()             // Red
    #define CH_CLR7     GREEN()           // Green
    #define CH_CLR8     YELLOW()          // Yellow
    #define CH_CLR9     DARKORANGE()      // Dark Orange
    #define CH_CLR10    LIGHTBLUE()       // Light Blur
    #define CH_CLR11    LIGHTRED()        // Light Red
    #define CH_CLR12    LIGHTGREEN()      // Light Green
    #define CH_CLR13    LIGHTYELLOW()     // Light Yellow
    #define CH_CLR14    LIGHTORANGE()     // Light Orange
    #define CH_CLR15    GOLD()            // Gold
#endif

#if(COLOR_DEPTH == 4)
    #define CH_CLR0     BLACK()
    #define CH_CLR1     GRAY001()
    #define CH_CLR2     GRAY002()
    #define CH_CLR3     GRAY003()
    #define CH_CLR4     GRAY004()
    #define CH_CLR5     GRAY005()
    #define CH_CLR6     GRAY006()
    #define CH_CLR7     GRAY007()
    #define CH_CLR8     GRAY008()
    #define CH_CLR9     GRAY009()
    #define CH_CLR10    GRAY010()
    #define CH_CLR11    GRAY011()
    #define CH_CLR12    GRAY012()
    #define CH_CLR13    GRAY013()
    #define CH_CLR14    GRAY014()
    #define CH_CLR15    WHITE()
#endif

#if(COLOR_DEPTH == 1)
    #define CH_CLR0     WHITE()
    #define CH_CLR1     BLACK()
    #define CH_CLR2     WHITE()
    #define CH_CLR3     BLACK()
    #define CH_CLR4     WHITE()
    #define CH_CLR5     BLACK()
    #define CH_CLR6     WHITE()
    #define CH_CLR7     BLACK()
    #define CH_CLR8     WHITE()
    #define CH_CLR9     BLACK()
    #define CH_CLR10    WHITE()
    #define CH_CLR11    BLACK()
    #define CH_CLR12    WHITE()
    #define CH_CLR13    BLACK()
    #define CH_CLR14    WHITE()
    #define CH_CLR15    BLACK()
#endif

	
	
	
#endif

short       GFX_GOL_ChartDataSeriesSet(GFX_GOL_CHART *pCh, uint16_t seriesNum, BYTE status);

/*********************************************************************
* Function: GFX_GOL_CHART  *GFX_GOL_ChartCreate( uint16_t ID, short left, short top,
*							  short right, short bottom, 
*				  			  uint16_t state, DATASERIES *pData, 
*							  CHARTPARAM *pParam, GFX_GOL_OBJ_SCHEME *pScheme)
*				  
* Overview: This function creates a CHART object with the parameters given. 
*			It automatically attaches the new object into a global linked list of 
*			objects and returns the address of the object.
*
* PreCondition: none
*
* Input: ID - Unique user defined ID for the object instance.
*        left - Left most position of the object.
* 		 top - Top most position of the object. 
*		 right - Right most position of the object.
*		 bottom - Bottom most position of the object.
*        state - Sets the initial state of the object.
*        pData - Pointer to the data for the contents of the chart. NULL can
*				 be assigned initially when creating the object. 
*        pParam - Pointer to the chart parameters. NULL can be assigned initially 
*				  when creating the object and the chart parameters can be 
*				  populated using the API provided. 
*        pScheme - Pointer to the style scheme used. When set to NULL,
*				   the default style scheme will be used.
*
* Output: Returns the pointer to the object created.
*
* Example:
*   <CODE> 
*
*	extern const FONT_FLASH GOLSmallFont;
*	extern const FONT_FLASH GOLMediumFont; 		
*
*   // Note that strings are declared as such to cover cases 
*	// where XCHAR type is declared as short (2 bytes).
*	XCHAR ChTitle[]     = {'E','x','a','m','p','l','e',0};
*	XCHAR SampleName[]  = {'C','a','t','e','g','o','r','y',0};
*	XCHAR ValueName[]   = {'#','H','i','t','s',0};
*	XCHAR SeriesName[2] = {
*						   {'V','1',0},
*						   {'V','2',0},
*				 		  };
*	V1Data[2] = { 50, 100};
*	V2Data[2] = { 5,  10};
*	
*	GFX_OBJ_SCHEME	*pScheme;
*	CHART		*pChart;
*	CHARTPARAM	 Contents;
*	uint16_t		 state;
*	
*		pScheme = GFX_OBJ_SchemeCreate();
*		state = CH_BAR|CH_DRAW|CH_BAR_HOR;	// GFX_PRIM_BarDraw Chart to be drawn with horizontal orientation
*
*
*		pChart = ChCreate(0x01,                         // ID 
*						  0, 0,                         // dimensions
*						  GFX_PRIM_GetMaxX(),
*						  GFX_PRIM_GetMaxY(),    
*			  			  state,                        // state of the chart
*			  			  NULL, 						// data not initialized yet
*			  			  NULL, 						// no parameters yet
*			  			  pScheme);						// style scheme used
*
*		if (pMyChart == NULL)							// check if chart was allocated memory
*			return 0;
*
*		ChSetTitleFont(pChart, (void*)&GOLMediumFont);
*		ChSetTitle(pChart, ChTitle);					// set the title
*		
*		// set the grid labels and axis labels font	
*		ChSetGridLabelFont(pChart, (void*)&GOLSmallFont);
*		ChSetAxisLabelFont(pChart, (void*)&GOLSmallFont);
*		
*		// set the labels for the X and Y axis
*		ChSetSampleLabel(pChart, (XCHAR*)SampleName);
*		ChSetValueLabel(pChart, (XCHAR*)ValueName);
*		
*		ChAddDataSeries(pChart, 2, V1Data, (XCHAR*)SeriesName[0]); 
*		ChAddDataSeries(pChart, 2, V2Data, (XCHAR*)SeriesName[1]);
*
*		// set the range of the sample values
*		ChSetValueRange(pChart, 0, 100);
*
*		// show all two samples to be displayed (start = 1, end = 2)
*		ChSetSampleRange(pChart, 1, 2);		
*		
*		GFX_OBJ_Draw();										// draw the chart
*
*	</CODE> 
*
* Side Effects: none
*
********************************************************************/
GFX_GOL_CHART       *GFX_GOL_ChartCreate
            (
                uint16_t        ID,
                short       left,
                short       top,
                short       right,
                short       bottom,
                uint16_t        state,
                DATASERIES  *pData,
                CHARTPARAM  *pParam,
                GFX_GOL_OBJ_SCHEME  *pScheme
            );

/*********************************************************************
* Function: GFX_GOL_ChartDataSeriesAdd(GFX_OBJ_CHART *pCh, uint16_t nSamples, uint16_t *pData, XCHAR *pName)
*
* Overview: This function creates a DATASERIES object and 
*			populates the structure with the given parameters.
*
* PreCondition: none
*
* Input: pCh - Pointer to the chart object.
*        nSamples - The number of samples or data points.
* 		 pData - Pointer to the array of samples or data points. 
*		 pName - Pointer to the string used to label the data series.
*
* Output: Returns the pointer to the data variable (DATASERIES) object created.
*		  If NULL is returned, the addition of the new object failed due to
*		  not enough memory for the object.
*
* Example: See ChCreate() example.
*
* Side Effects: Appends to the list of DATASERIES that the chart is operating on. 
*				By default, the show flag of the newly added data series is set to 
*				SHOW_DATA or enabled.
*
********************************************************************/
DATASERIES  *GFX_GOL_ChartDataSeriesAdd(GFX_GOL_CHART *pCh, uint16_t nSamples, uint16_t *pData, XCHAR *pName);

/*********************************************************************
* Function: void GFX_GOL_ChartDataSeriesFree(void *pObj)
*
* Overview: This function removes DATASERIES object from the list of 
*			DATASERIES objects and frees the memory used of that removed object.
*
* PreCondition: none
*
* Input: pCh - Pointer to the chart object.
*
* Output: none.
*
*
* Example:
*   <CODE> 
*
*	void ClearChartData(CHART *pCh) {
*       if(pCh->pChData != NULL)
*			// remove the all data series
*           ChFreeDataSeries(pCh;
*   }
*	</CODE> 
*
* Side Effects: none.
*
********************************************************************/
void GFX_GOL_ChartDataSeriesFree(void *pObj);

/*********************************************************************
* Function: GFX_GOL_ChartDataSeriesRemove(CHART *pCh, uint16_t number)
*
* Overview: This function removes DATASERIES object from the list of 
*			DATASERIES objects and frees the memory used of that removed object.
*			The position of the object to be removed is specified by the number 
*		 	parameter. If the list has only one member, it removes the member 
*			regardless of the number given.
*
* PreCondition: none
*
* Input: pCh - Pointer to the chart object.
*        number - The position of the object to be removed in the list where
*				  the first object in the list is assigned a value of 1.
*				  If this parameter is set to zero, the whole list of 
*				  DATA_SERIES is removed.
*
* Output: none.
*
*
* Example:
*   <CODE> 
*
*	void ClearChartData(CHART *pCh) {
*       if(pCh->pChData != NULL)
*			// remove the all data series
*           ChRemoveDataSeries(pCh, 0);
*   }
*	</CODE> 
*
* Side Effects: none.
*
********************************************************************/
void        GFX_GOL_ChartDataSeriesRemove(GFX_GOL_CHART *pCh, uint16_t number);

/**************************************************************************
  Description:
    Macros: short GFX_GOL_ChartShowSeriesSet(CHART *pCh, uint16_t
    seriesNum)
    
    This macro sets the specified data series number show flag to be set to
    SHOW_DATA.
  Conditions:
    none
  Input:
    pCh -        Pointer to the chart object.
    seriesNum -  The data series number that will be modified. If this
                 number is zero, all the entries' flag in the list will be
                 set to SHOW_DATA.
  Return:
    \Returns the same passed number if successful otherwise -1 if
    unsuccessful.
  Example:
    <code>
    // from the example in  ChCreate() we change the items to be shown when
    // GFX_OBJ_Draw() is called.
    
    // reset all data series to be HIDE_DATA
    ChHideSeries(pMyChart, 0);
    // set data series 1 (V1Data) to be shown
    ChShowSeries(pMyChart, 1);
    // draw the chart
    GFX_OBJ_Draw();
    .....
    </code>
    \*
  Side Effects:
    none                                                                   
  **************************************************************************/
    #define GFX_GOL_ChartShowSeriesSet(pCh, seriesNum)    (GFX_GOL_ChartDataSeriesSet(pCh, seriesNum, SHOW_DATA))

/**************************************************************************
  Description:
    Macros: GFX_GOL_ChartSeriesHide(CHART *pCh, uint16_t seriesNum)
    
    This macro sets the specified data series number show flag to be set to
    HIDE_DATA.
  Conditions:
    none
  Input:
    pCh -        Pointer to the chart object.
    seriesNum -  The data series number that will be modified. If this
                 number is zero, all the entries' flag in the list will be
                 set to HIDE_DATA.
  Return:
    \Returns the same passed number if successful otherwise -1 if
    unsuccessful.
  Example:
    See ChShowSeries() example.
  Side Effects:
    none                                                                   
  **************************************************************************/
    #define GFX_GOL_ChartSeriesHide(pCh, seriesNum)    (GFX_GOL_ChartDataSeriesSet(pCh, seriesNum, HIDE_DATA))

/*********************************************************************
* Macros: GFX_GOL_ChartShowSeriesCountGet(pCh)
*
* Overview: This macro shows the number of data series that has 
*			its show flag set to SHOW_DATA
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the number of data series with its show flag set to 
*		  SHOW_DATA.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartShowSeriesCountGet(pCh)   (pCh->prm.seriesCount)

/*********************************************************************
* Macros: GFX_GOL_ChartShowSeriesStatusGet(pDSeries)
*
* Overview: This macro returns the show ID status of the DATASERIES.
*
* PreCondition: none
*
* Input: pDSeries - Pointer to the data series(DATASERIES) that is 
*					being checked.
* 
* Output: Returns the status of the show flag.
*		  1 - (SHOW_DATA) means that the show status flag is set.
*		  0 - (HIDE_DATA) means that the show status flag is not set.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartShowSeriesStatusGet(pDSeries) (pDSeries->show)

/*********************************************************************
* Macros: GFX_GOL_ChartValueMaxGet(pCh)
*
* Overview: This macro returns the current maximum value that will
*			be drawn for bar charts.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the maximum value set when bar charts are drawn.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartValueMaxGet(pCh)  (pCh->prm.valMax)

/*********************************************************************
* Macros: GFX_GOL_ChartValueMinGet(pCh)
*
* Overview: This macro returns the current minimum value that will
*			be drawn for bar charts.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the minimum value set when bar charts are drawn.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartValueMinGet(pCh)  (pCh->prm.valMin)

/*********************************************************************
* Function: GFX_GOL_ChartValueRangeSet(GFX_GOL_CHART *pCh, uint16_t min, uint16_t max)
*
* Overview: This function sets the minimum and maximum range of values 
*           that the bar chart will show.
*			The criteria is that min <= max.
*
* PreCondition: none
*
* Input: pCh - Pointer to the chart object.
*        min - Minimum value that will be displayed in the bar chart.
*		 max - Maximum value that will be displayed in the bar chart.
*
* Output: none.
*
* Side Effects: none.
*
********************************************************************/
void    GFX_GOL_ChartValueRangeSet(GFX_GOL_CHART *pCh, uint16_t min, uint16_t max);

/*********************************************************************
* Function: GFX_GOL_ChartValueRangeGet(pCh)
*
* Overview: This macro gets the current range for bar charts. 
*			The value returned is calculated from the current (valMax - valMin) set.
*			To get the minimum use ChGetValueMin() and to get the 
*           maximum use ChGetValueMax().
*
* PreCondition: none
*
* Input: pCh - Pointer to the chart object.
*
* Output: Value range computed from valMax-valMin.
*
* Side Effects: none.
*
********************************************************************/
    #define GFX_GOL_ChartValueRangeGet(pCh)    (pCh->prm.valMax - pCh->prm.valMin)

/*********************************************************************
* Macros: ChGetPercentMax(pCh)
*
* Overview: This macro returns the current maximum value of the percentage
* 			range that will be drawn for bar charts when CH_PERCENTAGE bit state
*			is set.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the maximum percentage value set when bar charts are drawn.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartPercentMaxGet(pCh)    (pCh->prm.perMax)

/*********************************************************************
* Macros: ChGetPercentMin(pCh)
*
* Overview: This macro returns the current minimum value of the percentage
* 			range that will be drawn for bar charts when CH_PERCENTAGE bit state
*			is set.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the minimum percentage value when bar charts are drawn.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartPercentMinGet(pCh)    (pCh->prm.perMin)

/*********************************************************************
* Function: GFX_GOL_ChartPercentRangeSet(GFX_GOL_CHART *pCh, uint16_t min, uint16_t max)
*
* Overview: This function sets the minimum and maximum range of 
*			percentage that the bar chart will show. 
*			The criteria is that min <= max.
*			This affects bar charts only and CH_PERCENTAGE bit state is set.
*
* PreCondition: none
*
* Input: pCh - Pointer to the chart object.
*        min - Minimum percentage value that will be displayed in the bar chart.
*		 max - Maximum percentage value that will be displayed in the bar chart.
*
* Output: none.
*
* Side Effects: none.
*
********************************************************************/
void    GFX_GOL_ChartPercentRangeSet(GFX_GOL_CHART *pCh, uint16_t min, uint16_t max);

/*********************************************************************
* Function: ChGetPercentRange(pCh)
*
* Overview: This macro gets the percentage range for bar charts. 
*			The value returned is calculated from percentage max - min.
*			To get the minimum use ChGetPercentMin() and to get the 
*           maximum use ChGetPercentMax().
*
* PreCondition: none
*
* Input: pCh - Pointer to the chart object.
*
* Output: Percentage range computed from max-min.
*
* Side Effects: none.
*
********************************************************************/
    #define GFX_GOL_ChartPercentRangeGet(pCh)  (pCh->prm.perMax - pCh->prm.perMin)

/*********************************************************************
* Function: GFX_GOL_ChartSetSampleRange(GFX_GOL_CHART *pCh, uint16_t start, uint16_t end)
*
* Overview: This function sets the sample start and sample end when 
*			drawing the chart. Together with the data series' SHOW_DATA
*			flags the different way of displaying the chart data is achieved.
*
*	<TABLE>
*    	Start & End Value		  	The # of Data Series Flag Set	Chart Description
*		##################			#############################	###########
*		Start <= End			  	1								Show the data indicated by Start and End points of the DATASERIES with the flag set 
*		Start  = End			  	1								Show the data indicated by Start or End points of the DATASERIES with the flag set 
*		Start, End = don't care	  	> 1								Show the data indicated by Start point of the DATASERIES with the flag set. Each samples of all checked data series are grouped together according to sample number.
*	</TABLE>
*
* PreCondition: none
*
* Input: pCh - Pointer to the chart object.
*        start - Start point of the data samples to be displayed.
*		 end - End point of the data samples to be displayed.
*
* Output: none.
*
* Example: See ChCreate() example.
*
* Side Effects: none.
*
********************************************************************/
void    GFX_GOL_ChartSampleRangeSet(GFX_GOL_CHART *pCh, uint16_t start, uint16_t end);

/*********************************************************************
* Function: ChGetSampleRange(pCh)
*
* Overview: This macro gets the sample range for pie or bar charts. 
*			The value returned is calculated from smplEnd - smplStart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the chart object.
*
* Output: Sample range computed from smplEnd - smplStart.
*
* Side Effects: none.
*
********************************************************************/
    #define GFX_GOL_ChartSampleRangeGet(pCh)   (GFX_GOL_ChartSampleEndGet(pCh) - GFX_GOL_ChartSampleStartGet(pCh))

/*********************************************************************
* Macros:  GFX_GOL_ChartSampleStartGet(pCh)
*
* Overview: This macro returns the sampling start value.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
*
* Output: Returns the sample start point.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartSampleStartGet(pCh)   (((GFX_GOL_CHART *)pCh)->prm.smplStart)

/*********************************************************************
* Macros:  GFX_GOL_ChartSampleEndGet(pCh)
*
* Overview: This macro returns the sampling end value.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
*
* Output: Returns the sample end point.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartSampleEndGet(pCh) ((GFX_GOL_CHART *)pCh)->prm.smplEnd

/*********************************************************************
* Macros: GFX_GOL_ChartTitleSet(pCh, pNewTitle)
*
* Overview: This macro sets the address of the current 
*			text string used for the title of the chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
*   	 pNewTitle - pointer to the string to be used as a title
* 				     of the chart.
* 
* Output: none.
*
* Example: See ChCreate() example.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartTitleSet(pCh, pNewTitle)  (((GFX_GOL_CHART *)pCh)->prm.pTitle = pNewTitle)

/*********************************************************************
* Macros: GFX_GOL_ChartTitleGet(pCh)
*
* Overview: This macro returns the address of the current 
*			text string used for the title of the chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the pointer to the current title text used.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartTitleGet(pCh) (((GFX_GOL_CHART *)pCh)->prm.pTitle)

/*********************************************************************
* Macros: GFX_GOL_ChartAxisLabelFontSet(pCh, pNewFont)
*
* Overview: This macro sets the location of the font used for
*			the X and Y axis labels of the chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
*		 pNewFont - Pointer to the font used.
* 
* Output: none.
*
* Example: See ChCreate() example.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartAxisLabelFontSet(pCh, pNewFont)   (((GFX_GOL_CHART *)pCh)->prm.pAxisLabelsFont = pNewFont)

/*********************************************************************
* Macros: GFX_GOL_ChartAxisLabelFontGet(pCh)
*
* Overview: This macro returns the location of the font used for
*			the X and Y axis labels of the chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the address of the current font used for the title text.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartAxisLabelFontGet(pCh) (((GFX_GOL_CHART *)pCh)->prm.pAxisLabelsFont)

/*********************************************************************
* Macros: GFX_GOL_ChartGridLabelFontSet(pCh, pNewFont)
*
* Overview: This macro sets the location of the font used for
*			the X and Y axis grid labels of the chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
*		 pNewFont - Pointer to the font used.
* 
* Output: none.
*
* Example: See ChCreate() example.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartGridLabelFontSet(pCh, pNewFont)   (((GFX_GOL_CHART *)pCh)->prm.pGridLabelsFont = pNewFont)

/*********************************************************************
* Macros: GFX_GOL_ChartGridLabelFontGet(pCh)
*
* Overview: This macro returns the location of the font used for
*			the X and Y axis grid labels of the chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the address of the current font used for the title text.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartGridLabelFontGet(pCh) (((GFX_GOL_CHART *)pCh)->prm.pGridLabelsFont)

/*********************************************************************
* Macros: GFX_GOL_ChartTitleFontSet(pCh, pNewFont)
*
* Overview: This macro sets the location of the font used for
*			the title of the chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
*		 pNewFont - Pointer to the font used.
* 
* Output: none.
*
* Example: See ChCreate() example.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartTitleFontSet(pCh, pNewFont)   (((GFX_GOL_CHART *)pCh)->prm.pTitleFont = pNewFont)

/*********************************************************************
* Macros: GFX_GOL_ChartTitleFontGet(pCh)
*
* Overview: This macro returns the location of the font used for
*			the title of the chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the address of the current font used for the title text.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartTitleFontGet(pCh) (((GFX_GOL_CHART *)pCh)->prm.pTitleFont)

/*********************************************************************
* Macros: GFX_GOL_ChartSampleLabelSet(pCh, pNewXLabel)
*
* Overview: This macro sets the address of the current 
*			text string used for the sample axis label of the bar chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
*   	 pNewXLabel - pointer to the string to be used as an sample 
* 				      axis label of the bar chart.
* 
* Output: none.
*
* Example: See ChCreate() example.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartSampleLabelSet(pCh, pNewXLabel)   (((GFX_GOL_CHART *)pCh)->prm.pSmplLabel = pNewXLabel)

/*********************************************************************
* Macros: GFX_GOL_ChartSampleLabelGet(pCh)
*
* Overview: This macro returns the address of the current 
*			text string used for the sample axis label of the bar chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the pointer to the current sample axis label text 
*		  of the bar chart.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartSampleLabelGet(pCh)   (((GFX_GOL_CHART *)pCh)->prm.pSmplLabel)

/*********************************************************************
* Macros: GFX_GOL_ChartValueLabelSet(pCh, pNewYLabel)
*
* Overview: This macro sets the address of the current 
*			text string used for the value axis label of the bar chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
*   	 pNewYLabel - pointer to the string to be used as an value 
* 				     axis label of the bar chart.
* 
* Output: none.
*
* Example: See ChCreate() example.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartValueLabelSet(pCh, pNewValueLabel)    (((GFX_GOL_CHART *)pCh)->prm.pValLabel = pNewValueLabel)

/*********************************************************************
* Macros: GFX_GOL_ChartValueLabelGet(pCh)
*
* Overview: This macro returns the address of the current 
*			text string used for the value axis label of the bar chart.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the pointer to the current value axis label text 
*	      of the bar chart.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartValueLabelGet(pCh)    (((GFX_GOL_CHART *)pCh)->prm.pValLabel)

/*********************************************************************
* Macros: GFX_GOL_ChartColorTableSet(pCh, pNewTable)
*
* Overview: This macro sets the color table used to draw the data
*			in pie and bar charts.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
*		 pNewTable - Pointer to the color table that will be used.
* 
* Output: none.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartColorTableSet(pCh, pNewTable) ((((GFX_GOL_CHART *)pCh)->prm.pColor) = pNewTable)

/*********************************************************************
* Macros: GFX_GOL_ChartColorTableGet(pCh)
*
* Overview: This macro returns the current color table used for 
*			the pie and bar charts.
*
* PreCondition: none
*
* Input: pCh - Pointer to the object.
* 
* Output: Returns the address of the color table used.
*
* Side Effects: none
*
********************************************************************/
    #define GFX_GOL_ChartColorTableGet(pCh)    (((GFX_GOL_CHART *)pCh)->prm.pColor)

/*********************************************************************
* Function: GFX_GOL_ChartActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
*
* Overview: This function evaluates the message from a user if the 
*			message will affect the object or not. The table below enumerates 
*			the translated messages for each event of the touch screen 
*			and keyboard inputs.
*
*	<TABLE>
*    	Translated Message   Input Source  Events         							Description
*     	##################   ############  ######         							###########
*		CH_MSG_SELECTED		 Touch Screen  EVENT_PRESS, EVENT_RELEASE, EVENT_MOVE	If events occurs and the x,y position falls in the area of the chart.
*		OBJ_MSG_INVALID		 Any		   Any			  							If the message did not affect the object.							 
*	</TABLE>
*
* PreCondition: none
*
* Input: pCh    - The pointer to the object where the message will be
*				 evaluated to check if the message will affect the object.
*        pMsg  - Pointer to the message struct containing the message from 
*        		 the user interface.
*
* Output: Returns the translated message depending on the received GOL message:
*		- CH_MSG_SELECTED – Chart area is selected
* 		- OBJ_MSG_INVALID – Chart is not affected
*
* Output: none.
*
* Side Effects: none
*
********************************************************************/
uint16_t    GFX_GOL_ChartActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg);

/*********************************************************************
* Function: uint16_t GFX_GOL_ChartDraw(void *pObj)
*
* Overview: This function renders the object on the screen using 
* 			the current parameter settings. Location of the object is 
*			determined by the left, top, right and bottom parameters. 
*			The colors used are dependent on the state of the object. 
*			The font used is determined by the style scheme set.
*			
*			The colors of the bars of the bar chart or sectors of the 
*			pie chart can be the default color table  or user defined 
*			color table set by ChSetColorTable() function.
*			
*			When rendering objects of the same type, each object 
*			must be rendered completely before the rendering of the 
*			next object is started. This is to avoid incomplete 
*			object rendering.
*
* PreCondition: Object must be created before this function is called.
*
* Input: pCh - Pointer to the object to be rendered.
*        
* Output: Returns the status of the drawing
*		  - 1 - If the rendering was completed and 
*		  - 0 - If the rendering is not yet finished. 
*		  Next call to the function will resume the 
*		  rendering on the pending drawing state.
*
* Side Effects: none.
*
********************************************************************/
uint16_t GFX_GOL_ChartDraw(void *pObj);
#endif // _CHART_H
