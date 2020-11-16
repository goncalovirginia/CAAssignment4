
/**
 * AC - 2019/2020 MIEI FCT/UNL
 * 2020 vad
 **/
#include <stdio.h>
#include <unistd.h>

#include "hw.h"
#include "driver.h"

#define STATUS in(0x102)
#define READY 0b100

int sendByte(unsigned char c) {
    
    /* Waits until the printer is online (1), has paper (0) and isn't busy (0) */
    while (STATUS != READY);
    
    out(0x100, c); /* Copies the current byte to the BYTE_TX port */
    out(0x101, 1); /* Confirms and sends BYTE_TX to the printer */
    
    /* Checks if the printer is ready for the next byte */
    while (STATUS != READY) {
        if (!(STATUS & READY)) {
            return 0;
        }
    }
    
    return 1;
}
