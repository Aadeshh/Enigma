#include "Rotor.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

Rotor* new_Rotor(const char* rotor, size_t ring_setting, size_t init) {
    Rotor* r = (Rotor*)malloc(sizeof(Rotor));
    if (!r){
        return NULL;
    }
    strncpy(r->mapping,rotor,26);
    for(size_t i = 0;i<26;i++){
        r->reverse_mapping[r->mapping[i] -'A'] = 'A' + i;
    }
    const char* notchStr = strchr(rotor,',')+1;
    size_t numNotches = strlen(notchStr);
    r->notch = (char*)malloc((numNotches+1)*sizeof(char));
    if(!r->notch){
        free(r);
        return NULL;
    }
    strncpy(r->notch,notchStr,numNotches);
    r->notch[numNotches] = '\0';
    r->ring_setting = ring_setting;
    r->position = init%26;
    return r;
}
char rotor_encrypt(Rotor* r, char c) {
    size_t input = (c - 'A' + r->position - r->ring_setting + 26) % 26;
    size_t output = (r->mapping[input]-'A' - r->position + r->ring_setting + 26) % 26;
    return 'A' + output;
}
char rotor_encrypt_reverse(Rotor* r, char c) {
    size_t input = (c - 'A' + r->position - r->ring_setting + 26) % 26;
    size_t output = (r->reverse_mapping[input]-'A'- r->position + r->ring_setting + 26) % 26;
    return 'A' + output;
}
int rotor_tick(Rotor* r) {
    r->position = (r->position+1)%26;
    for(size_t i = 0;r->notch[i] != '\0';i++){
        if (r->notch[i] == '\0'){
            continue;
        }
        if((char)r->notch[i] == ((char)('A' + ((r->position -1 + 26)%26)))){
            return 1;
        }
    }
    return 0;
}
void rotor_reset(Rotor* r, size_t new_setting) {
    r->position = new_setting;
}
size_t rotor_get_setting(Rotor* r) {
    return r->position;
}
void free_Rotor(Rotor* r) {
    free(r->notch);
    free(r);
}
