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

void WINDOW::update(){
	  uint16_t i;
    GUI_COM *obj;

		//		_state &= ~obj_State_Update;
    /* Is the window visible? */
    if ( _state & obj_State_Visible )
    {		
				// 重画当前窗口
				if(_state & obj_State_ReDraw){
					_a.xs = _para.x;
					_a.ys = _para.y;
					_a.xe = _para.x+_para.w;
					_a.ye = _para.y+_para.h;
						/* 3D style? */
						if ( (_style & STYLE_3D) )
						{
								drawObjectFrame(&_a,(E_COLOR *)pal_window);
						}
						// 画标题
						if(_style & STYLE_SHOW_TITLE)
						{
								_drawTitle();
								_style &= ~STYLE_SHOW_TITLE;								
						}
						/* Draw window area? */
						_gui->fillFrameEx(_a.xs,_a.ys,_a.xe,_a.ye,_para.bc);
						_state &= ~obj_State_ReDraw;
				}
				
        // 更新窗口内组件
						for(i = 0; i < _componentList.size(); i++)
						{
						obj = (GUI_COM*)_componentList.data(i);
						if ( !(obj->_state & obj_State_Free) && (obj->_state & obj_State_Valid)/* && (obj->_state & obj_State_Visible) */){
							obj->update();
						}
        }
    }
    else
    {
			_gui->fillFrame(_para.x,_para.y,_para.w,_para.h,_gui->getBColor());
    }
}

void WINDOW::add(GUI_COM *com){
	_componentList.insert_tail(com);
	com->selectWindow(this);
}

void WINDOW::drawObjectFrame(AREA_S *a, E_COLOR *p){

	// Frame 0 
		_gui->drawLine(a->xs,a->ys,a->xe-1,a->ys,*p++);
		_gui->drawLine(a->xs,a->ys+1,a->xs,a->ye-1,*p++);
		_gui->drawLine(a->xs,a->ye,a->xe,a->ye,*p++);
		_gui->drawLine(a->xe,a->ys,a->xe,a->ye-1,*p++);
    // Frame 1
		_gui->drawLine(a->xs+1,a->ys+1,a->xe-2,a->ys+1,*p++);
		_gui->drawLine(a->xs+1,a->ys+2,a->xs+1,a->ye-2,*p++);
		_gui->drawLine(a->xs+1,a->ye-1,a->xe-1,a->ye-1,*p++);
		_gui->drawLine(a->xe-1,a->ys+1,a->xe-1,a->ye-2,*p++);
    // Frame 2
		_gui->drawLine(a->xs+2,a->ys+2,a->xe-3,a->ys+2,*p++);
		_gui->drawLine(a->xs+2,a->ys+3,a->xs+2,a->ye-3,*p++);
		_gui->drawLine(a->xs+2,a->ye-2,a->xe-2,a->ye-2,*p++);
		_gui->drawLine(a->xe-2,a->ys+2,a->xe-2,a->ye-3,*p++);
		// 修正坐标
		a->xs += 3;
		a->ys += 3;
		a->ye -= 3;
		a->xe -= 3;
}

void WINDOW::_drawTitle()
{
	  TEXT_SS txt;

    if (_state & obj_State_Valid) 
    {
        /* Draw title */
				_gui->fillFrameEx(_a.xs,_a.ys,_a.xe,_a.ys+_title.height-1,_title.bc);
        /* Draw title text */
        txt.pAFont = _title.font;
        txt.disp.x = _a.xs+1;
        txt.disp.y = _a.ys;
        txt.disp.w = _a.xe - _a.xs -2;
        txt.disp.h = _title.height - 1;
				txt.disp.bc = _title.bc;
				txt.disp.fc = _title.fc;
				txt.align = _title.align;
				txt.str = _title.str;
				_gui->ptxt(&txt);
        /* Draw line */
				_a.ys	+=	_title.height-1;
				_gui->drawLine(_a.xs,_a.ys,_a.xe,_a.ys, pal_window[11]);
				_a.ys += 1;
    }
}

void WINDOW::getWindow(AREA_S *a){
		a->xe = _a.xe;
		a->ye = _a.ye;
		a->xs = _a.xs;
		a->ys = _a.ys;
}
