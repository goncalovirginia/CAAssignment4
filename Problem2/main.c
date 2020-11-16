/**
 * AC - 2019/2020 MIEI FCT/UNL
 * 2018-2020 vad
 **/
/* teste do driver
 * le o ficheiro indicado e envia todo o seu conteudo para impressora
 * detecta se impressora fica offline
 */
#include <stdio.h>

#include "hw.h"  // so' para iniciar com hwInit
#include "driver.h"


int main(int argc, char *argv[]) {
    FILE *f;
    
    hwInit( "/dev/tty" );  // inicia hw

    // Verificar os argumentos da linha de comando
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Tentar abrir o ficheiro para leitura
    f=fopen (argv[1], "r");
    if (f== NULL) {
        printf("Invalid file: %s\n", argv[1]);
        return 1;
    }
 
	int c;
	int count = 0;
    // Ler os caracteres do ficheiro e "envia-os" 
    while ( (c=fgetc(f))!=EOF ) {
         if (!sendByte(c)) {
             printf("\nPrinter offline\n");
             break;
         } else count++;
    }
    printf("\nprinted %d bytes\n", count);
    // Fechar o ficheiro
    fclose(f);
    return 0;
}
