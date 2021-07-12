#include "EnclaveOBABE_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */
#include "sgx_lfence.h" /* for sgx_lfence */

#include <errno.h>
#include <mbusafecrt.h> /* for memcpy_s etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_ENCLAVE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_within_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define ADD_ASSIGN_OVERFLOW(a, b) (	\
	((a) += (b)) < (b)	\
)


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

static sgx_status_t SGX_CDECL sgx_ecall_EnclaveOBABE_sample(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_EnclaveOBABE_sample_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_EnclaveOBABE_sample_t* ms = SGX_CAST(ms_ecall_EnclaveOBABE_sample_t*, pms);
	sgx_status_t status = SGX_SUCCESS;



	ms->ms_retval = ecall_EnclaveOBABE_sample();


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_enc(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_enc_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_enc_t* ms = SGX_CAST(ms_ecall_enc_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	unsigned char* _tmp_In = ms->ms_In;
	size_t _tmp_len = ms->ms_len;
	size_t _len_In = _tmp_len;
	unsigned char* _in_In = NULL;
	unsigned char* _tmp_In2 = ms->ms_In2;
	size_t _len_In2 = _tmp_len;
	unsigned char* _in_In2 = NULL;

	CHECK_UNIQUE_POINTER(_tmp_In, _len_In);
	CHECK_UNIQUE_POINTER(_tmp_In2, _len_In2);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_In != NULL && _len_In != 0) {
		if ( _len_In % sizeof(*_tmp_In) != 0)
		{
			status = SGX_ERROR_INVALID_PARAMETER;
			goto err;
		}
		_in_In = (unsigned char*)malloc(_len_In);
		if (_in_In == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_In, _len_In, _tmp_In, _len_In)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}
	if (_tmp_In2 != NULL && _len_In2 != 0) {
		if ( _len_In2 % sizeof(*_tmp_In2) != 0)
		{
			status = SGX_ERROR_INVALID_PARAMETER;
			goto err;
		}
		if ((_in_In2 = (unsigned char*)malloc(_len_In2)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_In2, 0, _len_In2);
	}

	ms->ms_retval = ecall_enc(_in_In, _tmp_len, _in_In2);
	if (_in_In2) {
		if (memcpy_s(_tmp_In2, _len_In2, _in_In2, _len_In2)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}

err:
	if (_in_In) free(_in_In);
	if (_in_In2) free(_in_In2);
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_dec(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_dec_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_dec_t* ms = SGX_CAST(ms_ecall_dec_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	unsigned char* _tmp_In = ms->ms_In;
	size_t _tmp_len = ms->ms_len;
	size_t _len_In = _tmp_len;
	unsigned char* _in_In = NULL;
	unsigned char* _tmp_In2 = ms->ms_In2;
	size_t _len_In2 = _tmp_len;
	unsigned char* _in_In2 = NULL;

	CHECK_UNIQUE_POINTER(_tmp_In, _len_In);
	CHECK_UNIQUE_POINTER(_tmp_In2, _len_In2);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_In != NULL && _len_In != 0) {
		if ( _len_In % sizeof(*_tmp_In) != 0)
		{
			status = SGX_ERROR_INVALID_PARAMETER;
			goto err;
		}
		_in_In = (unsigned char*)malloc(_len_In);
		if (_in_In == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_In, _len_In, _tmp_In, _len_In)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}
	if (_tmp_In2 != NULL && _len_In2 != 0) {
		if ( _len_In2 % sizeof(*_tmp_In2) != 0)
		{
			status = SGX_ERROR_INVALID_PARAMETER;
			goto err;
		}
		if ((_in_In2 = (unsigned char*)malloc(_len_In2)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_In2, 0, _len_In2);
	}

	ms->ms_retval = ecall_dec(_in_In, _tmp_len, _in_In2);
	if (_in_In2) {
		if (memcpy_s(_tmp_In2, _len_In2, _in_In2, _len_In2)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}
	}

err:
	if (_in_In) free(_in_In);
	if (_in_In2) free(_in_In2);
	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv; uint8_t is_switchless;} ecall_table[3];
} g_ecall_table = {
	3,
	{
		{(void*)(uintptr_t)sgx_ecall_EnclaveOBABE_sample, 0, 0},
		{(void*)(uintptr_t)sgx_ecall_enc, 0, 0},
		{(void*)(uintptr_t)sgx_ecall_dec, 0, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[1][3];
} g_dyn_entry_table = {
	1,
	{
		{0, 0, 0, },
	}
};


sgx_status_t SGX_CDECL ocall_EnclaveOBABE_sample(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_EnclaveOBABE_sample_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_EnclaveOBABE_sample_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(str, _len_str);

	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (str != NULL) ? _len_str : 0))
		return SGX_ERROR_INVALID_PARAMETER;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_EnclaveOBABE_sample_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_EnclaveOBABE_sample_t));
	ocalloc_size -= sizeof(ms_ocall_EnclaveOBABE_sample_t);

	if (str != NULL) {
		ms->ms_str = (const char*)__tmp;
		if (_len_str % sizeof(*str) != 0) {
			sgx_ocfree();
			return SGX_ERROR_INVALID_PARAMETER;
		}
		if (memcpy_s(__tmp, ocalloc_size, str, _len_str)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_str);
		ocalloc_size -= _len_str;
	} else {
		ms->ms_str = NULL;
	}
	
	status = sgx_ocall(0, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

