
/****
 * hw - simulacao do hardware para IO e de controladores
 *    baseado nos exemplos das aulas com porta serie IBM/PC
 * AC - MIEI - FCT/UNL
 * 2018-2020 vad
 ****/

/* tipo BYTE que representa um byte (8bits)*/
typedef unsigned char BYTE;

/* iniciar simulador de IO e perifericos
 * args - indicar o ficheiro ou terminal que simula periferico
 *        ou NULL para usar o stdout e stdin do programa
 */
void hwInit( char *args );

/* simulacao das instrucoes IN e OUT do CPU */
BYTE in( int port );
void out( int port, BYTE data );

