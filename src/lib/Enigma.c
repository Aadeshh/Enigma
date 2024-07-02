#include "Enigma.h"
#include "EnigmaImpl.h"
#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"
#include <stdio.h>
#include "Enigma.h"
#include "EnigmaImpl.h"
#include  <stdlib.h>
#include <string.h>

Enigma* new_Enigma(size_t num_rotors, const char** rotors, size_t* rings,
                   size_t* inits, const char* reflector, size_t num_pairs,
                   const char* pairs) {
    Enigma* enigma = (Enigma*)malloc(sizeof(Enigma));
    if(enigma == NULL){
        return NULL;
    }
    enigma->reflector = new_Reflector(reflector);
    if(enigma->reflector == NULL){
        free_Enigma(enigma);
        return NULL;
    }
    enigma->rotors = (Rotor**)malloc(num_rotors * sizeof(Rotor*));
    if(enigma->rotors == NULL){
        free_Enigma(enigma);
        return NULL;
    }
    enigma->num_rotors = num_rotors;
    for (size_t i = 0; i < num_rotors; i++) {
        enigma->rotors[i] = new_Rotor(rotors[i], rings[i], inits[i]);
        if(enigma->rotors[i] == NULL){
            free_Enigma(enigma);
            return NULL;
        }
    }
    enigma->num_pairs = num_pairs;
    enigma->pairs = pairs;
    return enigma;
}
char* encrypt_Enigma(Enigma* self, char* dst, const char* src) {
    if(!self ||!dst ||!src ){
        return NULL;
    }
    strcpy(dst, src);
    tick_Enigma(self);
    while (*src) {
        char c = *src++;
        if(c == ' '){
            *dst++ = c;
            continue;
        }
        char o;
        plugboard_encrypt(self->num_pairs,self->pairs, c,&o);
        c = o;
        for (size_t i = 0; i < self->num_rotors; i++) {
            c = rotor_encrypt(self->rotors[i], c);
        }
        c = reflector_encrypt(self->reflector, c);
        for (size_t i = self->num_rotors; i > 0; i--) {
            c = rotor_encrypt_reverse(self->rotors[i - 1], c);
        }
        plugboard_encrypt(self->num_pairs,self->pairs, c,&o);
        c = o;
        *dst++ = c;
        tick_Enigma(self);
    }
    return dst;
}
void reset_rotor_Enigma(Enigma* self, size_t* new_setting) {
    for (size_t i = 0; i < self->num_rotors; i++) {
        rotor_reset(self->rotors[i], new_setting[i]);
    }
}
void free_Enigma(Enigma* self) {
    free_Reflector(self->reflector);
    for (size_t i = 0; i < self->num_rotors; i++) {
        free_Rotor(self->rotors[i]);
    }
    free(self->rotors);
    free(self);
}
void get_setting_Enigma(Enigma* self, char* ret) {
    for (size_t i = 0; i < self->num_rotors; i++) {
        ret[i] = 'A' + rotor_get_setting(self->rotors[i]);
    }
    ret[self->num_rotors] = '\0';
}
int rotor_is_at_notch(Rotor* r) {
    for (size_t i = 0; r->notch[i] != '\0'; i++) {
        if ((char)(r->notch[i]) == (char)('A' + r->position)) {
            return 1;
        }
    }
    return 0;
}
void tick_Enigma(Enigma* self) {
    if (!self || self->num_rotors == 0) {
        return;
    }
    //handle double step
    int first_rotor_notch = 0;
    int second_rotor_notch = 0;
    if (self->num_rotors > 1) {
        first_rotor_notch = rotor_is_at_notch(self->rotors[0]);
    }
    if (self->num_rotors > 2) {
        second_rotor_notch = rotor_is_at_notch(self->rotors[1]);
    }
    if (second_rotor_notch && self->num_rotors > 2) {
        rotor_tick(self->rotors[1]);
        rotor_tick(self->rotors[2]);
    }
    rotor_tick(self->rotors[0]);
    if (first_rotor_notch && self->num_rotors > 1) {
        rotor_tick(self->rotors[1]);
    }
}
void tick_n_Enigma(Enigma* self, size_t n) {
    for (size_t i = 0; i < n; i++) {
        tick_Enigma(self);
    }
}

