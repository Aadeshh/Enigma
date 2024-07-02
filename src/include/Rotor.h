#ifndef ROTOR_H
#define ROTOR_H
#include <stddef.h>
#include "common.h"
#include  <stdlib.h>

/* Your definition of Rotor */
typedef struct {
    char mapping[MAX_SIZE];
    char reverse_mapping[MAX_SIZE];
    char *notch;
    size_t position;
    size_t ring_setting;
} Rotor;

Rotor* new_Rotor(const char* rotor, size_t ring_setting, size_t init);
char rotor_encrypt(Rotor* r, char c);
char rotor_encrypt_reverse(Rotor* r, char c);
int rotor_tick(Rotor* r);
size_t rotor_get_setting(Rotor* r);
void rotor_reset(Rotor* r, size_t new_setting);
void free_Rotor(Rotor* r);
#endif