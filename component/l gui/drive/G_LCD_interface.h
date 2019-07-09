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

#ifndef __G_LCD_INTERFACE_H
#define __G_LCD_INTERFACE_H

#include "ebox_type.h"
#include "enum.h"
#include "colorDefine.h"
#include "lgui_font.h"


//typedef struct {
//		uint16_t x;						// 坐标x
//		uint16_t y;						// 坐标y
//    uint16_t width;    		// 屏幕宽度
//    uint16_t height;    	// 屏幕高度
//		DispMode_e mode;			// 显示模式
//    E_COLOR fColor;
//    E_COLOR bColor;
//}display_t;



class GAPI
{
public:
		// 底层设备,实现接口时必须传入屏幕尺寸
		GAPI(int16_t width,int16_t height){_width = width;_height = height;}
		// 描点（x,y），必须实现该接口
    virtual void    draw_pixel(int16_t x, int16_t y, E_COLOR color)=0;
		// 水平线（x,y,len），建议底层实现该接口，优化效率
    virtual void    draw_h_line(int16_t x, int16_t y, int16_t len, E_COLOR color);
		// 垂直线（x,y,len），建议底层实现该接口，优化效率
    virtual void    draw_v_line(int16_t x, int16_t y, int16_t len, E_COLOR color);
		// 填充矩形（x,y,width,high）建议底层实现该接口，优化效率
    virtual void    fill_rect(int16_t x, int16_t y, int16_t width, int16_t height, E_COLOR color);
		// 强制输出，根据硬件特性决定是否实现
		virtual void    flush();
		
		
//    void    draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, E_COLOR color);
    void    draw_circle(int16_t x, int16_t y, int16_t r, E_COLOR color);
    void    fill_screen(E_COLOR color);

		uint16_t		getWidth(){return _width;}
		uint16_t		getHeight(){return _height;}
protected :
    int16_t	_width;
		int16_t  _height;
};
#endif
