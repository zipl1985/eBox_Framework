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
#include "gui.h"


WINDOW::WINDOW(GUI *g){
	_gui = g;	
  _paraInit(_gui->getWidth(),_gui->getHeight());
  setBackColor(0xEF7D);
  setForeColor(0x0000);
  _titleInit();

	_style = STYLE_3D | STYLE_SHOW_TITLE;
	_state = obj_State_Visible | obj_State_Update | obj_State_ReDraw | obj_State_Valid;
}

void WINDOW::_titleInit(){
  _title.align = AlignMode_Center | AlignMode_Vcenter;
	_title.height = 18;
	_title.bc = C_BLUE;
	_title.fc = C_WHITE;
	_title.str = "windows";
	_title.font = _gui->getFont();
}

void WINDOW::fillFrame(AREA_S *area, E_COLOR c){
	_gui->fillFrame(area->x, area->y, area->x+area->w, area->y+area->h, _para.bc);
}

void WINDOW::update(){
	  uint16_t i;
    GUI_COM *obj;

	_state &= ~obj_State_Update;
    /* Is the window visible? */
    if ( _state & obj_State_Visible )
    {
				if(_state & obj_State_ReDraw){
								  /* 3D style? */
						if ( (_style & STYLE_3D) )
						{
								drawObjectFrame(&_para,(E_COLOR *)pal_window);
						}
						// 画标题
						if(_style & STYLE_SHOW_TITLE)
						{
								_drawTitle();
								_style &= ~STYLE_SHOW_TITLE;
						}
												/* Draw window area? */
						fillFrame(&_para,_para.bc);
						_state &= ~obj_State_ReDraw;
				}
				
        /* Force each object to be updated! */
        for(i = 0; i < _componentList.size(); i++)
        {
            obj = (GUI_COM*)_componentList.data(i);
            if ( !(obj->_state & obj_State_Free) && (obj->_state & obj_State_Valid) && (obj->_state & obj_State_Visible) ){
							obj->_state |= (obj_State_Update | obj_State_ReDraw);
							obj->update();
						}
        }
    }
    else
    {
			fillFrame(&_para,_gui->getBColor());
    }
}

void WINDOW::add(GUI_COM *com){
	_componentList.insert_tail(com);
	com->selectWindow(this);
}

void WINDOW::drawObjectFrame(AREA_S *a, E_COLOR *p){
		int16_t x=a->x,y=a->y, xe = a->x + a->w ,ye = a->y + a->h;
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
		// 修正坐标
		_para.x += 3;
		_para.y += 3;
		_para.w -= 6;
		_para.h -= 6;
}

void WINDOW::_drawTitle()
{
	  TEXT_S txt;
    int16_t xs, ys, xe, ye;

    if (_state & obj_State_Valid) 
    {
        /* Draw title */
        _gui->fillFrame(_para.x, _para.y,_para.w, _para.y + _title.height-1, _title.bc);

        /* Draw title text */
//        txt.str = _title.str;
        txt.pAFont = _title.font;
        txt.disp.x = _para.x+1;
        txt.disp.y = _para.y+1;
        txt.disp.w = _para.w-1;
        txt.disp.h = _title.height - 1;
				txt.disp.bc = _title.bc;
				txt.disp.fc = _title.fc;
				_gui->putText(&txt,_title.str,_title.align);
        /* Draw line */
				_gui->drawLine(_para.x, _para.y + _title.height,_para.x+ _para.w, ys + _title.height, pal_window[11]);
				_para.y = _para.y +_title.height + 1;		//修正y坐标
				_para.h -= _para.y;
    }
}
