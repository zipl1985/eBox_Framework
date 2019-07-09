/**
  ******************************************************************************
  * @file    GUI.h
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

#ifndef __L_GUI_H
#define __L_GUI_H

#include "lgui_font.h"
#include "G_LCD_interface.h"
#include "graphic.h"
#include "TEXT_interface.h"
#include "gui_com.h"
#include "list.h"

#ifdef USE_COLOR_RGB565
const E_COLOR pal_window[] =
{
    0x632C,
    0x632C,
    0x632C,
    0x632C,

    0xFFFF,
    0xFFFF,
    0x6B4D,
    0x6B4D,

    0xE71C,
    0xE71C,
    0x9D13,
    0x9D13,
};

const E_COLOR pal_button_pressed[] =
{
    0x632C,
    0x632C,
    0x632C,
    0x632C,

    0x9D13,
    0x9D13,
    0x9D13,
    0x9D13,

    0xEF7D,
    0xEF7D,
    0xEF7D,
    0xEF7D,
};

const E_COLOR pal_button_released[] =
{
    0x632C,
    0x632C,
    0x632C,
    0x632C,

    0xFFFF,
    0xFFFF,
    0x6B4D,
    0x6B4D,

    0xE71C,
    0xE71C,
    0x9D13,
    0x9D13,
};
#endif

/* Window styles */
#define STYLE_2D                                  (0<<0)
#define STYLE_3D                                  (1<<0)
#define STYLE_HIDE_TITLE                          (0<<1)
#define STYLE_SHOW_TITLE                          (1<<1)
#define STYLE_3D_DRAW															(1<<2)


class WINDOW:public GUI_COM{
public:
  WINDOW(GUI *g);

	virtual void  update();

	void 		add(GUI_COM *com);	
	
	void  	drawObjectFrame(AREA_S *area, E_COLOR *p);
	void  	drawFrame(AREA_S *area, E_COLOR c);
	void  	fillFrame(AREA_S *area, E_COLOR c);
	
	GUI * _gui;	  // 图形接口
private:
	typedef struct
	{
			char *str;
			const GUI_FONT *font;
			int8_t align;
			E_COLOR fc;
			E_COLOR bc;
			int8_t height;
	}_TITLE;

	List	  _componentList;

	uint8_t _style;
	_TITLE  _title;
	void    _drawTitle();
  void    _titleInit();
  virtual void 	selectWindow(GUI_COM *wnd){};
  
};

class LAB:public TXT_COM{
public:
	LAB(int16_t x,int16_t y,TEXT_S _t,char* s);

	virtual void 	selectWindow(GUI_COM *wnd);
	virtual void  update();
	void setTxt(char * s){_lab.str = s;show();}
protected:
//	TEXT_S _lab;
//	char * str;
	WINDOW *_wnd;
};

// /* Button states */
// #define BTN_STATE_RELEASED                            (0<<0)
// #define BTN_STATE_PRESSED                             (1<<0)
// #define BTN_STATE_ALWAYS_REDRAW                       (1<<1)

// /* Button style */
// #define BTN_STYLE_2D                                  (0<<0)
// #define BTN_STYLE_3D                                  (1<<0)
// #define BTN_STYLE_TOGGLE_COLORS                       (1<<1)
// #define BTN_STYLE_USE_ALTERNATE_COLORS                (1<<2)
// #define BTN_STYLE_NO_BORDERS                          (1<<3)
// #define BTN_STYLE_NO_FILL                             (1<<4)

// class BOTTON:public LAB{
// public:
	// BOTTON(int16_t x,int16_t y,TEXT_S _lab,char* s);
	// virtual void update();
// private:
	// uint8_t	_bState;
	// uint8_t _style;
// };

#endif
