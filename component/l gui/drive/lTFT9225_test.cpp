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
#include "parallel_gpio.h"
#include "ltft9225.h"
#include "dispchar.h"

/* 定义例程名和例程发布日期 */
#define EXAMPLE_NAME	"tft9225 lcd example"
#define EXAMPLE_DATE	"2019-06-15"

mcuGpio PF0(PF0_ID);
mcuGpio PF1(PF1_ID);

mcuGpio PF6(PF6_ID);
mcuGpio PF7(PF7_ID);

Port db(GPIOB_BASE,8);		// PB0-PB7
Lcd lcd(&PA12,&PB9, &PA15, &PF6, &PF7, &db);

TextInfo t;

TEXTAPI print(&lcd,&t);

void setup()
{
    ebox_init();
		
		UART.begin(115200);
		print_log(EXAMPLE_NAME, EXAMPLE_DATE);
		
		PF0.mode(OUTPUT_PP);
		PF0.set();
    lcd.begin();
    lcd.clear(WHITE);
//		lcd.off();
////		lcd.draw_pixel(10,10,BLACK);
//		lcd.on();

		t.TextAlign = GUI_TA_VCENTER;
    
		lcd.draw_h_line(0, 0, 220, BLUE);
		lcd.draw_v_line(0, 0, 176, RED);
		lcd.draw_h_line(0, 175, 220, BLUE);
		lcd.draw_v_line(219, 0, 176, RED);
    lcd.draw_circle(50, 50, 40, YELLOW);
    lcd.draw_line(0, 0, 175, 189, GREEN);
		lcd.fill_rect(100,120,10,20,GREEN);
		
		print.putChar('A');
		print.putString(0,0,"AA");
		print.printf(12,20,"AB %d \r\n",23);
		
		lcd.draw_circle(100, 80, 40, RED);
}

int main(void)
{
		uint16_t i = 0;
    setup();
    while(1)
    {
				print.printf(12,20,"AB %d \r\n",i++);
				delay_ms(1000);
    }
}


