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

int ecall_enc(unsigned char *In, size_t len,unsigned char *In2 );
int ecall_dec(unsigned char *In, size_t len, unsigned char *In2);

#if defined(__cplusplus)
}
#endif

#endif /* !_ENCLAVEOBABE_H_ */


