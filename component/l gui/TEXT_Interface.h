/**
  ******************************************************************************
  * @file    TEXT_Interface.h
  * @author  cat_li
  * @brief   文本输出接口,用来向指定设备输出文本
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

#ifndef __TEXT_INTERFACE_H
#define __TEXT_INTERFACE_H

#include "lgui_font.h"
#include "G_LCD_interface.h"

// 显示区域参数
typedef struct
{
		int16_t x;				// 坐标
		int16_t y;
		int16_t w;				// 尺寸
		int16_t h;
		E_COLOR fc;				// 颜色
    E_COLOR bc;
		DispMode_e mode;	// 显示模式
}AREA_S;

typedef struct
{
    AREA_S   disp;
    const 	 GUI_FONT 	*pAFont;
		int16_t  DispPosX, DispPosY;
}TEXT_S;

typedef struct
{
    AREA_S    disp;
	  char 		  *str;
		uint8_t   align;		// 对齐模式
    const 	  GUI_FONT 	  *pAFont;
		int16_t   DispPosX,   DispPosY;
}TEXT_SS;

class TEXTAPI
{
public: 
		TEXTAPI(GAPI *pG,TEXT_S *pT);
	
    void putChar(const char c);
		void putCharS(const char *s , uint16_t num);
		void putString(uint16_t x,uint16_t y,const char *str);
		// 属性设置
		void selectFont(const GUI_FONT *f){_pT->pAFont = f;}
		void setTextBackColor(E_COLOR c){_pT->disp.bc = c;}
		void setTextForeColor(E_COLOR c){_pT->disp.fc = c;}
		void setTextMode(DispMode_e mode){_pT->disp.mode = mode;}
		
//		void putText(TEXT_S *t,char 		  *str);
protected :
    TEXT_S *_pT;			// 指向文本参数
		GAPI   *_pDev;		// 指向输出设备

		void _dispChar(char c);
		virtual void 		_drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR color);
		virtual void 		_drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR bcolor,E_COLOR fcolor);
private	:

		void _dispCharP(char c);
		void _dispNextLine();
};

#endif
