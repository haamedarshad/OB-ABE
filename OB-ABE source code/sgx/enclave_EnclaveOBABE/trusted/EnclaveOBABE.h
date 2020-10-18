#ifndef _ENCLAVEOBABE_H_
#define _ENCLAVEOBABE_H_

#include <stdlib.h>
#include <assert.h>
#include "stdint.h"

#if defined(__cplusplus)
extern "C" {
#endif

void printf(const char *fmt, ...);

#if defined(__cplusplus)
}
#endif

#if defined(__cplusplus)
extern "C" {
#endif

//void ecall_enc(uint8_t In, size_t len, uint8_t Out);
int ecall_enc(char *In, size_t len, char *In2);
int ecall_dec(char *In, size_t len, char *In2);

//int ecall_enc(char *In, int *len);

#if defined(__cplusplus)
}
#endif

#endif /* !_ENCLAVEOBABE_H_ */


