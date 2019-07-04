/**
  ******************************************************************************
  * @file    G_LCD_interface.h
  * @author  cat_li
  * @brief   图形显示器接口
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form
  * or means, without the prior written consent of shentq. This specification is
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#ifndef __G_DISP_CHAR_H
#define __G_DISP_CHAR_H

#include "lgui_font.h"
#include "G_LCD_interface.h"

typedef struct {
  const GUI_FONT   * pAFont;
	int16_t	LBorder;								// 边界
  int16_t DispPosX, DispPosY;
  int16_t DrawPosX, DrawPosY;
  int16_t TextMode, TextAlign;
}TextInfo;

class TEXTAPI
{
public: 
		TEXTAPI(GAPI *pG,TextInfo *pT);
		
    void putChar(char c);
		void putCharS(char *s , uint16_t num);
		void putString(uint16_t x,uint16_t y,const char *str);
		void printf(uint16_t x,uint16_t y,const char *fmt, ...);
protected :
    TextInfo *_context;
		GAPI *_put;
private	:
		void _dispChar(char c);
		void _dispCharP(char c);
		void _dispNextLine();
		uint16_t	_getYAdjust();
};

#endif
