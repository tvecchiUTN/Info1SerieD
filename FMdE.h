#ifndef __FMDE_H
#define __FMDE_H

#include <stdint.h>


#define ON 1
#define OFF 0

//typedef unsigned char uint_8t;
//typedef unsigned int uint_32t;

void outDig (uint8_t port, uint8_t pin, uint8_t estado);

int inDig (uint8_t port, uint8_t pin);

int getInp (uint8_t port, uint8_t pin, uint8_t *valor);

int tiempo();


#endif
