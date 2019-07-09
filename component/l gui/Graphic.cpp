/**
  ******************************************************************************
  * @file    GUI.cpp
  * @author  cat_li
  * @brief   基本图形绘制
	*		1 2019.7.8	添加判断，防止坐标超出屏幕
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
#include "Graphic.h"
#include "ebox_core.h"

GUI::GUI(GAPI *pG):TEXTAPI(pG,&_t){
	_t.pAFont = &GUI_FontGUI_Font8_1;
	_g.bc = _t.disp.bc = 0xEF7D;
	_g.fc = _t.disp.fc = 0x0000;
	_g.mode = _t.disp.mode = DispMode_Normal;
  _g.w = _t.disp.w = _pDev->getWidth();
  _g.h = _t.disp.h = _pDev->getHeight();
}

void GUI::begin(){

}

void GUI::setDispMode(DispMode_e mode){
	_g.mode = mode;
	if(_g.mode == DispMode_Rev){
		swap(&_g.bc,&_g.fc);
		_t.disp.bc = _g.bc;
		_t.disp.fc = _g.fc;
	}
}

void GUI::fillScreen( E_COLOR c ){
	_pDev->fill_rect(_g.x,_g.y,_g.w,_g.h,c); 
}
void GUI::fillFrame(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, E_COLOR c ){
	_pDev->fill_rect(x1,y1,_getXend(x1+width)-x1,_getYend(y1+height)-y1,c);
}
void GUI::fillRoundFrame( uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, uint16_t r, E_COLOR c ){
    int16_t  x, y, xd;

    if ( r <= 0 ) return;

    xd = 3 - (r << 1);
    x = 0;
    y = r;

    _pDev->fill_rect(x1 + r, y1, width - r-r, height, c);

    while ( x <= y )
    {
        if( y > 0 )
        {
					_pDev->draw_v_line(x1+width+x-r,y1-y+r,height-(r<<1)+(y<<1),c);
					_pDev->draw_v_line(x1-x+r,y1-y+r,height-(r<<1)+(y<<1),c);
        }
        if( x > 0 )
        {
					_pDev->draw_v_line(x1 - y + r, y1 - x + r,height+((x-r)<<1),c);
					_pDev->draw_v_line(x1+width + y - r, y1 - x + r,height+((x-r)<<1),c);
        }
        if ( xd < 0 )
        {
            xd += (x << 2) + 6;
        }
        else
        {
            xd += ((x - y) << 2) + 10;
            y--;
        }
        x++;
    }
}
void GUI::drawMesh(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height,uint16_t gap, E_COLOR c ){
    int16_t n = x1+width , m = y1+height ;

    for(; y1 <= m; y1 += gap )
    {
        for(; x1 <= n; x1 += gap )
        {
           _pDev->draw_pixel(x1, y1, c);
        }
    }
}
void GUI::drawFrame(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, E_COLOR c ){
  _pDev->draw_h_line(x1,y1,width,c);
  _pDev->draw_h_line(x1,y1+height,width,c);
  _pDev->draw_v_line(x1,y1,height,c);
  _pDev->draw_v_line(x1+width,y1,height,c);
}
void GUI::drawRoundFrame( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t r, E_COLOR c ){
    int16_t n;
    if ( x2 < x1 )
    {
        n = x2;
        x2 = x1;
        x1 = n;
    }
    if ( y2 < y1 )
    {
        n = y2;
        y2 = y1;
        y1 = n;
    }

    if ( r > x2 ) return;
    if ( r > y2 ) return;

    drawLine(x1 + r, y1, x2 - r, y1, c);
    drawLine(x1 + r, y2, x2 - r, y2, c);
    drawLine(x1, y1 + r, x1, y2 - r, c);
    drawLine(x2, y1 + r, x2, y2 - r, c);
    drawArc(x1 + r, y1 + r, r, 0x0C, c);
    drawArc(x2 - r, y1 + r, r, 0x03, c);
    drawArc(x1 + r, y2 - r, r, 0x30, c);
    drawArc(x2 - r, y2 - r, r, 0xC0, c);
}
void GUI::drawPixel( uint16_t x, uint16_t y, E_COLOR c ){
	if(x>_g.w || y > _g.h) return;
  _pDev->draw_pixel(x,y,c);
}
void GUI::drawCircle( uint16_t x0, uint16_t y0, uint16_t r, E_COLOR c ){
	_pDev->draw_circle(x0,y0,r,c);
}
void GUI::fillCircle( uint16_t x0, uint16_t y0, uint16_t r, E_COLOR c ){
    int16_t  x, y, xd;

    if ( x0 < 0 ) return;
    if ( y0 < 0 ) return;
    if ( r <= 0 ) return;

    xd = 3 - (r << 1);
    x = 0;
    y = r;

    while ( x <= y )
    {
        if( y > 0 )
        {
					_pDev->draw_v_line(x0-x,y0-y,2*y,c);
					_pDev->draw_v_line(x0+x,y0-y,2*y,c);
        }
        if( x > 0 )
        {
					_pDev->draw_v_line(x0-y,y0-x,2*x,c);
					_pDev->draw_v_line(x0+y,y0-x,2*x,c);
        }
        if ( xd < 0 )
        {
            xd += (x << 2) + 6;
        }
        else
        {
            xd += ((x - y) << 2) + 10;
            y--;
        }
        x++;
    }
    _pDev->draw_circle(x0, y0, r, c);
}
void GUI::drawArc( uint16_t x0, uint16_t y0, uint16_t r, uint8_t s, E_COLOR c ){
    int16_t x, y, xd, yd, e;

    if ( x0 < 0 ) return;
    if ( y0 < 0 ) return;
    if ( r <= 0 ) return;

    xd = 1 - (r << 1);
    yd = 0;
    e = 0;
    x = r;
    y = 0;

    while ( x >= y )
    {
        // Q1
        if ( s & 0x01 ) _pDev->draw_pixel(x0 + x, y0 - y, c);
        if ( s & 0x02 ) _pDev->draw_pixel(x0 + y, y0 - x, c);

        // Q2
        if ( s & 0x04 ) _pDev->draw_pixel(x0 - y, y0 - x, c);
        if ( s & 0x08 ) _pDev->draw_pixel(x0 - x, y0 - y, c);

        // Q3
        if ( s & 0x10 ) _pDev->draw_pixel(x0 - x, y0 + y, c);
        if ( s & 0x20 ) _pDev->draw_pixel(x0 - y, y0 + x, c);

        // Q4
        if ( s & 0x40 ) _pDev->draw_pixel(x0 + y, y0 + x, c);
        if ( s & 0x80 ) _pDev->draw_pixel(x0 + x, y0 + y, c);

        y++;
        e += yd;
        yd += 2;
        if ( ((e << 1) + xd) > 0 )
        {
            x--;
            e += xd;
            xd += 2;
        }
    }
}
void GUI::drawLine( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, E_COLOR c ){

	if(y2==y1) _pDev->draw_h_line(x1,y1,_getXend(x2)-x1,c);
		else if(x2==x1) _pDev->draw_v_line(x1,y1,_getYend(y2)-y1,c);
		else _drawLine(x1,y1,x2,y2,c);
}

void GUI::_drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, E_COLOR c){
    int dx,             // difference in x's
        dy,             // difference in y's
        dx2,            // dx,dy * 2
        dy2,
        x_inc,          // amount in pixel space to move during drawing
        y_inc,          // amount in pixel space to move during drawing
        error,          // the discriminant i.e. error i.e. decision variable
        index;          // used for looping

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
            _pDev->draw_pixel(x0, y0, c);

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
            _pDev->draw_pixel(x0, y0, c);

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

void GUI::drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR bcolor,E_COLOR fcolor){
    int16_t i, j, byteWidth = (w + 7) / 8;
    uint8_t byte; uint8_t flag=1;
		if(_pT->disp.mode == DispMode_Rev) swap(&bcolor,&fcolor);
//		else 
//			if(_pT->disp.mode == DispMode_Trans) flag=0;
    for(j = 0; j < h; j++)
    {
        for(i = 0; i < w; i++)
        {
            if(i & 7) byte <<= 1;
            else      byte   = *(bitmap + j * byteWidth + i / 8);
            
						if(byte & 0x80){
							_pDev->draw_pixel(x + i, y + j, fcolor);
						}else{
//							if(_pT->disp.mode != DispMode_Trans)
						 	_pDev->draw_pixel(x + i, y + j, bcolor);
						}
        }
    }
}

void GUI::putText(TEXT_S *t,char *strs,uint8_t align)
{
	  uint16_t sl, rc, wl;
    int16_t xp, yp;

    char chr;

    char *str = strs;
    char *c = str;
		
		TEXT_S *old = _pT;
		_pT = t;

    if ( _pT->pAFont== NULL ) return;
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
		yp = _pT->disp.y + _getYAdjust(align,rc);
		_pT->DispPosY = yp;

    while( 1 )
    {
        sl = 0;
        c = str;
        wl = 0;
        while( (*c != 0) && (*c != '\n') )
        {
						// 如果当前字符不存在
            if (!(_pT->pAFont->pfIsInFont(_pT->pAFont,*c)))
            {
                c++;
                continue;
            }
            sl++; // 字符串长度						
            wl += _pT->pAFont->pfGetCharDistX(_pT->pAFont,*c);	// 字符串宽度
            c++;
        }

        xp = _pT->disp.x+_getXAdjust(align,wl+2);
				_pT->DispPosX = xp;
        while( (*str != '\n') )
        {
            chr = *str++;
            if ( chr == 0 ){
									_pT = old;
							return;}
							_dispChar(chr);
        }
        str++;
       _pT->DispPosY += _pT->pAFont->YDist;
    }
}

// 调整Y坐标,返回偏移量
int16_t GUI::_getYAdjust(uint8_t align,uint16_t h)
{
	switch (align & AlignFlag_Vertical) {
	case AlignMode_Bottom:
		return _pT->disp.h - _pT->pAFont->YSize * h;
	case AlignMode_Vcenter :
		return (_pT->disp.h -	_pT->pAFont->YSize * h)/2;
	case AlignMode_Top:
		return 	0;
	}
}

// 调整Y坐标,返回偏移量
int16_t GUI::_getXAdjust(uint8_t align,uint16_t stringWidth)
{
	switch (align & AlignFlag_Horizontal) {
	case AlignMode_Left:
		return 0;
	case AlignMode_Right:
		return _pT->disp.w - stringWidth - 3;
	case AlignMode_Center:
		return 	(_pT->disp.w - stringWidth)/2;
	}
}