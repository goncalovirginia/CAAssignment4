
/**
 * AC - 2019/2020 MIEI FCT/UNL
 * 2018-2020 vad
 **/
/* programa so' para testar o driver
 */
#include <stdio.h>

#include "hw.h"
#include "driver.h"


int main() {
    char *str = "String de teste!\nCorreu bem?\n";

    hwInit("/dev/tty");
    // a string enviada deve aparecer correta no stdout (ecra)
    while ( *str!='\0')
       if ( !sendByte( *str++ ) ) {
           printf("\nPrinter offline\n");
           return 0;
       }
    return 0;
}
