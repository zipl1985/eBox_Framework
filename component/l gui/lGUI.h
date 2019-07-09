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

#ifndef __L_GUI_H
#define __L_GUI_H

#include "lgui_font.h"
#include "G_LCD_interface.h"
#include "TEXT_interface.h"


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

typedef struct {
  WND_S 			g;		// 图形属性
  TEXT_S    	t;  	// 文本属性
}GUI_T;

class GUI : public TEXTAPI
{
public: 
	GUI(GAPI *pG);
    
  void fillScreen( E_COLOR c );
  void fillFrame( uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, E_COLOR c );
  void fillRoundFrame( uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, uint16_t r, E_COLOR c );
  void drawMesh(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height,uint16_t gap, E_COLOR c );
  void drawFrame(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, E_COLOR c );
  void drawRoundFrame( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t r, E_COLOR c );
  void drawPixel( uint16_t x0, uint16_t y0, E_COLOR c );
  void drawCircle( uint16_t x0, uint16_t y0, uint16_t r, E_COLOR c );
  void fillCircle( uint16_t x0, uint16_t y0, uint16_t r, E_COLOR c );
  void drawArc( uint16_t x0, uint16_t y0, uint16_t r, uint8_t s, E_COLOR c );
  void drawLine( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, E_COLOR c );

	virtual void 		drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, E_COLOR bcolor,E_COLOR fcolor);

	
	E_COLOR	getBColor(){return _g.bc;}
	E_COLOR  getfColor(){return _g.fc;}
	int16_t		getWidth(){return  _g.w;}
	int16_t		getHeight(){return _g.h;}
	const GUI_FONT * getFont(){return _t.pAFont;}
private	:
	WND_S 	_g;
	TEXT_S  _t;
};
typedef enum{
	obj_State_Free 		= 0,
	obj_State_Valid		=	0x01,								// 有效
	obj_State_Busy		=	0x02,
	obj_State_Visible = 0x04,								// 可见
	obj_State_Enable	= 0x08,
	obj_State_Update	= 0x10,								// 更新
	obj_State_ReDraw	= 0x20,								// 重绘
	obj_State_Init		= (obj_State_Free|obj_State_Valid)
}State_e;

#include "list.h"

/* Window styles */
#define WND_STYLE_2D                                  (0<<0)
#define WND_STYLE_3D                                  (1<<0)
#define WND_STYLE_HIDE_TITLE                          (0<<1)
#define WND_STYLE_SHOW_TITLE                          (1<<1)

typedef struct
{
    char *str;
    const GUI_FONT *font;
    int8_t align;
    E_COLOR fc;
    E_COLOR bc;
    E_COLOR ifc;
    E_COLOR ibc;
    int8_t height;
}UG_TITLE;

class COMPONENT 
{
 public:

 	virtual void 	update(void) = 0;
	virtual void 	selectWindow(COMPONENT *wnd)= 0;
  virtual void 	show();
  virtual void 	hide();
	
	void  setForeColor(E_COLOR c);

public:
	E_COLOR     _bColor;
  E_COLOR     _fColor;
  int16_t    	_x;
  int16_t    	_y;
  int16_t    	_width;
  int16_t    	_height;
	uint16_t		_state;
};

class WINDOW:public COMPONENT{
public:
  WINDOW(GUI *g);
  virtual void 	show();
  virtual void 	hide();
	virtual void  update();


	void 		add(COMPONENT *com);
	E_COLOR getBColor(){return _bColor;};
	void  drawObjectFrame(int16_t x, int16_t y, int16_t width, int16_t height, E_COLOR *p );
	
	GUI * _gui;	
private:
	virtual void 	selectWindow(COMPONENT *wnd){};
	List	_componentList;

	uint8_t _style;
	UG_TITLE _title;
	void _drawTitle();
};



class LAB:public COMPONENT{
public:
	LAB(int16_t x,int16_t y,TEXT_S _lab,char* s);
	LAB(int16_t x,int16_t y,int16_t width,int16_t height,TEXT_S _lab,char* s);
	virtual void 	selectWindow(COMPONENT *wnd);
	virtual void  update();
	void setTxt(char * s){_lab.str = s;show();}
protected:
	TEXT_S _lab;
	WINDOW *_wnd;
};

/* Button states */
#define BTN_STATE_RELEASED                            (0<<0)
#define BTN_STATE_PRESSED                             (1<<0)
#define BTN_STATE_ALWAYS_REDRAW                       (1<<1)

/* Button style */
#define BTN_STYLE_2D                                  (0<<0)
#define BTN_STYLE_3D                                  (1<<0)
#define BTN_STYLE_TOGGLE_COLORS                       (1<<1)
#define BTN_STYLE_USE_ALTERNATE_COLORS                (1<<2)
#define BTN_STYLE_NO_BORDERS                          (1<<3)
#define BTN_STYLE_NO_FILL                             (1<<4)

class BOTTON:public LAB{
public:
	BOTTON(int16_t x,int16_t y,TEXT_S _lab,char* s);
	virtual void update();
private:
	uint8_t	_bState;
	uint8_t _style;
};

#endif
