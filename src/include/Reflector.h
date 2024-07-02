#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "common.h"
#include  <stdlib.h>
typedef struct {
    char mapping[MAX_SIZE];
} Reflector;
Reflector* new_Reflector(const char* reflector);
char reflector_encrypt(Reflector* r, char c);
void free_Reflector(Reflector* r);


#endif