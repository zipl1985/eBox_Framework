#include "virtual_lcd.h"
#include "ebox_mem.h"
VLcd::VLcd(Print *p)
{
	_p = p;
};

VLcd::~VLcd()
{
    ebox_free(_lcd.pixel);
};
void VLcd::begin(uint16_t lcd_w, uint16_t lcd_h)
{
    _lcd.width = lcd_w;
    _lcd.height = lcd_h;
    _lcd.mem_size = sizeof(uint8_t) * _lcd.width * _lcd.height;
    _lcd.pixel = (uint8_t *)ebox_malloc(_lcd.mem_size);
    memset(_lcd.pixel, 0, _lcd.mem_size);

}
uint32_t VLcd::_getPosition(int16_t x, int16_t y)
{
    if(x < 0 || x >= _lcd.width)return -1 ;
    if(y < 0 || y >= _lcd.width)return -1 ;
    return x + y * _lcd.width;
}
void VLcd::set_xy(int16_t x, int16_t y)
{
    current_x = x;
    current_y = y;
}

void VLcd::draw_pixel(int16_t x, int16_t y, uint32_t color)
{
    if(x < 0 || x >= _lcd.width)return;
    if(y < 0 || y >= _lcd.width)return;

    uint32_t index = _getPosition(x, y);
		_lcd.pixel[index] = color;
}

void VLcd::fill_screen(uint32_t color)
{
    memset(_lcd.pixel, 0, _lcd.mem_size);

}
void VLcd::clear(uint32_t color)
{
    memset(_lcd.pixel, 0, _lcd.mem_size);
}

void VLcd::flush()
{
	  _p->print("   ");
    for(int x = 0; x < _lcd.width; x++)
    {
        _p->printf("%3d", x);
    }
    _p->println();
    for(int y = 0; y < _lcd.height; y++)
    {
        _p->printf("%2d", y);
        _p->print(" ");
        for(int x = 0; x < _lcd.width; x++)
        {
            if(_lcd.pixel != 0)
                _p->print("  *");
            else
                _p->print("   ");
        }
        _p->println();
    }
}
