#ifndef __virtual_lcd_h
#define __virtual_lcd_h

#include "ebox_core.h"
#include "print.h"
#include "G_LCD_interface.h"

// 利用串口模拟屏幕

class VLcd : public GAPI
{
private:
    typedef struct
    {
        uint8_t 		*pixel;		//显存的入口指针
        uint8_t     width; 		//显示器宽度
        uint8_t     height;		//显示器高度
        uint32_t    mem_size;	//显存大小
    } Lcd_t;

public:
    VLcd(Print *p);
    ~VLcd();
    void    begin(uint16_t lcd_w, uint16_t lcd_h);
    void    set_xy(int16_t x, int16_t y);
    void    clear(uint32_t color);

    //重载Vhmi的接口
    virtual void    draw_pixel(int16_t x, int16_t y, uint32_t color);
    virtual void    fill_screen(uint32_t color);
		virtual void    flush();

private:
    Lcd_t   _lcd;
		Print		*_p;		//输出设备

    uint32_t _getPosition(int16_t x, int16_t y);		// 根据屏幕位置返回像素在内存位置		
};

#endif

