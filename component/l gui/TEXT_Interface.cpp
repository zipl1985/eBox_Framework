/**
  ******************************************************************************
  * @file    TEXT_Interface.cpp
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
#include "ebox_core.h"
#include "text_interface.h"
#include "bsp_ebox.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif
		extern const GUI_FONT_PROP * GUIPROP_FindChar(const GUI_FONT_PROP * pProp, uint16_t c);
#if defined(__cplusplus)
}
#endif



TEXTAPI::TEXTAPI(GAPI *pG,TEXT_S *pT)
{
	_pDev = pG;
	_pT = pT;
	// 如果没有字体信息，则假定文本参数没有初始化
	if(pT->pAFont == NULL){
		_pT->pAFont = &GUI_FontGUI_Font8_1;
		_pT->pUC_API = &ENC_API_TableNone;
		_pT->disp.bc = C_WHITE;
		_pT->disp.fc = C_BLACK;
		_pT->disp.mode = DispMode_Normal;
	}
	if(_pT->disp.x == 0 || _pT->disp.y == 0){
		_pT->disp.x = 2;
		_pT->disp.y = 2;
		_pT->disp.w = _pDev->getWidth() -4;
		_pT->disp.h = _pDev->getHeight() -4;
	}
}

void TEXTAPI::selectFont(const GUI_FONT *f,const GUI_UC_ENC_APILIST * pUC_API){
	_pT->pAFont = f;
	_pT->pUC_API = pUC_API;
}

void TEXTAPI::_dispChar(uint16_t c) {
	if( _pT->pAFont->pfGetFontInfo() == GUI_FONTINFO_FLAG_PROP) _dispCharP(c);
}

void TEXTAPI::putChar(uint16_t c)
{
	if(c=='\n'){
		_dispNextLine();
	}else if(c!='\r'){		
		_dispChar(c);
	}		
}

uint16_t TEXTAPI::__GetCharCodeInc(const char  ** ps) {
  const char  * s;
  uint16_t r;
  s   = *ps;
//  #if GUI_SUPPORT_UNICODE
    r   = _pT->pUC_API->pfGetCharCode(s);
    s  += _pT->pUC_API->pfGetCharSize(s);
//  #else
//    r   = *s;
//    s  += 1;
//  #endif
  *ps = s;
  return r;
}

void TEXTAPI::putString(uint16_t x,uint16_t y,const char *str)
{
		uint16_t Char;
		_pT->DispPosX = _pT->disp.x + x;
		_pT->DispPosY = _pT->disp.y + y;
		for(;*str;){
			Char = __GetCharCodeInc(&str);
			putChar(Char);
    }
}

void TEXTAPI::_drawBitmap(int16_t x, int16_t y,
                     const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR color)
{

    int16_t i, j, byteWidth = (w + 7) / 8;
    uint8_t byte;

    for(j = 0; j < h; j++)
    {
        for(i = 0; i < w; i++)
        {
            if(i & 7) byte <<= 1;
            else      byte   = *(bitmap + j * byteWidth + i / 8);
            if(byte & 0x80) _pDev->draw_pixel(x + i, y + j, color);
        }
    }
}

void TEXTAPI::_drawBitmap(int16_t x, int16_t y,
                     const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR bcolor,E_COLOR fcolor)
{

    int16_t i, j, byteWidth = (w + 7) / 8;
    uint8_t byte;

    for(j = 0; j < h; j++)
    {
        for(i = 0; i < w; i++)
        {
            if(i & 7) byte <<= 1;
            else      byte   = *(bitmap + j * byteWidth + i / 8);
            
						if(byte & 0x80){
							_pDev->draw_pixel(x + i, y + j, fcolor);
						}else{
							_pDev->draw_pixel(x + i, y + j, bcolor);
						}
        }
    }
}



void TEXTAPI::_dispCharP(uint16_t c){
	int xe = _pT->disp.x+_pT->disp.w ;
	// 获取字库
  const GUI_FONT_PROP * pProp = GUIPROP_FindChar(_pT->pAFont->p.pProp, c);
  if (pProp) {
		// 指向要显示的字符(字库首地址+偏移）
    const GUI_CHARINFO * pCharInfo = pProp->paCharInfo+(c-pProp->First);

		_drawBitmap(_pT->DispPosX, _pT->DispPosY,pCharInfo->pData,pCharInfo->XSize, _pT->pAFont->YSize,_pT->disp.bc,_pT->disp.fc);
    /* Fill empty pixel lines */
    if (_pT->pAFont->YDist > _pT->pAFont->YSize){
      int YMag = _pT->pAFont->YMag;
      int YDist = _pT->pAFont->YDist * YMag;
      int YSize = _pT->pAFont->YSize * YMag;
      if (_pT->disp.mode != DispMode_Trans) {
					_pDev->fill_rect(_pT->DispPosX, 
                     _pT->DispPosY + YSize, 
                      pCharInfo->XSize, 
                     YDist,
										 _pT->disp.bc);
      }
    }
		// 移动到下一个字符位置，支持自动换行
//		if(xe-_pT->DispPosX < (pCharInfo->XDist * _pT->pAFont->XMag)<<1) _dispNextLine();
//		else _pT->DispPosX += pCharInfo->XDist * _pT->pAFont->XMag;
			_pT->DispPosX += pCharInfo->XDist * _pT->pAFont->XMag;
			if((xe - _pT->DispPosX) < (pCharInfo->XDist * _pT->pAFont->XMag)) 
				_dispNextLine();
  }
}

void TEXTAPI::_dispNextLine(void)
{
		_pT->DispPosY += _pT->pAFont->YDist;
		_pT->DispPosX = _pT->disp.x;
}



