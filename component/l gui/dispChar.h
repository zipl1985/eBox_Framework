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

typedef struct
{
		int16_t x;
		int16_t y;
		int16_t w;
		int16_t h;
		E_COLOR fc;
    E_COLOR bc;
    uint8_t align;
		DispMode_e mode;
}WND_S;

typedef struct
{
    WND_S   disp;
	  char *str;
    const GUI_FONT *pAFont;
		int16_t DispPosX, DispPosY;
}TEXT_S;

class TEXTAPI
{
public: 
		TEXTAPI(GAPI *pG,TEXT_S *pT);
		
    void putChar(char c);
		void putCharS(char *s , uint16_t num);
		void putString(uint16_t x,uint16_t y,const char *str);
		void printf(uint16_t x,uint16_t y,const char *fmt, ...);
    void putText(TEXT_S *t);
protected :
    TEXT_S *_context;
		GAPI *_dev;
		virtual void 		drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR color);
		virtual void 		drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR bcolor,E_COLOR fcolor);
private	:
		void _dispChar(char c);
		void _dispCharP(char c);
		void _dispNextLine();
		int16_t	_getYAdjust(uint16_t h=1);
		int16_t	_getXAdjust(uint16_t stringWidth);
};

#endif
