#include "Reflector.h"
#include "common.h"
#include "stdlib.h"
#include "string.h"

#include "common.h"

Reflector* new_Reflector(const char* reflector) {
    Reflector* r = (Reflector*)malloc(sizeof(Reflector));
    if (!r) {
        return NULL;
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        r->mapping[i] = reflector[i] - 'A';
    }
    return r;
}

char reflector_encrypt(Reflector* r, char c) {
    if (c < 'A' || c > 'Z') {
        return c;
    }
    return r->mapping[c - 'A'] + 'A';
}

void free_Reflector(Reflector* r) {
    free(r);
}
