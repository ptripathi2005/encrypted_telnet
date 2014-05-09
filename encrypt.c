/**
 * ****************************************************************************
 * * @File: encrypt.c
 * * @Brief: This file contains the encrytpion/decrytpion handling.
 * * @Revision History:
 * * 	     May2,2014;  Initial file commit
 * ****************************************************************************
 * */

#include "encrypt.h"

int encrypt(
    void* buffer,
    int buffer_len, /* Because the plaintext could include null bytes*/
    char* IV, 
    char* key,
    int key_len 
){
  MCRYPT td = mcrypt_module_open(MCRYPT_ENCRYPTION_SCHEME, NULL, "cbc", NULL);
  int blocksize = mcrypt_enc_get_block_size(td);
  if( buffer_len % blocksize != 0 ){return 1;}

  mcrypt_generic_init(td, key, key_len, IV);
  mcrypt_generic(td, buffer, buffer_len);
  mcrypt_generic_deinit (td);
  mcrypt_module_close(td);
  
  return 0;
}

int decrypt(
    void* buffer,
    int buffer_len,
    char* IV, 
    char* key,
    int key_len 
){
  MCRYPT td = mcrypt_module_open(MCRYPT_ENCRYPTION_SCHEME, NULL, "cbc", NULL);
  int blocksize = mcrypt_enc_get_block_size(td);
  if( buffer_len % blocksize != 0 ){return 1;}
  
  mcrypt_generic_init(td, key, key_len, IV);
  mdecrypt_generic(td, buffer, buffer_len);
  mcrypt_generic_deinit (td);
  mcrypt_module_close(td);
  
  return 0;
}

void display(char* ciphertext, int len){
  int i = 0;
  for (i = 0; i < len; i++){
    printf("%d ", ciphertext[i]);
  }
  printf("\n");
}

int sym_encrypt(char* buffer,  bool flag)
{
  char* IV = INIT_VECTOR;
  char *key = E_KEY;
  int keysize = KEY_LEN;
  int buffer_len = BUFFER_SIZE;
#ifdef PRINT_CIPHER
  printf("====\n");
#endif
if (flag == true) {
	encrypt(buffer, buffer_len, IV, key, keysize); 
#ifdef PRINT_CIPHER
  	printf("cipher:  "); display(buffer , buffer_len);
#endif
  }
  else {
  	decrypt(buffer, buffer_len, IV, key, keysize);
#ifdef PRINT_CIPHER
  	printf("decrypt: %s\n", buffer);
#endif
  }
  return 0;
}

