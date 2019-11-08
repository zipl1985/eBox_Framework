/**
  ******************************************************************************
  * @file    GUI_button.cpp
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


BOTTON::BOTTON(int16_t x,int16_t y,TEXT_S t,char* s):LAB(x,y,t,s){
	_bState = BTN_STATE_RELEASED;
	_style 	= STYLE_3D;
	_align	= AlignMode_Center | AlignMode_Vcenter;
}

void BOTTON::update(){
  uint8_t d;
  AREA_S	a;
  TEXT_SS txt;

  if ( _state & obj_State_Visible )
  {
    txt.str		= _str;
    txt.pAFont	=	_pAFont;
    txt.align		= _align;
    txt.disp.bc = _para.bc;
    txt.disp.fc = _para.fc;
		
    d = ( _style & BTN_STYLE_3D ) ? 3 : 1;
		// 修正坐标系,使用当前窗口相对坐标		
		_wnd->getWindow(&a);
		a.xs += _para.x;
		a.ys += _para.y;
    /* Full redraw necessary? */
    if ( (_state & obj_State_ReDraw) || (_bState & BTN_STATE_ALWAYS_REDRAW) )
    {
      if ( _bState & BTN_STATE_PRESSED ) 		swap(&_para.bc,&_para.fc);
      if ( !(_style & BTN_STYLE_NO_FILL))		_wnd->_gui->fillFrame(a.xs,a.ys,_para.w,_para.h,_para.bc);
      _state &= ~obj_State_ReDraw;
//#ifdef USE_POSTRENDER_EVENT
//                _UG_SendObjectPostrenderEvent(wnd, obj);
//#endif
    }
    /* Draw button text */
    txt.disp.x	= a.xs+d;
    txt.disp.y	= a.ys+d;
    txt.disp.w	= _para.w-(d<<1);
    txt.disp.h 	= _para.h-(d<<1);
    _wnd->_gui->ptxt(&txt);
    /* Draw button frame */
    if ( !(_style & BTN_STYLE_NO_BORDERS) )
    {
      a.xe = _para.w+a.xs;
      a.ye = _para.h+a.ys;

      if ( _style & BTN_STYLE_3D )
      {
        _wnd->drawObjectFrame(&a, (_bState & BTN_STATE_PRESSED) ? (E_COLOR *)pal_button_pressed : (E_COLOR *)pal_button_released);
      }
      else
      {
        _wnd->_gui->drawFrameEx(a.xs,a.xe,a.ys,a.ye,(_bState & BTN_STATE_PRESSED) ? _para.bc : _para.fc);
      }
    }
  }
  else
  {
    if ( !(_style & BTN_STYLE_NO_FILL) )
      _wnd->_gui->fillFrame(_para.x,_para.y,_para.w,_para.h, _para.bc);
  }
  _state &= ~obj_State_Update;
}
