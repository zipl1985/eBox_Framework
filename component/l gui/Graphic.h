/**
  ******************************************************************************
  * @file    Graphic.h
  * @author  cat_li
  * @brief   基础图形
	*		2019.7.10		添加图形Ex接口：Ex 通过起始坐标和结束坐标确定位置和大小
	*								不带Ex通过左上确定位置，宽，高确定大小								
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
#include "gui_com.h"


class GUI : public TEXTAPI
{
public: 
	GUI(GAPI *pG);
	
	void begin();
	void clear(){fillScreen(_g.bc);}
	void setDispMode(DispMode_e mode);
	
  /*  填充图形	*/ 
  void fillScreen( E_COLOR c );
  void fillFrame( uint16_t x, uint16_t y, uint16_t width, uint16_t height, E_COLOR c );		// 填充矩形-坐标(x,y),尺寸(width,height),颜色(c)
	void fillFrameEx( uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, E_COLOR c );  		// 填充矩形-坐标(xs,ys,xe,ye),颜色(c)
  void fillRoundFrame( uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint16_t r, E_COLOR c );	// 填充圆角矩形-坐标(x,y),尺寸(width,height),圆弧半径(r),颜色(c)	
	void fillRoundFrameEx( uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t r, E_COLOR c );   // 填充圆角矩形-坐标(xs,ys,xe,ye),颜色(c)
  void fillCircle( uint16_t x, uint16_t y, uint16_t r, E_COLOR c );			// 填充圆形-坐标(x,y),半径(r),颜色(c)
  
  /* 	画图 	*/  
  void drawMesh(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint16_t gap, E_COLOR c );	// 画网格-坐标(x,y),尺寸(width,height),间距(gap)颜色(c)
	void drawMeshEx(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,uint16_t gap, E_COLOR c );			// 画网格-坐标(xs,ys,xe,ye),间距(gap)颜色(c)
  void drawFrame(uint16_t x, uint16_t y, uint16_t width, uint16_t height, E_COLOR c );		// 画矩形-坐标(x,y),尺寸(width,height),颜色(c)
  void drawFrameEx(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, E_COLOR c );  			// 画矩形-坐标(xs,ys,xe,ye),颜色(c)
  void drawRoundFrame( uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t r, E_COLOR c );			// 画圆角矩形-坐标(x,y),尺寸(width,height),圆弧半径(r),颜色(c)	
	void drawRoundFrameEx(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t r, E_COLOR c );		// 画圆角矩形-坐标(xs,ys,xe,ye),圆弧半径(r),颜色(c)  
  void drawPixel( uint16_t x0, uint16_t y0, E_COLOR c );														// 描点-坐标(x,y),颜色(c)  
  void drawCircle( uint16_t x0, uint16_t y0, uint16_t r, E_COLOR c );								// 画圆-坐标(x,y),半径(r),颜色(c)  
  void drawArc( uint16_t x0, uint16_t y0, uint16_t r, uint8_t s, E_COLOR c ); 			// 画弧线 
  void drawLine( uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, E_COLOR c );		// 画线-起点(xs,ys),终点(xe,ye)

	virtual void		drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR bcolor,E_COLOR fcolor);

	// 获取参数
	E_COLOR		getBColor(){return _g.bc;}
	E_COLOR  	getfColor(){return _g.fc;}
	int16_t		getWidth(){return  _g.w;}
	int16_t		getHeight(){return _g.h;}	
	
	
	void 	putText(TEXT_S *t,char *str,uint8_t align);
	void	ptxt(TEXT_SS *t);
	
	void 	loop();
	void 	setCurrentWND(GUI_COM *wnd){_wnd = wnd;}
private	:
	WINDOW_S 	_g;			// 显示区域信息
	TEXT_S  	_t;			// 显示文本信息
	
	GUI_COM *_wnd;

	void _drawLine(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, E_COLOR c);		// 画任意角度直线
	int16_t _getXend(int16_t xe){ return (xe>_g.w ? _g.w : xe);}											// 防止x出边界
	int16_t _getYend(int16_t ye){ return (ye>_g.h ? _g.h : ye);}											// 防止y出边界
	
	int16_t	_getYAdjust(uint8_t align,uint16_t h=1);
	int16_t	_getXAdjust(uint8_t align,uint16_t stringWidth);
};
#endif
