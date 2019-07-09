/**
  ******************************************************************************
  * @file    GUI.cpp
  * @author  cat_li
  * @brief   基本图形绘制
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
#include "lgui.h"
#include "ebox_config.h"
#include "bsp_ebox.h"

#if EBOX_DEBUG
// 是否打印调试信息, 1打印,0不打印
#define debug 1
#endif

#if debug
#define  tish(...) DBG("[gui]  "),DBG(__VA_ARGS__)
#else
#define  DEBUG(...)
#endif


GUI::GUI(GAPI *pG):TEXTAPI(pG,&_t){
	_g.bc = _t.disp.bc = 0xEF7D;
	_g.fc = _t.disp.fc = 0x0000;
	_g.mode = _t.disp.mode = DispMode_Normal;
  _g.w = _t.disp.w = _dev->getWidth();
  _g.h = _t.disp.h = _dev->getHeight();
}

void GUI::fillScreen( E_COLOR c ){
	_dev->fill_rect(_g.x,_g.y,_g.w,_g.h,c); 
}
void GUI::fillFrame(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, E_COLOR c ){
	_dev->fill_rect(x1,y1,width,height,c);
}
void GUI::fillRoundFrame( uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, uint16_t r, E_COLOR c ){
    int16_t  x, y, xd;

    if ( r <= 0 ) return;

    xd = 3 - (r << 1);
    x = 0;
    y = r;

    _dev->fill_rect(x1 + r, y1, width - r-r, height, c);

    while ( x <= y )
    {
        if( y > 0 )
        {
					_dev->draw_v_line(x1+width+x-r,y1-y+r,height-(r<<1)+(y<<1),c);
					_dev->draw_v_line(x1-x+r,y1-y+r,height-(r<<1)+(y<<1),c);
        }
        if( x > 0 )
        {
					_dev->draw_v_line(x1 - y + r, y1 - x + r,height+((x-r)<<1),c);
					_dev->draw_v_line(x1+width + y - r, y1 - x + r,height+((x-r)<<1),c);
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
           _dev->draw_pixel(x1, y1, c);
        }
    }
}
void GUI::drawFrame(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, E_COLOR c ){
  _dev->draw_h_line(x1,y1,width,c);
  _dev->draw_h_line(x1,y1+height,width,c);
  _dev->draw_v_line(x1,y1,height,c);
  _dev->draw_v_line(x1+width,y1,height,c);
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
  _dev->draw_pixel(x,y,c);
}
void GUI::drawCircle( uint16_t x0, uint16_t y0, uint16_t r, E_COLOR c ){
	_dev->draw_circle(x0,y0,r,c);
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
					_dev->draw_v_line(x0-x,y0-y,2*y,c);
					_dev->draw_v_line(x0+x,y0-y,2*y,c);
        }
        if( x > 0 )
        {
					_dev->draw_v_line(x0-y,y0-x,2*x,c);
					_dev->draw_v_line(x0+y,y0-x,2*x,c);
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
    _dev->draw_circle(x0, y0, r, c);
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
        if ( s & 0x01 ) _dev->draw_pixel(x0 + x, y0 - y, c);
        if ( s & 0x02 ) _dev->draw_pixel(x0 + y, y0 - x, c);

        // Q2
        if ( s & 0x04 ) _dev->draw_pixel(x0 - y, y0 - x, c);
        if ( s & 0x08 ) _dev->draw_pixel(x0 - x, y0 - y, c);

        // Q3
        if ( s & 0x10 ) _dev->draw_pixel(x0 - x, y0 + y, c);
        if ( s & 0x20 ) _dev->draw_pixel(x0 - y, y0 + x, c);

        // Q4
        if ( s & 0x40 ) _dev->draw_pixel(x0 + y, y0 + x, c);
        if ( s & 0x80 ) _dev->draw_pixel(x0 + x, y0 + y, c);

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
		if(y2==y1) _dev->draw_h_line(x1,y1,x2-x1,c);
		else if(x2==x1) _dev->draw_v_line(x1,y1,y2-y1,c);
		else _dev->draw_line(x1,y1,x2,y2,c);
}

void GUI::drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR bcolor,E_COLOR fcolor){
    int16_t i, j, byteWidth = (w + 7) / 8;
    uint8_t byte; uint8_t flag=1;
		if(_context->disp.mode == DispMode_Rev) swap(&bcolor,&fcolor);
//		else 
//			if(_context->disp.mode == DispMode_Trans) flag=0;
    for(j = 0; j < h; j++)
    {
        for(i = 0; i < w; i++)
        {
            if(i & 7) byte <<= 1;
            else      byte   = *(bitmap + j * byteWidth + i / 8);
            
						if(byte & 0x80){
							_dev->draw_pixel(x + i, y + j, fcolor);
						}else{
						 if(_context->disp.mode != DispMode_Trans)	_dev->draw_pixel(x + i, y + j, bcolor);
						}
        }
    }
}

void COMPONENT::show(){
		_state |= obj_State_Visible | obj_State_Update | obj_State_ReDraw;
}

void COMPONENT::hide(){
		_state &= ~obj_State_Visible;
		_state |= obj_State_Update;
}

WINDOW::WINDOW(GUI *g){
	_gui = g;	
	_title.align = AlignMode_Left;
	_title.height = 20;
	_title.bc = C_BLUE;
	_title.fc = C_WHITE;
	_title.str = "windows";
	_title.font = _gui->getFont();
	_style = WND_STYLE_2D | WND_STYLE_SHOW_TITLE;
	_bColor = 0xEF7D;
	_fColor = 0x0000;
	_state = obj_State_Visible | obj_State_Update | obj_State_ReDraw | obj_State_Valid;
	_width = _gui->getWidth();
	_height = _gui->getHeight();
}

void WINDOW::show(){
	_state |= obj_State_Visible | obj_State_Update;
//	_state &= ~WND_State_ReDrawTitle;  
}

void WINDOW::hide(){
		_gui->fillFrame(0,0,_width,_height,_bColor);
}

void WINDOW::update(){
	  uint16_t i;
    COMPONENT *obj;
    int16_t xs, ys, xe, ye;

    xs = _x;
    ys = _y;
    xe = _x+_width;
    ye = _y+_height;

    _state &= ~obj_State_Update;
    /* Is the window visible? */
    if ( _state & obj_State_Visible )
    {
			        /* 3D style? */
        if ( (_style & WND_STYLE_3D) && !(_state & obj_State_ReDraw) )
        {
						drawObjectFrame(xs, ys, xe, ye, (E_COLOR *)pal_window);
            xs += 3;
            ys += 3;
            xe -= 3;
            ye -= 3;
        }
				if(_state & obj_State_ReDraw){
						// 画标题
						if(_style & WND_STYLE_SHOW_TITLE)
						{
								_drawTitle();
								ys += _title.height + 1;
						}
						/* Draw window area? */
						_gui->fillFrame(xs, ys, xe, ye, _bColor);
						_state &= ~obj_State_ReDraw;
				}
        /* Force each object to be updated! */
        for(i = 0; i < _componentList.size(); i++)
        {
            obj = (COMPONENT*)_componentList.data(i);
            if ( !(obj->_state & obj_State_Free) && (obj->_state & obj_State_Valid) && (obj->_state & obj_State_Visible) ){
							obj->_state |= (obj_State_Update | obj_State_ReDraw);
							obj->update();
						}
        }
    }
    else
    {
        _gui->fillFrame(xs, ys, xe, ye,_gui->getBColor());
    }
}

void WINDOW::add(COMPONENT *com){
	_componentList.insert_tail(com);
	com->selectWindow(this);
}

void WINDOW::drawObjectFrame(int16_t x, int16_t y, int16_t width, int16_t height, E_COLOR *p){
		int16_t xe = x+width,ye = y+height;
	// Frame 0
		_gui->drawLine(x,y,xe-1,y,*p++);
		_gui->drawLine(x,y+1,x,ye-1,*p++);
		_gui->drawLine(x,ye,xe,ye,*p++);
		_gui->drawLine(xe,y,xe,ye-1,*p++);
    // Frame 1
		_gui->drawLine(x+1,y+1,xe-2,y+1,*p++);
		_gui->drawLine(x+1,y+2,x+1,ye-2,*p++);
		_gui->drawLine(x+1,ye-1,xe-1,ye-1,*p++);
		_gui->drawLine(xe-1,y+1,xe-1,ye-2,*p++);
    // Frame 2
		_gui->drawLine(x+2,y+2,xe-3,y+2,*p++);
		_gui->drawLine(x+2,y+3,x+2,ye-3,*p++);
		_gui->drawLine(x+2,ye-2,xe-2,ye-2,*p++);
		_gui->drawLine(xe-2,y+2,xe-2,ye-3,*p++);
}

void WINDOW::_drawTitle()
{
	  TEXT_S txt;
    int16_t xs, ys, xe, ye;

    if (_state & obj_State_Valid) 
    {
        xs = _x;
        ys = _y;
        xe = _x+_width;
        ye = _y+_height;

        /* Draw title */
        _gui->fillFrame(xs, ys, xe, ys + _title.height-1, _title.bc);

        /* Draw title text */
        txt.str = _title.str;
        txt.pAFont = _title.font;
        txt.disp.x = xs + 3;
        txt.disp.y = ys;
        txt.disp.w = _width;
        txt.disp.h = _title.height - 1;
				txt.disp.bc = _title.bc;
				txt.disp.fc = _title.fc;
        txt.disp.align = _title.align;
				_gui->putText(&txt);
        /* Draw line */
        _gui->drawLine(xs, ys + _title.height, xe, ys + _title.height, pal_window[11]);
    }
}

LAB::LAB(int16_t x,int16_t y,TEXT_S t,char* s){
		_lab.pAFont = t.pAFont;
		_lab.disp.mode = t.disp.mode;
		_lab.disp.x = x;
		_lab.disp.y = y;
		_lab.disp.w = 50;
		_lab.disp.h = 20;
		_lab.disp.bc = t.disp.bc;
		_lab.disp.fc = t.disp.fc;
		_lab.str = s;
		_state |= obj_State_Valid|obj_State_ReDraw|obj_State_Visible;	
}

void LAB::selectWindow(COMPONENT *wnd){
	_wnd = (WINDOW *)wnd;
	if(_lab.disp.bc == 0) _lab.disp.bc = _wnd->_bColor;
	if(_lab.disp.fc == 0) _lab.disp.fc = _wnd->_fColor;
}


void LAB::update(){
    if ( _state & obj_State_Update)
    {
        if ( _state & obj_State_Visible)
        {
            /* Full redraw necessary? */
            if ( _state & obj_State_ReDraw )
            {
								_wnd->_gui->fillFrame(_lab.disp.x, _lab.disp.y, _lab.disp.w, _lab.disp.h, _lab.disp.bc);

								/* Draw Textbox text */
								_wnd->_gui->putText(&_lab);
								_state &= ~obj_State_ReDraw;
            }
        } else
        {
           _wnd->_gui->fillFrame(_lab.disp.x, _lab.disp.y, _lab.disp.w, _lab.disp.h, _wnd->getBColor());
        }
        _state &= ~obj_State_Update;
    }
}

BOTTON::BOTTON(int16_t x,int16_t y,TEXT_S t,char* s):LAB(x,y,t,s){
	_x=x;
	_y = y;
	_width = 51;
	_height = 21;
	_bColor = C_BLUE;
	_fColor = C_WHITE;
	_bState = BTN_STATE_RELEASED;
	_lab.disp.align = AlignMode_Center | AlignMode_Vcenter;
	_style = BTN_STYLE_3D;
}

void BOTTON::update(){
		uint8_t d;
    if ( _state & obj_State_Update )
    {
        if ( _state & obj_State_Visible )
        {
            /* Full redraw necessary? */
            if ( (_state & obj_State_ReDraw) || (_bState & BTN_STATE_ALWAYS_REDRAW) )
            {
//                UG_WindowGetArea(wnd, &a);
//                obj->a_abs.xs = obj->a_rel.xs + a.xs;
//                obj->a_abs.ys = obj->a_rel.ys + a.ys;
//                obj->a_abs.xe = obj->a_rel.xe + a.xs;
//                obj->a_abs.ye = obj->a_rel.ye + a.ys;
//                if ( obj->a_abs.ye > wnd->ye ) return;
//                if ( obj->a_abs.xe > wnd->xe ) return;

                /* 3D or 2D style? */
                d = ( _style & BTN_STYLE_3D ) ? 3 : 1;

//                txt.bc = btn->bc;
//                txt.fc = btn->fc;

                if( _bState & BTN_STATE_PRESSED )
                {
                    /* "toggle" style? */
                    if( _style & BTN_STYLE_TOGGLE_COLORS )
                    {
                        /* Swap colors */
//                        txt.bc = btn->fc;
//                        txt.fc = btn->bc;
                    }
                    /* Use alternate colors? */
                    else if ( _style & BTN_STYLE_USE_ALTERNATE_COLORS )
                    {
//                        txt.bc = btn->abc;
//                        txt.fc = btn->afc;
                    }
                }
                if ( !(_style & BTN_STYLE_NO_FILL) )
										_wnd->_gui->fillFrame(160+d,110+d,50-d,20-d,_lab.disp.bc);

                /* Draw button text */
//                txt.a.xs = obj->a_abs.xs + d;
//                txt.a.ys = obj->a_abs.ys + d;
//                txt.a.xe = obj->a_abs.xe - d;
//                txt.a.ye = obj->a_abs.ye - d;
//                txt.align = btn->align;
//                txt.font = btn->font;
//                txt.h_space = 2;
//                txt.v_space = 2;
//                txt.str = btn->str;
								_wnd->_gui->putText(&_lab);
//                _UG_PutText( &txt );
                _state &= ~obj_State_ReDraw;
#ifdef USE_POSTRENDER_EVENT
                _UG_SendObjectPostrenderEvent(wnd, obj);
#endif
            }
            /* Draw button frame */
            if ( !(_style & BTN_STYLE_NO_BORDERS) )
            {
                if ( _style & BTN_STYLE_3D )
                {
                    /* 3D */
                 _wnd->drawObjectFrame(_x, _y, _width,_height, (_state & BTN_STATE_PRESSED) ? (E_COLOR *)pal_button_pressed : (E_COLOR *)pal_button_released);
                }
                else
                {
                    /* 2D */
									_wnd->_gui->drawFrame(_x,_y,_width,_height, (_state & BTN_STATE_PRESSED) ? _bColor : _fColor);
                }
            }
        }
        else
        {
            if ( !(_style & BTN_STYLE_NO_FILL) )
									_wnd->_gui->fillFrame(_x,_y,_width,_height, _bColor);
        }
        _state &= ~obj_State_Update;
    }
}

