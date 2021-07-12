#ifndef ENCLAVEOBABE_U_H__
#define ENCLAVEOBABE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OCALL_ENCLAVEOBABE_SAMPLE_DEFINED__
#define OCALL_ENCLAVEOBABE_SAMPLE_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_EnclaveOBABE_sample, (const char* str));
#endif

sgx_status_t ecall_EnclaveOBABE_sample(sgx_enclave_id_t eid, int* retval);
sgx_status_t ecall_enc(sgx_enclave_id_t eid, int* retval, unsigned char* In, size_t len, unsigned char* In2);
sgx_status_t ecall_dec(sgx_enclave_id_t eid, int* retval, unsigned char* In, size_t len, unsigned char* In2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
