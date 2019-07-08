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
#include "dispchar.h"

#define USE_COLOR_RGB565
/* -------------------------------------------------------------------------------- */
/* -- μGUI COLORS                                                                -- */
/* -- Source: http://www.rapidtables.com/web/color/RGB_Color.htm                 -- */
/* -------------------------------------------------------------------------------- */
#ifdef USE_COLOR_RGB565
#define C_MAROON                       0x8000
#define C_DARK_RED                     0x8800
#define C_BROWN                        0xA145
#define C_FIREBRICK                    0xB104
#define C_CRIMSON                      0xD8A7
#define C_RED                          0xF800
#define C_TOMATO                       0xFB09
#define C_CORAL                        0xFBEA
#define C_INDIAN_RED                   0xCAEB
#define C_LIGHT_CORAL                  0xEC10
#define C_DARK_SALMON                  0xE4AF
#define C_SALMON                       0xF40E
#define C_LIGHT_SALMON                 0xFD0F
#define C_ORANGE_RED                   0xFA20
#define C_DARK_ORANGE                  0xFC60
#define C_ORANGE                       0xFD20
#define C_GOLD                         0xFEA0
#define C_DARK_GOLDEN_ROD              0xB421
#define C_GOLDEN_ROD                   0xDD24
#define C_PALE_GOLDEN_ROD              0xEF35
#define C_DARK_KHAKI                   0xBDAD
#define C_KHAKI                        0xEF31
#define C_OLIVE                        0x8400
#define C_YELLOW                       0xFFE0
#define C_YELLOW_GREEN                 0x9E66
#define C_DARK_OLIVE_GREEN             0x5346
#define C_OLIVE_DRAB                   0x6C64
#define C_LAWN_GREEN                   0x7FC0
#define C_CHART_REUSE                  0x7FE0
#define C_GREEN_YELLOW                 0xAFE6
#define C_DARK_GREEN                   0x0320
#define C_GREEN                        0x07E0
#define C_FOREST_GREEN                 0x2444
#define C_LIME                         0x07E0
#define C_LIME_GREEN                   0x3666
#define C_LIGHT_GREEN                  0x9772
#define C_PALE_GREEN                   0x97D2
#define C_DARK_SEA_GREEN               0x8DD1
#define C_MEDIUM_SPRING_GREEN          0x07D3
#define C_SPRING_GREEN                 0x07EF
#define C_SEA_GREEN                    0x344B
#define C_MEDIUM_AQUA_MARINE           0x6675
#define C_MEDIUM_SEA_GREEN             0x3D8E
#define C_LIGHT_SEA_GREEN              0x2595
#define C_DARK_SLATE_GRAY              0x328A
#define C_TEAL                         0x0410
#define C_DARK_CYAN                    0x0451
#define C_AQUA                         0x07FF
#define C_CYAN                         0x07FF
#define C_LIGHT_CYAN                   0xDFFF
#define C_DARK_TURQUOISE               0x0679
#define C_TURQUOISE                    0x46F9
#define C_MEDIUM_TURQUOISE             0x4E99
#define C_PALE_TURQUOISE               0xAF7D
#define C_AQUA_MARINE                  0x7FFA
#define C_POWDER_BLUE                  0xAEFC
#define C_CADET_BLUE                   0x64F3
#define C_STEEL_BLUE                   0x4C16
#define C_CORN_FLOWER_BLUE             0x64BD
#define C_DEEP_SKY_BLUE                0x05FF
#define C_DODGER_BLUE                  0x249F
#define C_LIGHT_BLUE                   0xAEBC
#define C_SKY_BLUE                     0x867D
#define C_LIGHT_SKY_BLUE               0x867E
#define C_MIDNIGHT_BLUE                0x18CE
#define C_NAVY                         0x0010
#define C_DARK_BLUE                    0x0011
#define C_MEDIUM_BLUE                  0x0019
#define C_BLUE                         0x001F
#define C_ROYAL_BLUE                   0x435B
#define C_BLUE_VIOLET                  0x897B
#define C_INDIGO                       0x4810
#define C_DARK_SLATE_BLUE              0x49F1
#define C_SLATE_BLUE                   0x6AD9
#define C_MEDIUM_SLATE_BLUE            0x7B5D
#define C_MEDIUM_PURPLE                0x939B
#define C_DARK_MAGENTA                 0x8811
#define C_DARK_VIOLET                  0x901A
#define C_DARK_ORCHID                  0x9999
#define C_MEDIUM_ORCHID                0xBABA
#define C_PURPLE                       0x8010
#define C_THISTLE                      0xD5FA
#define C_PLUM                         0xDD1B
#define C_VIOLET                       0xEC1D
#define C_MAGENTA                      0xF81F
#define C_ORCHID                       0xDB9A
#define C_MEDIUM_VIOLET_RED            0xC0B0
#define C_PALE_VIOLET_RED              0xDB92
#define C_DEEP_PINK                    0xF8B2
#define C_HOT_PINK                     0xFB56
#define C_LIGHT_PINK                   0xFDB7
#define C_PINK                         0xFDF9
#define C_ANTIQUE_WHITE                0xF75A
#define C_BEIGE                        0xF7BB
#define C_BISQUE                       0xFF18
#define C_BLANCHED_ALMOND              0xFF59
#define C_WHEAT                        0xF6F6
#define C_CORN_SILK                    0xFFBB
#define C_LEMON_CHIFFON                0xFFD9
#define C_LIGHT_GOLDEN_ROD_YELLOW      0xF7DA
#define C_LIGHT_YELLOW                 0xFFFB
#define C_SADDLE_BROWN                 0x8A22
#define C_SIENNA                       0x9A85
#define C_CHOCOLATE                    0xD344
#define C_PERU                         0xCC28
#define C_SANDY_BROWN                  0xF52C
#define C_BURLY_WOOD                   0xDDB0
#define C_TAN                          0xD591
#define C_ROSY_BROWN                   0xBC71
#define C_MOCCASIN                     0xFF16
#define C_NAVAJO_WHITE                 0xFEF5
#define C_PEACH_PUFF                   0xFED6
#define C_MISTY_ROSE                   0xFF1B
#define C_LAVENDER_BLUSH               0xFF7E
#define C_LINEN                        0xF77C
#define C_OLD_LACE                     0xFFBC
#define C_PAPAYA_WHIP                  0xFF7A
#define C_SEA_SHELL                    0xFFBD
#define C_MINT_CREAM                   0xF7FE
#define C_SLATE_GRAY                   0x7412
#define C_LIGHT_SLATE_GRAY             0x7453
#define C_LIGHT_STEEL_BLUE             0xAE1B
#define C_LAVENDER                     0xE73E
#define C_FLORAL_WHITE                 0xFFDD
#define C_ALICE_BLUE                   0xEFBF
#define C_GHOST_WHITE                  0xF7BF
#define C_HONEYDEW                     0xEFFD
#define C_IVORY                        0xFFFD
#define C_AZURE                        0xEFFF
#define C_SNOW                         0xFFDE
#define C_BLACK                        0x0000
#define C_DIM_GRAY                     0x6B4D
#define C_GRAY                         0x8410
#define C_DARK_GRAY                    0xAD55
#define C_SILVER                       0xBDF7
#define C_LIGHT_GRAY                   0xD69A
#define C_GAINSBORO                    0xDEDB
#define C_WHITE_SMOKE                  0xF7BE
#define C_WHITE                        0xFFFF
#endif

#ifdef USE_COLOR_RGB888
#define  C_MAROON                     0x800000
#define  C_DARK_RED                   0x8B0000
#define  C_BROWN                      0xA52A2A
#define  C_FIREBRICK                  0xB22222
#define  C_CRIMSON                    0xDC143C
#define  C_RED                        0xFF0000
#define  C_TOMATO                     0xFF6347
#define  C_CORAL                      0xFF7F50
#define  C_INDIAN_RED                 0xCD5C5C
#define  C_LIGHT_CORAL                0xF08080
#define  C_DARK_SALMON                0xE9967A
#define  C_SALMON                     0xFA8072
#define  C_LIGHT_SALMON               0xFFA07A
#define  C_ORANGE_RED                 0xFF4500
#define  C_DARK_ORANGE                0xFF8C00
#define  C_ORANGE                     0xFFA500
#define  C_GOLD                       0xFFD700
#define  C_DARK_GOLDEN_ROD            0xB8860B
#define  C_GOLDEN_ROD                 0xDAA520
#define  C_PALE_GOLDEN_ROD            0xEEE8AA
#define  C_DARK_KHAKI                 0xBDB76B
#define  C_KHAKI                      0xF0E68C
#define  C_OLIVE                      0x808000
#define  C_YELLOW                     0xFFFF00
#define  C_YELLOW_GREEN               0x9ACD32
#define  C_DARK_OLIVE_GREEN           0x556B2F
#define  C_OLIVE_DRAB                 0x6B8E23
#define  C_LAWN_GREEN                 0x7CFC00
#define  C_CHART_REUSE                0x7FFF00
#define  C_GREEN_YELLOW               0xADFF2F
#define  C_DARK_GREEN                 0x006400
#define  C_GREEN                      0x00FF00
#define  C_FOREST_GREEN               0x228B22
#define  C_LIME                       0x00FF00
#define  C_LIME_GREEN                 0x32CD32
#define  C_LIGHT_GREEN                0x90EE90
#define  C_PALE_GREEN                 0x98FB98
#define  C_DARK_SEA_GREEN             0x8FBC8F
#define  C_MEDIUM_SPRING_GREEN        0x00FA9A
#define  C_SPRING_GREEN               0x00FF7F
#define  C_SEA_GREEN                  0x2E8B57
#define  C_MEDIUM_AQUA_MARINE         0x66CDAA
#define  C_MEDIUM_SEA_GREEN           0x3CB371
#define  C_LIGHT_SEA_GREEN            0x20B2AA
#define  C_DARK_SLATE_GRAY            0x2F4F4F
#define  C_TEAL                       0x008080
#define  C_DARK_CYAN                  0x008B8B
#define  C_AQUA                       0x00FFFF
#define  C_CYAN                       0x00FFFF
#define  C_LIGHT_CYAN                 0xE0FFFF
#define  C_DARK_TURQUOISE             0x00CED1
#define  C_TURQUOISE                  0x40E0D0
#define  C_MEDIUM_TURQUOISE           0x48D1CC
#define  C_PALE_TURQUOISE             0xAFEEEE
#define  C_AQUA_MARINE                0x7FFFD4
#define  C_POWDER_BLUE                0xB0E0E6
#define  C_CADET_BLUE                 0x5F9EA0
#define  C_STEEL_BLUE                 0x4682B4
#define  C_CORN_FLOWER_BLUE           0x6495ED
#define  C_DEEP_SKY_BLUE              0x00BFFF
#define  C_DODGER_BLUE                0x1E90FF
#define  C_LIGHT_BLUE                 0xADD8E6
#define  C_SKY_BLUE                   0x87CEEB
#define  C_LIGHT_SKY_BLUE             0x87CEFA
#define  C_MIDNIGHT_BLUE              0x191970
#define  C_NAVY                       0x000080
#define  C_DARK_BLUE                  0x00008B
#define  C_MEDIUM_BLUE                0x0000CD
#define  C_BLUE                       0x0000FF
#define  C_ROYAL_BLUE                 0x4169E1
#define  C_BLUE_VIOLET                0x8A2BE2
#define  C_INDIGO                     0x4B0082
#define  C_DARK_SLATE_BLUE            0x483D8B
#define  C_SLATE_BLUE                 0x6A5ACD
#define  C_MEDIUM_SLATE_BLUE          0x7B68EE
#define  C_MEDIUM_PURPLE              0x9370DB
#define  C_DARK_MAGENTA               0x8B008B
#define  C_DARK_VIOLET                0x9400D3
#define  C_DARK_ORCHID                0x9932CC
#define  C_MEDIUM_ORCHID              0xBA55D3
#define  C_PURPLE                     0x800080
#define  C_THISTLE                    0xD8BFD8
#define  C_PLUM                       0xDDA0DD
#define  C_VIOLET                     0xEE82EE
#define  C_MAGENTA                    0xFF00FF
#define  C_ORCHID                     0xDA70D6
#define  C_MEDIUM_VIOLET_RED          0xC71585
#define  C_PALE_VIOLET_RED            0xDB7093
#define  C_DEEP_PINK                  0xFF1493
#define  C_HOT_PINK                   0xFF69B4
#define  C_LIGHT_PINK                 0xFFB6C1
#define  C_PINK                       0xFFC0CB
#define  C_ANTIQUE_WHITE              0xFAEBD7
#define  C_BEIGE                      0xF5F5DC
#define  C_BISQUE                     0xFFE4C4
#define  C_BLANCHED_ALMOND            0xFFEBCD
#define  C_WHEAT                      0xF5DEB3
#define  C_CORN_SILK                  0xFFF8DC
#define  C_LEMON_CHIFFON              0xFFFACD
#define  C_LIGHT_GOLDEN_ROD_YELLOW    0xFAFAD2
#define  C_LIGHT_YELLOW               0xFFFFE0
#define  C_SADDLE_BROWN               0x8B4513
#define  C_SIENNA                     0xA0522D
#define  C_CHOCOLATE                  0xD2691E
#define  C_PERU                       0xCD853F
#define  C_SANDY_BROWN                0xF4A460
#define  C_BURLY_WOOD                 0xDEB887
#define  C_TAN                        0xD2B48C
#define  C_ROSY_BROWN                 0xBC8F8F
#define  C_MOCCASIN                   0xFFE4B5
#define  C_NAVAJO_WHITE               0xFFDEAD
#define  C_PEACH_PUFF                 0xFFDAB9
#define  C_MISTY_ROSE                 0xFFE4E1
#define  C_LAVENDER_BLUSH             0xFFF0F5
#define  C_LINEN                      0xFAF0E6
#define  C_OLD_LACE                   0xFDF5E6
#define  C_PAPAYA_WHIP                0xFFEFD5
#define  C_SEA_SHELL                  0xFFF5EE
#define  C_MINT_CREAM                 0xF5FFFA
#define  C_SLATE_GRAY                 0x708090
#define  C_LIGHT_SLATE_GRAY           0x778899
#define  C_LIGHT_STEEL_BLUE           0xB0C4DE
#define  C_LAVENDER                   0xE6E6FA
#define  C_FLORAL_WHITE               0xFFFAF0
#define  C_ALICE_BLUE                 0xF0F8FF
#define  C_GHOST_WHITE                0xF8F8FF
#define  C_HONEYDEW                   0xF0FFF0
#define  C_IVORY                      0xFFFFF0
#define  C_AZURE                      0xF0FFFF
#define  C_SNOW                       0xFFFAFA
#define  C_BLACK                      0x000000
#define  C_DIM_GRAY                   0x696969
#define  C_GRAY                       0x808080
#define  C_DARK_GRAY                  0xA9A9A9
#define  C_SILVER                     0xC0C0C0
#define  C_LIGHT_GRAY                 0xD3D3D3
#define  C_GAINSBORO                  0xDCDCDC
#define  C_WHITE_SMOKE                0xF5F5F5
#define  C_WHITE                      0xFFFFFF
#endif

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
