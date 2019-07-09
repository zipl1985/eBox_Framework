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

void LAB::selectWindow(GUI_COM *wnd){
	_wnd = (WINDOW *)wnd;
	if(_lab.disp.bc == 0) _lab.disp.bc = _wnd->getBackColor() ;
	if(_lab.disp.fc == 0) _lab.disp.fc = _wnd->getForeColor();
}


void LAB::update(){
		TEXT_S t;
		t.disp = _lab.disp;
		t.pAFont = _lab.pAFont;
    if ( _state & obj_State_Update)
    {
        if ( _state & obj_State_Visible)
        {
            /* Full redraw necessary? */
            if ( _state & obj_State_ReDraw )
            {
								_wnd->_gui->fillFrame(_lab.disp.x, _lab.disp.y, _lab.disp.w, _lab.disp.h, _lab.disp.bc);

								/* Draw Textbox text */
								_wnd->_gui->putText(&t,_lab.str,_lab.align);
								_state &= ~obj_State_ReDraw;
            }
        } else
        {
           _wnd->_gui->fillFrame(_lab.disp.x, _lab.disp.y, _lab.disp.w, _lab.disp.h, _wnd->getBackColor());
        }
        _state &= ~obj_State_Update;
    }
}

