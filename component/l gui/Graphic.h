/**
  ******************************************************************************
  * @file    Graphic.h
  * @author  cat_li
  * @brief   »ù´¡Í¼ÐÎ
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

#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include "G_LCD_interface.h"
#include "TEXT_interface.h"
#include "lgui_font.h"

class GUI : public TEXTAPI
{
public: 
	GUI(GAPI *pG);
	
	void begin();
	void clear(){fillScreen(_g.bc);}
	void setDispMode(DispMode_e mode);
  // Ìî³äÍ¼ÐÎ 
  void fillScreen( E_COLOR c );
  // Ìî³ä¾ØÐÎ-×ø±ê(x,y),³ß´ç(width,height),ÑÕÉ«(c)
  void fillFrame( uint16_t x, uint16_t y, uint16_t width, uint16_t height, E_COLOR c );
  // Ìî³äÔ²½Ç¾ØÐÎ-×ø±ê(x,y),³ß´ç(width,height),Ô²»¡°ë¾¶(r),ÑÕÉ«(c)
  void fillRoundFrame( uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t r, E_COLOR c );
  // Ìî³äÔ²ÐÎ-×ø±ê(x,y),°ë¾¶(r),ÑÕÉ«(c)
  void fillCircle( uint16_t x, uint16_t y, uint16_t r, E_COLOR c );
  
  /* »­Í¼ */
  // »­Íø¸ñ-×ø±ê(x,y),³ß´ç(width,height),¼ä¾à(gap)ÑÕÉ«(c)
  void drawMesh(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height,uint16_t gap, E_COLOR c );
  // »­¾ØÐÎ-×ø±ê(x,y),³ß´ç(width,height),ÑÕÉ«(c)
  void drawFrame(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, E_COLOR c );
  // »­Ô²½Ç¾ØÐÎ-×ø±ê(x,y),³ß´ç(width,height),Ô²»¡°ë¾¶(r),ÑÕÉ«(c)
  void drawRoundFrame( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t r, E_COLOR c );
  // Ãèµã-×ø±ê(x,y),ÑÕÉ«(c)
  void drawPixel( uint16_t x0, uint16_t y0, E_COLOR c );
  // »­Ô²-×ø±ê(x,y),°ë¾¶(r),ÑÕÉ«(c)
  void drawCircle( uint16_t x0, uint16_t y0, uint16_t r, E_COLOR c );
  // »­»¡Ïß
  void drawArc( uint16_t x0, uint16_t y0, uint16_t r, uint8_t s, E_COLOR c );
  // »­Ïß-Æðµã(xs,ys),ÖÕµã(xe,ye)
  void drawLine( uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, E_COLOR c );

	virtual void		drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR bcolor,E_COLOR fcolor);

	
	E_COLOR		getBColor(){return _g.bc;}
	E_COLOR  	getfColor(){return _g.fc;}
	int16_t		getWidth(){return  _g.w;}
	int16_t		getHeight(){return _g.h;}
	
	const GUI_FONT * getFont(){return _t.pAFont;}
	
	void 	putText(TEXT_S *t,char *str,uint8_t align);
private	:
	AREA_S 	_g;			// ÏÔÊ¾ÇøÓòÐÅÏ¢
	TEXT_S  _t;			// ÏÔÊ¾ÎÄ±¾ÐÅÏ¢

	void _drawLine(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, E_COLOR c);
	int16_t _getXend(int16_t xe){ return (xe>_g.w ? _g.w : xe);}
	int16_t _getYend(int16_t ye){ return (ye>_g.h ? _g.h : ye);}
	
	int16_t	_getYAdjust(uint8_t align,uint16_t h=1);
	int16_t	_getXAdjust(uint8_t align,uint16_t stringWidth);
};
#endif
