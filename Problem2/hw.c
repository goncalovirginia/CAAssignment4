/**
 * AC - 2019/2020 MIEI FCT/UNL
 * 2018-2020 vad
 **/
#define _DEFAULT_SOURCE		// for usleep compatibility
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "hw.h"

#define MAXPORTS  0x400

/* configuracao dos ports dos perifericos */
static BYTE (*readPort[MAXPORTS])(void);  // operacoes para simular a sua leitura
static void (*writePort[MAXPORTS])(int);  // operacoes para simular a sua escrita


/************************************************************/

BYTE in( int port ) {
    return readPort[port]();  // ler do port
}

void out( int port, BYTE data ) {
    writePort[port]( data );  // escrever no port
}

/************************************************************/
/* internal registers for printer controler TPC4 2019/20    */

volatile BYTE DATA_TX = '?';
volatile BYTE CONTROL = 0;
volatile BYTE STATUS = 0;

/* Comands */
#define SEND  (1)  // send byte

/* Status bits */
#define BUSY    (1)    // bit 0
#define NOPAPER (2)    // bit 1
#define ONLINE  (4)    // bit 2

/***/
char *dev = NULL;   // device for input and output

pthread_cond_t dataready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *devSender( void *arg ) {      // output simulation
    // device is working...
    int nbytes = 0; // bytes printed
    FILE *outdev; 
    if ( dev == NULL ) outdev = stdout;
    else outdev = fopen( dev, "w" );
    if ( outdev == NULL ) {
        perror("dev: can't send");
    }

    while (1) {
        pthread_mutex_lock( &lock );
        while ( (STATUS & BUSY)==0) 
           pthread_cond_wait( &dataready, &lock ); // wait for work
        pthread_mutex_unlock( &lock );
        // do work
        //usleep( 200 );
        if ( nbytes>=700 ) {
            STATUS = 0;  // simulate offline (never goes online again)
        } else {
			fputc( DATA_TX, outdev );
			fflush( outdev );
			nbytes++;
            if ( nbytes%300 == 0 ) {
                STATUS = ONLINE | NOPAPER;  // simulate no paper
				usleep(400);
            } 
            STATUS = ONLINE;   // ready to print again
			usleep( 200 );
        }        
    }
}


void devInit( char *file ) {    // initialize simulator
    pthread_t tid;
    dev = file; // "/dev/tty" e' o proprio terminal onde executa
                // pode ser outro terminal: /dev/tty* (fazer sleep 999 nesse terminal)
                // ou pode usar ficheiros normais
 
    int status1 = pthread_create( &tid, NULL, devSender, NULL );

    if ( status1 != 0 ) {
        perror( "devInit: device failed to start!" );
	    exit(1);
    }
    STATUS = ONLINE;  // online
    //printf("IO ready!\n");
}


BYTE getStatus(void) {
    usleep(50);
    return STATUS;
    usleep(50);
}

void setData( BYTE data ) {
    usleep(1);
    DATA_TX = data;
}

void setControl( BYTE cmd ) {
    usleep(1);
    CONTROL = cmd;
    // do some work
    if (cmd == SEND) {
		pthread_mutex_lock(&lock);
        if (STATUS == ONLINE) { // only works if online, not busy and has paper
            // start sending
            STATUS = STATUS | BUSY;
            pthread_cond_signal(&dataready);
        } // else ignore byte
		pthread_mutex_unlock(&lock);
    } 
}

/******************************************************/


void none(void) { } // funcao que nao faz nada

void hwInit( char *args ) {
    /* iniciar o device semelhante a UART e registar os seus ports */
    devInit( args );
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
    readPort[0x100] = none;
    writePort[0x100] = setData;
    readPort[0x101] = none;
    writePort[0x101] = setControl;
    readPort[0x102] = getStatus;
    writePort[0x102] = none;
    // todos os outros ports deviam estar a none, mas vamos deixar abortar
    // para ser mais facil encontrar erros
    printf("hwInit done!\n");
}


/****/
// para compatibilidade:


//void sleepus(unsigned usec) {
//    struct timespec ts;
//    ts.tv_sec = usec/1000000;
//    ts.tv_nsec = (usec%1000000)*1000;
//    nanosleep(&ts, NULL);
//}

