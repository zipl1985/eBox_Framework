/**
  ******************************************************************************
  * @file    GUI_LAB.cpp
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

LAB::LAB(int16_t x,int16_t y,TEXT_S t,char* s){
		_pAFont = t.pAFont;
		_para.mode = t.disp.mode;
		_para.x = x;
		_para.y = y;
		_para.w = 50;
		_para.h = 20;
		_para.bc = t.disp.bc;
		_para.fc = t.disp.fc;
		_str = s;
		_state = obj_State_Valid|obj_State_ReDraw|obj_State_Visible|obj_State_Update;	
}

void LAB::selectWindow(GUI_COM *wnd){
	_wnd = (WINDOW *)wnd;
	if(_para.bc == 0) _para.bc = _wnd->getBackColor();
	if(_para.fc == 0) _para.fc = _wnd->getForeColor();
}


void LAB::update(){
		TEXT_SS t;
		AREA_S 	a;
		t.pAFont 	= _pAFont;
		t.align 	= _align;
		t.str 		= _str;
	
    if( _state & obj_State_Update){
				_wnd->getWindow(&a);
				// 修正坐标系,使用当前窗口相对坐标
				a.xs += _para.x;
				a.ys += _para.y;
        if( _state & obj_State_Visible)
        {
            /* Full redraw necessary? */
            if ( _state & obj_State_ReDraw )
            {
								_wnd->_gui->fillFrame(a.xs,a.ys,_para.w,_para.h,_para.bc);
								/* Draw Textbox text */
								_state &= ~obj_State_ReDraw;
            }
						t.disp = _para;
						t.disp.x = a.xs+1;
						t.disp.y = a.ys+1;
						t.disp.w = _para.w - 2;
						t.disp.h = _para.h - 2;
						_wnd->_gui->ptxt(&t);
        }else{
					_wnd->_gui->fillFrame(a.xs,a.ys,_para.w,_para.h,_wnd->getBackColor());
        }
        _state &= ~obj_State_Update;
    }
}

