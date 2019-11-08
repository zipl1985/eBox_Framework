/*
file   : *.cpp
author : shentq
version: V1.0
date   : 2015/7/5

Copyright 2015 shentq. All Rights Reserved.
*/

//STM32 RUN IN eBox


#include "ebox.h"

void setup()
{
    ebox_init();
		PA0.mode(OUTPUT_PP);
}
int main(void)
{
    setup();
    while(1)
    {		
				PA0.set();
        delay_ms(1000);
				PA0.reset();
    }
}




