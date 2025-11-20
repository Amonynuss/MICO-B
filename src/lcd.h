#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class Lcd {
    private:
        LiquidCrystal lfd;

    public:
        Lcd();
};

#endif