#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include "common.h"
#include <stddef.h>
#include  <stdlib.h>
/* Your definition of Plugboard */

// Encrypts a character using the plugboard.
void plugboard_encrypt(size_t num_pairs,const char* pairs, const char c,char *o);


#endif