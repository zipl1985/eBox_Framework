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
#include "color_table.h"
#include "lgui_font.h"

#define EBOX_COLOR  uint16_t  

uint16_t bgr2rgb(uint16_t c);
uint16_t rgb24_2_rgb565(uint32_t color);   //应该会损失数据内容

typedef struct {
		uint16_t x;						// 坐标x
		uint16_t y;						// 坐标y
    uint16_t width;    		// 屏幕宽度
    uint16_t height;    	// 屏幕高度
		DrawMode_t mode;			// 显示模式
    EBOX_COLOR fColor;
    EBOX_COLOR bColor;
}display_t;



class GAPI
{
public: 
		// 描点（x,y），必须实现该接口
    virtual void    draw_pixel(int16_t x, int16_t y, uint32_t color)=0;
		// 水平线（x,y,len），建议底层实现该接口，优化效率
    virtual void    draw_h_line(int16_t x, int16_t y, int16_t len, uint32_t color);
		// 垂直线（x,y,len），建议底层实现该接口，优化效率
    virtual void    draw_v_line(int16_t x, int16_t y, int16_t len, uint32_t color);
		// 填充矩形（x,y,width,high）建议底层实现该接口，优化效率
    virtual void    fill_rect(int16_t x, int16_t y, int16_t width, int16_t height, uint32_t color);
		// 强制输出，根据硬件特性决定是否实现
		virtual void    flush();
		
		
    void    draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);
    void    draw_circle(int16_t x, int16_t y, int16_t r, uint32_t color);
    void    fill_screen(uint32_t color);

		void 		drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, uint32_t color);
		void 		drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, uint32_t bcolor,uint32_t fcolor);
protected :
    uint16_t	_width;
		uint16_t  _height;
};
#endif
