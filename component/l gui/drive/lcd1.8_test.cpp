/**
  ******************************************************************************
  * @file   : *.cpp
  * @author : shentq
  * @version: V1.2
  * @date   : 2016/08/14

  * @brief   ebox application example .
  *
  * Copyright 2016 shentq. All Rights Reserved.
  ******************************************************************************
 */


#include "ebox.h"
#include "bsp_ebox.h"
#include "lcd_1.8.h"
#include "text_interface.h"
#include "gui.h"
#include "Graphic.h"

/* 定义例程名和例程发布日期 */
#define EXAMPLE_NAME	"tft9225 lcd example"
#define EXAMPLE_DATE	"2019-06-15"

Lcd lcd(&PB5,&PB6,&PB4,&PB3,&spi1,128,160);
//Lcd lcd(&PA12,&PB9, &PA15, &PF6, &PF7, &db,220,176);

TEXT_S t;

TEXTAPI print(&lcd,&t);

GUI gui(&lcd);
WINDOW win(&gui);
LAB *l;
LAB *e;
//BOTTON *b;
//BOTTON *c;

void setup()
{
    ebox_init();
		
		UART.begin(115200);
		print_log(EXAMPLE_NAME, EXAMPLE_DATE);
		

    lcd.begin();
		gui.begin();
		gui.setDispMode(DispMode_Rev);
		gui.clear();
//    lcd.clear(WHITE);
//		lcd.off();
////		lcd.draw_pixel(10,10,BLACK);
//		lcd.on();

//		t.align = GUI_TA_VCENTER;
//   
			t.disp.bc = 0;
			t.disp.fc = 0;
//		lcd.draw_h_line(0, 0, 220, C_BLUE);
//		lcd.draw_v_line(0, 0, 176, C_RED);
//		lcd.draw_h_line(0, 175, 220, C_BLUE);
//		lcd.draw_v_line(219, 0, 176, C_RED);
//    lcd.draw_circle(50, 50, 40, C_YELLOW);
			gui.drawLine(1, 5, 236, 5, C_RED);
			gui.fillFrame(100,10,50,50,C_BLUE);
			gui.putString(10,10,"123456745679012345674567901234567456790123456745679012345674567901234567456790");
			gui.drawLine(2, 2, 175, 189, C_BLUE);
			gui.clear();
//		
//		print.putChar('A');
//		print.putString(0,0,"AA");
//		print.printf(12,20,"AB %d \r\n",23);
//	
//		lcd.draw_circle(100, 80, 40, C_RED);
		l = new LAB(50,30,t,"ceshi");
		e = new LAB(50,80,t,"webb");
//		b = new BOTTON(160,110,t,"b");
//		c = new BOTTON(100,110,t,"btn");
		win.add(l);
		win.add(e);
//		win.add(b);
////		win.add(c);
//print_log(EXAMPLE_NAME, EXAMPLE_DATE);
		win.show();
		win.update();
////		gui.putString(100,30,"nihao");
//		gui.drawFrame(30,30,50,50,C_ROSY_BROWN);
//		gui.drawCircle(100, 80, 42, C_BLACK);
//		gui.fillCircle(100,80,35,C_ROSY_BROWN);
//		gui.fillRoundFrame(30,90,50,50,10,C_RED);
//		gui.drawMesh(10,170,100,174,5,C_RED);
//		gui.putString(140,30,"nihao");
		delay_ms(3000);
}

int main(void)
{
		uint16_t i = 0;
    setup();
    while(1)
    {
//				print.printf(12,20,"AB %d \r\n",i++);
//				gui.printf(50,20,"AB %d \r\n",i++);
				l->setTxt("123");
				e->setTxt("nihao");
				win.update();
				delay_ms(2000);
				l->setTxt("126");
				e->setTxt("heihao");
				win.update();
				delay_ms(2000);
    }
}


