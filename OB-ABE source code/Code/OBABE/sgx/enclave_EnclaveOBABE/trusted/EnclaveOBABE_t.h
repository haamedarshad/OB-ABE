#ifndef ENCLAVEOBABE_T_H__
#define ENCLAVEOBABE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int ecall_EnclaveOBABE_sample(void);
int ecall_enc(unsigned char* In, size_t len, unsigned char* In2);
int ecall_dec(unsigned char* In, size_t len, unsigned char* In2);

sgx_status_t SGX_CDECL ocall_EnclaveOBABE_sample(const char* str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
