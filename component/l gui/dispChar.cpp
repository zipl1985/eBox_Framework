/**
  ******************************************************************************
  * @file    G_LCD_interface.cpp
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
#include "ebox_core.h"
#include "dispChar.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif
		extern const GUI_FONT_PROP * GUIPROP_FindChar(const GUI_FONT_PROP * pProp, uint16_t c);
#if defined(__cplusplus)
}
#endif

extern const GUI_FONT GUI_FontGUI_Font8_1;

TEXTAPI::TEXTAPI(GAPI *pG,TextInfo *pT)
{
	_put = pG;
	_context = pT;
	if(pT->pAFont == NULL) _context->pAFont = &GUI_FontGUI_Font8_1;
}

void TEXTAPI::_dispChar(char c) {
	if( _context->pAFont->pfGetFontInfo() == GUI_FONTINFO_FLAG_PROP) _dispCharP(c);
}

void TEXTAPI::putChar(char c)
{
	if(c=='\n'){
		_dispNextLine();
	}else if(c!='\r'){
		_dispChar(c);
	}		
}

void TEXTAPI::putString(uint16_t x,uint16_t y,const char *str)
{
		_context->DispPosX = x;
		_context->DispPosY = y - _getYAdjust();
		for(;*str;str++){
			putChar(*str);
    }
}

void TEXTAPI::printf(uint16_t x,uint16_t y,const char *fmt, ...)
{
		char buf[256];
		va_list va_params;
		va_start(va_params, fmt);
		ebox_vsnprintf(buf, 256, fmt, va_params);
		putString(x,y,buf);
		va_end(va_params);	
		
}

void TEXTAPI::_dispCharP(char c){
	int BytesPerLine;
	// 获取字库
  const GUI_FONT_PROP * pProp = GUIPROP_FindChar(_context->pAFont->p.pProp, c);
  if (pProp) {
		// 指向要显示的字符(字库首地址+偏移）
    const GUI_CHARINFO * pCharInfo = pProp->paCharInfo+(c-pProp->First);
    BytesPerLine = pCharInfo->BytesPerLine;
		_put->drawBitmap(_context->DispPosX, _context->DispPosY,pCharInfo->pData,pCharInfo->XSize, _context->pAFont->YSize,0XD69A,0XCAA0);
    /* Fill empty pixel lines */
    if (_context->pAFont->YDist > _context->pAFont->YSize) {
      int YMag = _context->pAFont->YMag;
      int YDist = _context->pAFont->YDist * YMag;
      int YSize = _context->pAFont->YSize * YMag;
      if (_context->TextMode != LCD_DRAWMODE_TRANS) {
					_put->fill_rect(_context->DispPosX, 
                     _context->DispPosY + YSize, 
                      pCharInfo->XSize, 
                     YDist,
										 1);
      }
    }
    _context->DispPosX += pCharInfo->XDist * _context->pAFont->XMag;
  }
}

void TEXTAPI::_dispNextLine(void)
{
		_context->DispPosY += _context->pAFont->YDist;
		_context->DispPosX = _context->LBorder;
}

// 调整Y坐标
uint16_t TEXTAPI::_getYAdjust()
{
	switch (_context->TextAlign & GUI_TA_VERTICAL) {
	case GUI_TA_BOTTOM:
		return  _context->pAFont->YSize - 1;
	case GUI_TA_VCENTER:
		return 	_context->pAFont->YSize / 2;
	case GUI_TA_BASELINE:
		return 	_context->pAFont->YSize / 2;
	}
}

