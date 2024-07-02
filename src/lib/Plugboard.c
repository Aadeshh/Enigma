#include "Plugboard.h"
#include "common.h"
#include <stdio.h>
/* Your code to implement Plugboard here */

#include "Enigma.h"
#include <string.h>

void plugboard_encrypt(size_t num_pairs,const char* pairs, const char c,char *o) {
    *o = c;
    for(size_t i = 0; i < num_pairs ; i++){

        if(c == pairs[i*2])
        {
            *o = pairs[i*2+1];
            break;
        }
        else if(c == pairs[i*2+1])
        {
            *o = pairs[i*2];
            break;
        }
    }
    
}
