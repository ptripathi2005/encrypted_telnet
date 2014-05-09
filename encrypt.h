#ifndef __ENCRYPT_H
#define __ENCRYPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mcrypt.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#undef PRINT_CIPHER

#define MCRYPT_ENCRYPTION_SCHEME MCRYPT_RIJNDAEL_128
#define INIT_VECTOR "AAAAAAAAAAAAAAAA" 
#define E_KEY "0123456789abcdef"
#define KEY_LEN 16
#define BUFFER_SIZE 16 

int sym_encrypt(char* buffer,  bool flag);

#endif
