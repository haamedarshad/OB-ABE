#include <assert.h>
#include <string.h>
#include <unistd.h>
#include </usr/include/glib-2.0/glib.h>
#include </usr/local/include/pbc/pbc.h>
#include </usr/local/include/pbc/pbc_random.h>
#include "bswabe.h"
#include "common.h"
#include "sample.h"
#include "time.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char  pub_file_dec[1050000];
char  in_file_dec[1050000];
char prv_file[1050000];
char* out_file_dec   = 0;

uint8_t bufferIn[100];

GByteArray* c2;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int scandata_dec(){
	printf("Please enter the input file, public key, and private key\n");
	scanf("%s",in_file_dec);
	scanf("%s",pub_file_dec);
	scanf("%s",prv_file);
	if(  strlen(in_file_dec) > 6 &&	!strcmp(in_file_dec + strlen(in_file_dec) - 6, ".cpabe") )
		out_file_dec = g_strndup(in_file_dec, strlen(in_file_dec) - 6);
	else
		out_file_dec = strdup(in_file_dec);

	return 0;
}
///////////////////////

int decryption( ){
	bswabe_pub_t* pub;
	bswabe_prv_t* prv;
	int file_len;
	GByteArray* aes_buf;
	GByteArray* plt;
	GByteArray* cph_buf;
	bswabe_cph_t* cph;
	element_t m;
	GByteArray* p1;
	GByteArray* ct1;
	int ret3dec;
	int ecall_return3 = 0;

	scandata_dec();

	///////////////////////////////////////////////////////////////////////////////////
	clock_t begin_d1 = clock();
	///////////////////////////////////////////////////////////////////////////////////

	pub = bswabe_pub_unserialize(suck_file(pub_file_dec), 1);

	prv = bswabe_prv_unserialize(pub, suck_file(prv_file), 1);

	read_cpabe_file(in_file_dec, &cph_buf, &file_len, &aes_buf);

	cph = bswabe_cph_unserialize(pub, cph_buf, 1);

	if( !bswabe_dec(pub, prv, cph, m) )
		die("%s", bswabe_error());
	bswabe_cph_free(cph);
	ct1 = aes_128_cbc_decrypt(aes_buf, m);
	g_byte_array_set_size(ct1, file_len);
	ct1->obg = aes_buf->obg;
	g_byte_array_free(aes_buf, 1);
	plt = g_byte_array_new();
	g_byte_array_set_size(plt, file_len);

	///////////////////////////////////////////////////////////////////////////////////
	clock_t end_d1 = clock();
	double time_spent_d1 = (double)(end_d1 - begin_d1) / CLOCKS_PER_SEC;
	printf("The execution time without obligations is %f\n", time_spent_d1);
	///////////////////////////////////////////////////////////////////////////////////
	c2 = g_byte_array_new();
	g_byte_array_set_size(c2,file_len);
//////////////////////////////////////////////////////////////////
if(ct1->obg == 17){

	printf("An email has been sent!\n");

	///////////////////////////////////////////////////////////////////////////////////
	clock_t begin_d2 = clock();
	//////////////////////////////////////////////////////////////////////////////////////
	//calling SGX.Decryption

	ret3dec = ecall_dec(global_eid, &ecall_return3, ct1->data,file_len,plt->data);
	c2=plt;

	///////////////////////////////////////////////////////////////////////////////////
	clock_t end_d2 = clock();
	double time_spent_d2 = (double)((end_d1 - begin_d1)+(end_d2 - begin_d2)) / CLOCKS_PER_SEC;
	printf("The execution time with obligations -email- is %f\n", time_spent_d2);
	///////////////////////////////////////////////////////////////////////////////////

	spit_file(out_file_dec, c2, 1);

}
else if(ct1->obg == 18){

	printf("A log has been written!\n");

	///////////////////////////////////////////////////////////////////////////////////
	clock_t begin_d3 = clock();
	///////////////////////////////////////////////////////////////////////////////////
	//calling SGX.Decryption

	ret3dec = ecall_dec(global_eid, &ecall_return3, ct1->data,file_len,plt->data);
	c2=plt;

	///////////////////////////////////////////////////////////////////////////////////
	clock_t end_d3 = clock();
	double time_spent_d3 = (double)((end_d1 - begin_d1)+(end_d3 - begin_d3)) / CLOCKS_PER_SEC;
	printf("The execution time with obligations -log- is %f\n", time_spent_d3);
	///////////////////////////////////////////////////////////////////////////////////

	spit_file(out_file_dec, c2, 1);

}
else if(ct1->obg == 19){

	printf("obligations show an error message!\n");

	///////////////////////////////////////////////////////////////////////////////////
	clock_t begin_d4 = clock();
	///////////////////////////////////////////////////////////////////////////////////
	//calling SGX.Decryption

	ret3dec = ecall_dec(global_eid, &ecall_return3, ct1->data,file_len,plt->data);
	c2=plt;

	///////////////////////////////////////////////////////////////////////////////////
	clock_t end_d4 = clock();
	double time_spent_d4 = (double)((end_d1 - begin_d1)+(end_d4 - begin_d4)) / CLOCKS_PER_SEC;
	printf("The execution time with obligations -error- is %f\n", time_spent_d4);
	///////////////////////////////////////////////////////////////////////////////////

	spit_file(out_file_dec, c2, 1);

}
else{

	printf("No valid obligations!\n");

	spit_file(out_file_dec, ct1, 1);
}

	return 0;
}
