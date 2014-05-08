#ifndef __NETWORK_H
#define __NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mcrypt.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define MCRYPT_ENCRYPTION_SCHEME MCRYPT_RIJNDAEL_128
#define INIT_VECTOR "AAAAAAAAAAAAAAAA" 
#define E_KEY "0123456789abcdef"
#define KEY_LEN 16
#define BUFFER_SIZE 16 

int aes_encrypt(char* buffer,  bool flag);

#endif
