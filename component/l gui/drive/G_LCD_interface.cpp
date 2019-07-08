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
#include "G_LCD_interface.h"

uint16_t bgr2rgb(uint16_t c)
{
    uint16_t  r, g, b, rgb;
    b = (c >> 0) & 0x1f;
    g = (c >> 5) & 0x3f;
    r = (c >> 11) & 0x1f;
    rgb = (b << 11) + (g << 5) + (r << 0);
    return(rgb);

}

uint16_t rgb24_2_rgb565(int r, int g, int b)   //应该会损失数据内容
{
        
return (uint16_t)(  ((unsigned(r) << 8) & 0xF800) | 
            
                    ((unsigned(g) << 3) & 0x7E0)  |
                    ((unsigned(b) >> 3))
                 );
}

uint16_t rgb24_2_rgb565(uint32_t color)   //应该会损失数据内容
{
        
return (uint16_t)(  ((color & 0xF80000) >> 8) | 
                    ((color & 0x00FC00) >> 5)|
                    ((color & 0x0000F1) >> 3)
                 );
}


void GAPI::draw_v_line(int16_t x, int16_t y, int16_t len, E_COLOR color)
{
//		if(_screen.height !=0) len = _screen.height-y > len ? len : _screen.height-y;
    while(len--)
        draw_pixel(x, y++, color);
}
void GAPI::draw_h_line(int16_t x, int16_t y, int16_t len, E_COLOR color)
{
//		if(_screen.width !=0) len = _screen.width-x > len ? len : _screen.width-x;
    while(len--)
        draw_pixel(x++, y, color);
}

void GAPI::fill_rect(int16_t x, int16_t y, int16_t width, int16_t height, E_COLOR color)
{
//		if(_screen.height !=0) height = _screen.height-y > height ? height : _screen.height-y;
//		if(_screen.width !=0) width = _screen.width-x > width ? width : _screen.width-x;
	
    for(uint16_t i=0; i <= width; i++)
    {
        for(uint16_t j = 0; j <= height; j++)
            draw_pixel(x+i, y+j, color);
    }
}

void GAPI::draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, E_COLOR color)
{
    int dx,             // difference in x's
        dy,             // difference in y's
        dx2,            // dx,dy * 2
        dy2,
        x_inc,          // amount in pixel space to move during drawing
        y_inc,          // amount in pixel space to move during drawing
        error,          // the discriminant i.e. error i.e. decision variable
        index;          // used for looping

    //            set_xy(x0, y0);
    dx = x1 - x0; //计算x距离
    dy = y1 - y0; //计算y距离

    if (dx >= 0)
    {
        x_inc = 1;
    }
    else
    {
        x_inc = -1;
        dx    = -dx;
    }

    if (dy >= 0)
    {
        y_inc = 1;
    }
    else
    {
        y_inc = -1;
        dy    = -dy;
    }

    dx2 = dx << 1;
    dy2 = dy << 1;

    if (dx > dy)//x距离大于y距离，那么每个x轴上只有一个点，每个y轴上有若干个点
    {
        //且线的点数等于x距离，以x轴递增画点
        // initialize error term
        error = dy2 - dx;

        // draw the line
        for (index = 0; index <= dx; index++) //要画的点数不会超过x距离
        {
            //画点
            draw_pixel(x0, y0, color);

            // test if error has overflowed
            if (error >= 0) //是否需要增加y坐标值
            {
                error -= dx2;

                // move to next line
                y0 += y_inc; //增加y坐标值
            } // end if error overflowed

            // adjust the error term
            error += dy2;

            // move to the next pixel
            x0 += x_inc; //x坐标值每次画点后都递增1
        } // end for
    } // end if |slope| <= 1
    else//y轴大于x轴，则每个y轴上只有一个点，x轴若干个点
    {
        //以y轴为递增画点
        // initialize error term
        error = dx2 - dy;

        // draw the line
        for (index = 0; index <= dy; index++)
        {
            // set the pixel
            draw_pixel(x0, y0, color);

            // test if error overflowed
            if (error >= 0)
            {
                error -= dy2;

                // move to next line
                x0 += x_inc;
            } // end if error overflowed

            // adjust the error term
            error += dx2;

            // move to the next pixel
            y0 += y_inc;
        } // end for
    } // end else |slope| > 1
}



void GAPI::draw_circle(int16_t x, int16_t y, int16_t r, E_COLOR color)
{
    unsigned short  a, b;
    int c;
    a = 0;
    b = r;
    c = 3 - 2 * r;
    while (a < b)
    {
        draw_pixel(x + a, y + b, color); //        7
        draw_pixel(x - a, y + b, color); //        6
        draw_pixel(x + a, y - b, color); //        2
        draw_pixel(x - a, y - b, color); //        3
        draw_pixel(x + b, y + a, color); //        8
        draw_pixel(x - b, y + a, color); //        5
        draw_pixel(x + b, y - a, color); //        1
        draw_pixel(x - b, y - a, color); //        4

        if(c < 0) c = c + 4 * a + 6;
        else
        {
            c = c + 4 * (a - b) + 10;
            b -= 1;
        }
        a += 1;
    }
    if (a == b)
    {
        draw_pixel(x + a, y + b, color);
        draw_pixel(x + a, y + b, color);
        draw_pixel(x + a, y - b, color);
        draw_pixel(x - a, y - b, color);
        draw_pixel(x + b, y + a, color);
        draw_pixel(x - b, y + a, color);
        draw_pixel(x + b, y - a, color);
        draw_pixel(x - b, y - a, color);
    }
}

void GAPI::fill_screen(E_COLOR color)
{
	fill_rect(0,0,_width,_height,color);
}

void GAPI::flush()
{
}


