#include "EnclaveOBABE_u.h"
#include <errno.h>

typedef struct ms_ecall_EnclaveOBABE_sample_t {
	int ms_retval;
} ms_ecall_EnclaveOBABE_sample_t;

typedef struct ms_ecall_enc_t {
	int ms_retval;
	unsigned char* ms_In;
	size_t ms_len;
	unsigned char* ms_In2;
} ms_ecall_enc_t;

typedef struct ms_ecall_dec_t {
	int ms_retval;
	unsigned char* ms_In;
	size_t ms_len;
	unsigned char* ms_In2;
} ms_ecall_dec_t;

typedef struct ms_ocall_EnclaveOBABE_sample_t {
	const char* ms_str;
} ms_ocall_EnclaveOBABE_sample_t;

static sgx_status_t SGX_CDECL EnclaveOBABE_ocall_EnclaveOBABE_sample(void* pms)
{
	ms_ocall_EnclaveOBABE_sample_t* ms = SGX_CAST(ms_ocall_EnclaveOBABE_sample_t*, pms);
	ocall_EnclaveOBABE_sample(ms->ms_str);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[1];
} ocall_table_EnclaveOBABE = {
	1,
	{
		(void*)EnclaveOBABE_ocall_EnclaveOBABE_sample,
	}
};
sgx_status_t ecall_EnclaveOBABE_sample(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_ecall_EnclaveOBABE_sample_t ms;
	status = sgx_ecall(eid, 0, &ocall_table_EnclaveOBABE, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t ecall_enc(sgx_enclave_id_t eid, int* retval, unsigned char* In, size_t len, unsigned char* In2)
{
	sgx_status_t status;
	ms_ecall_enc_t ms;
	ms.ms_In = In;
	ms.ms_len = len;
	ms.ms_In2 = In2;
	status = sgx_ecall(eid, 1, &ocall_table_EnclaveOBABE, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t ecall_dec(sgx_enclave_id_t eid, int* retval, unsigned char* In, size_t len, unsigned char* In2)
{
	sgx_status_t status;
	ms_ecall_dec_t ms;
	ms.ms_In = In;
	ms.ms_len = len;
	ms.ms_In2 = In2;
	status = sgx_ecall(eid, 2, &ocall_table_EnclaveOBABE, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

