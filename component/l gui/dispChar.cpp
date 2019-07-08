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
#include "bsp_ebox.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif
		extern const GUI_FONT_PROP * GUIPROP_FindChar(const GUI_FONT_PROP * pProp, uint16_t c);
#if defined(__cplusplus)
}
#endif

extern const GUI_FONT GUI_FontGUI_Font8_1;

TEXTAPI::TEXTAPI(GAPI *pG,TEXT_S *pT)
{
	_dev = pG;
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
//		char buf[256];
//		va_list va_params;
//		va_start(va_params, fmt);
//		ebox_vsnprintf(buf, 256, fmt, va_params);
//		putString(x,y,buf);
//		va_end(va_params);			
}

void TEXTAPI::drawBitmap(int16_t x, int16_t y,
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
            if(byte & 0x80) _dev->draw_pixel(x + i, y + j, color);
        }
    }
}

void TEXTAPI::drawBitmap(int16_t x, int16_t y,
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
							_dev->draw_pixel(x + i, y + j, fcolor);
						}else{
							_dev->draw_pixel(x + i, y + j, bcolor);
						}
        }
    }
}

void TEXTAPI::putText(TEXT_S *txt)
{
	  uint16_t sl, rc, wl;
    int16_t xp, yp;
    int16_t xs = txt->disp.x;
    int16_t ys = txt->disp.y;
    int16_t xe = txt->disp.x+txt->disp.w;
    int16_t ye = txt->disp.y+txt->disp.h;

    char chr;

    char *str = txt->str;
    char *c = str;
		
		TEXT_S *old = _context;
		_context = txt;

    if ( txt->pAFont== NULL ) return;
    if ( str == NULL ) return;
//    if ( (ye - ys) < txt->pAFont->YSize ) return;

    rc = 1;
    c = str;
		// 计算行数
    while ( *c != 0 )
    {
        if ( *c == '\n' ) rc++;
        c++;
    }

    yp = 0;
		yp = ys + _getYAdjust(rc);
		_context->DispPosY = yp;

    while( 1 )
    {
        sl = 0;
        c = str;
        wl = 0;
        while( (*c != 0) && (*c != '\n') )
        {
						// 如果当前字符不存在
            if (!(txt->pAFont->pfIsInFont(txt->pAFont,*c)))
            {
                c++;
                continue;
            }
            sl++; // 字符串长度						
            wl += txt->pAFont->pfGetCharDistX(txt->pAFont,*c);	// 字符串宽度
            c++;
        }

        xp = xs+_getXAdjust(wl+2);
				_context->DispPosX = xp;
        while( (*str != '\n') )
        {
            chr = *str++;
            if ( chr == 0 ){
									_context = old;
							return;}
						_dispChar(chr);
        }
        str++;
       _context->DispPosY += _context->pAFont->YDist;
    }


}

void TEXTAPI::_dispCharP(char c){
	int BytesPerLine;
	// 获取字库
  const GUI_FONT_PROP * pProp = GUIPROP_FindChar(_context->pAFont->p.pProp, c);
  if (pProp) {
		// 指向要显示的字符(字库首地址+偏移）
    const GUI_CHARINFO * pCharInfo = pProp->paCharInfo+(c-pProp->First);
    BytesPerLine = pCharInfo->BytesPerLine;
		drawBitmap(_context->DispPosX, _context->DispPosY,pCharInfo->pData,pCharInfo->XSize, _context->pAFont->YSize,_context->disp.bc,_context->disp.fc);
    /* Fill empty pixel lines */
    if (_context->pAFont->YDist > _context->pAFont->YSize) {
      int YMag = _context->pAFont->YMag;
      int YDist = _context->pAFont->YDist * YMag;
      int YSize = _context->pAFont->YSize * YMag;
      if (_context->disp.mode != DispMode_Trans) {
					_dev->fill_rect(_context->DispPosX, 
                     _context->DispPosY + YSize, 
                      pCharInfo->XSize, 
                     YDist,
										 _context->disp.bc);
      }
    }
    _context->DispPosX += pCharInfo->XDist * _context->pAFont->XMag;
  }
}

void TEXTAPI::_dispNextLine(void)
{
		_context->DispPosY += _context->pAFont->YDist;
		_context->DispPosX = _context->disp.x;
}

// 调整Y坐标,返回偏移量
int16_t TEXTAPI::_getYAdjust(uint16_t h)
{
	switch (_context->disp.align & GUI_TA_VERTICAL) {
	case GUI_TA_BOTTOM:
		return _context->disp.h - _context->pAFont->YSize * h;
	case GUI_TA_VCENTER:
		return (_context->disp.h -	_context->pAFont->YSize * h)/2;
	case GUI_TA_TOP:
		return 	0;
	}
}

// 调整Y坐标,返回偏移量
int16_t TEXTAPI::_getXAdjust(uint16_t stringWidth)
{
	switch (_context->disp.align & GUI_TA_HORIZONTAL) {
	case GUI_TA_LEFT:
		return 0;
	case GUI_TA_RIGHT:
		return _context->disp.w - stringWidth - 3;
	case GUI_TA_CENTER:
		return 	(_context->disp.w - stringWidth)/2;
	}
}

