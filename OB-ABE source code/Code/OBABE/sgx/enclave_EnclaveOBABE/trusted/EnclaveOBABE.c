#include <stdarg.h>
#include <stdio.h>      /* vsnprintf */

#include "EnclaveOBABE.h"
#include "EnclaveOBABE_t.h"  /* print_string */
#include "sgx_trts.h"
#include "sgx_tcrypto.h"
#include "stdlib.h"
#include <string.h>


/*
 * printf:
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
void printf(const char *fmt, ...)
{
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_EnclaveOBABE_sample(buf);
}

int ecall_EnclaveOBABE_sample()
{
  printf("IN ENCLAVEOBABE\n");
  return 0;
}
/////////////
int ecall_enc(unsigned char *In,size_t len, unsigned char *In2){

	uint8_t *piv = 0;

	const uint8_t key[16] = {
	        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88,
	        0x09, 0xcf, 0x4f, 0x3c
    };

	const sgx_aes_ctr_128bit_key_t *k = &key;

	uint8_t ctr[16] = {
	        0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb,
	        0xfc, 0xfd, 0xfe, 0xff
    };

	uint8_t *ctrr = &ctr;
	uint32_t ctr_num_bit_size = 32;

	///Encryption inside SGX
	sgx_aes_ctr_encrypt(k,
						In,
						len,
						ctrr,
						ctr_num_bit_size,
						In2);
						
	return 0;

	}

/////////////////////////////////////////////////////////////////
int ecall_dec(unsigned char *In,size_t len, unsigned char *In2){

	uint8_t *piv = 0;

	const uint8_t key[16] = {
		        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88,
		        0x09, 0xcf, 0x4f, 0x3c
	};

	const sgx_aes_ctr_128bit_key_t *k = &key;

	uint8_t ctr[16] = {
		        0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb,
		        0xfc, 0xfd, 0xfe, 0xff
	};

	uint8_t *ctrr = &ctr;

	uint32_t ctr_num_bit_size = 32;

	//Decryption inside SGX
	sgx_aes_ctr_decrypt(k,
						In,
						len,
						ctrr,
						ctr_num_bit_size,
						In2);


	unsigned int keyArray4[61];

	memcpy(keyArray4, (int*)In2, 244);

	switch(keyArray4[60]){
	case 17:
		printf("An email is sent by the trusted hardware!\n");
		break;
	case 18:
		printf("A log is written by the trusted hardware!\n");
		break;
	case 19:
		printf("An error message is shown by the trusted hardware!\n");
		break;
    default:
        printf("The attached obligation is not defined in the trusted hardware!\n");
        break;
	}
	
	return 0;
}
