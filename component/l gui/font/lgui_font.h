/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI.h
Purpose     : GUI API include file
---------------------------END-OF-HEADER------------------------------

Attention : Do not modify this file ! If you do, you will not
            be able do update to a later GUI version !

*/
#ifndef  _FONT_H
#define  _FONT_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#include "fontType.h"
/*********************************************************************
*
*            Standard Fonts
*
**********************************************************************

Note: The external declarations for the fonts are now also included in
      this file.
*/

/* Proportional fonts */
extern const GUI_FONT GUI_FontGUI_Font8_1;
extern const GUI_FONT GUI_Font8_ASCII,        GUI_Font8_1;
extern const GUI_FONT GUI_Font10S_ASCII,      GUI_Font10S_1;
extern const GUI_FONT GUI_Font10_ASCII,       GUI_Font10_1;
extern const GUI_FONT GUI_Font13_ASCII,       GUI_Font13_1;
extern const GUI_FONT GUI_Font13B_ASCII,      GUI_Font13B_1;
extern const GUI_FONT GUI_Font13H_ASCII,      GUI_Font13H_1;
extern const GUI_FONT GUI_Font13HB_ASCII,     GUI_Font13HB_1;
extern const GUI_FONT GUI_Font16_ASCII,       GUI_Font16_1,       GUI_Font16_HK,    GUI_Font16_1HK;
extern const GUI_FONT GUI_Font16B_ASCII,      GUI_Font16B_1;
extern const GUI_FONT GUI_Font24_ASCII,       GUI_Font24_1;
extern const GUI_FONT GUI_Font24B_ASCII,      GUI_Font24B_1;
extern const GUI_FONT GUI_Font32_ASCII,       GUI_Font32_1;
extern const GUI_FONT GUI_Font32B_ASCII,      GUI_Font32B_1;

/* Monospaced */
extern const GUI_FONT GUI_Font4x6;
extern const GUI_FONT GUI_Font6x8,            GUI_Font6x9;
extern const GUI_FONT GUI_Font8x8,            GUI_Font8x9;
extern const GUI_FONT GUI_Font8x10_ASCII;
extern const GUI_FONT GUI_Font8x12_ASCII;
extern const GUI_FONT GUI_Font8x13_ASCII,     GUI_Font8x13_1;
extern const GUI_FONT GUI_Font8x15B_ASCII,    GUI_Font8x15B_1;
extern const GUI_FONT GUI_Font8x16,           GUI_Font8x17,       GUI_Font8x18;
extern const GUI_FONT GUI_Font8x16x1x2,       GUI_Font8x16x2x2,   GUI_Font8x16x3x3;

/* Digits */
extern const GUI_FONT GUI_FontD24x32;
extern const GUI_FONT GUI_FontD32;
extern const GUI_FONT GUI_FontD36x48;
extern const GUI_FONT GUI_FontD48;
extern const GUI_FONT GUI_FontD48x64;
extern const GUI_FONT GUI_FontD64;
extern const GUI_FONT GUI_FontD60x80;
extern const GUI_FONT GUI_FontD80;

/* Comic fonts */
extern const GUI_FONT GUI_FontComic18B_ASCII, GUI_FontComic18B_1;
extern const GUI_FONT GUI_FontComic24B_ASCII, GUI_FontComic24B_1;

typedef enum{
		DispMode_Normal = 0,									// 0,正常，覆盖任何已经显示的东西
		DispMode_XOR,													// 1,异或，
		DispMode_Trans,												// 2,透明, 叠加显示在已有内容上
		DispMode_Rev = 1<<2										// 4,反转，
}DispMode_e;

typedef enum{
		AlignFlag_Horizontal	= 3,			// 水平对齐标志 0011
		AlignMode_Left = 0,							// 左对齐				0000
		AlignMode_Right,								// 右对齐				0001
		AlignMode_Center,								// 水平居中			0010
		AlignFlag_Vertical		= 3<<2,		// 垂直对齐标志 1100
		AlignMode_Top  		= 0,					// 顶部对齐			0000
		AlignMode_Bottom 	= 1<<2,				// 底部对齐			0100
		AlignMode_Vcenter = 2<<2				// 垂直居中     1000
}AlignMode_e;

#if defined(__cplusplus)
}     /* Make sure we have C-declarations in C++ programs */
#endif

#endif   /* ifdef GUI_H */

/*************************** End of file ****************************/
