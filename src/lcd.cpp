#include "lcd.h"

Lcd::Lcd() : lfd(8, 9, 4, 5, 6, 7) {
    lfd.begin(16, 2);
}