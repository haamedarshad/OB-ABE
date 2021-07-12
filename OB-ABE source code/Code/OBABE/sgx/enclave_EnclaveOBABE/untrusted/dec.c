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

//////////
FILE *timeFile;
#define CLOCKS_PER_SEC  ((__clock_t) 1000000)
/////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char  pub_file_dec[1050000];
char  in_file_dec[1050000];
char prv_file[1050000];
char* out_file_dec   = 0;
int extension=0;

uint8_t bufferIn[100];

GByteArray* c2;
typedef struct bswabe_pub_s bswabe_pub_t;

struct bswabe_pub_s {
           char* pairing_desc;
           pairing_t p;
           element_t g;           /* G_1 */
          element_t h;           /* G_1 */
          element_t gp;          /* G_2 */
          element_t g_hat_alpha; /* G_T */
  };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int scandata_dec(){
printf("Please enter the input file, public key, and private key\n");
scanf("%s",in_file_dec);
scanf("%s",pub_file_dec);
scanf("%s",prv_file);
if(  strlen(in_file_dec) > 6 && !strcmp(in_file_dec + strlen(in_file_dec) - 6, ".cpabe") ){
	out_file_dec = g_strndup(in_file_dec, strlen(in_file_dec) - 6);
	extension=1;
}else if( strlen(in_file_dec) > 6 && !strcmp(in_file_dec + strlen(in_file_dec) - 6, ".obabe") ){
	out_file_dec = g_strndup(in_file_dec, strlen(in_file_dec) - 6);
	extension=2;
}else
	out_file_dec = strdup(in_file_dec);

return 0;
}
//////////////////////////

int decryption( ){
bswabe_pub_t* pub;
bswabe_prv_t* prv;
int file_len;
GByteArray* aes_buf;
GByteArray* kSgxAbe;
GByteArray* plt;
GByteArray* plt2;
GByteArray* cph_buf;
GByteArray* e1;
bswabe_cph_t* cph;
element_t m;
int ret3dec;
int ecall_return3 = 0;

scandata_dec();

///////////////////////////////////////////////////////////////////////////////////

pub = bswabe_pub_unserialize(suck_file(pub_file_dec), 1);

prv = bswabe_prv_unserialize(pub, suck_file(prv_file), 1);

if(extension ==1){
	read_cpabe_file(in_file_dec, &cph_buf, &file_len, &aes_buf);

	cph = bswabe_cph_unserialize(pub, cph_buf, 1);

	if( !bswabe_dec(pub, prv, cph, m) )
		die("%s", bswabe_error());
	bswabe_cph_free(cph);
///////////////////////////////////////////////////////////////////////////////////
/////For time
/*
for(int t=0;t<100;t++)
{
clock_t begin1 = clock();
*/
//////////////////////////////////////////////////////////////////////////////////
	plt = aes_128_cbc_decrypt(aes_buf, m);
	g_byte_array_set_size(plt, file_len);
//	g_byte_array_free(aes_buf, 1);

///////////////////////////////////////////////////////////////////////////////////
//clock_t end1 = clock();
///////////////////////////////////////////////////////////////////////////////////

	spit_file(out_file_dec, plt, 1);

///////////////////////////////////////////////////////////////////////////////////
/*
double time_spent1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
printf("The execution time without obligations is %f \n", time_spent1);

timeFile = fopen("time-dec-without-obligation.txt", "a");
fprintf(timeFile,"%f\n", time_spent1);
}
*/
///////////////////////////////////////////////////////////////////////////////////

}
else if(extension ==2){

	read_cpabe_file_OBABE(in_file_dec, &cph_buf, &file_len,&aes_buf,&kSgxAbe);


///////////////////////////////////////////////////////////////
/////Decryption of the kSgxAbe suing ABE
///////////////////////////////////////////////////////////////
	cph = bswabe_cph_unserialize(pub, cph_buf, 1);
	if( !bswabe_dec(pub, prv, cph, m) )
		die("%s", bswabe_error());
	bswabe_cph_free(cph);

///////////////////////////////////////////////////////////////////////////////////
/////For time
/*
for(int t=0;t<100;t++)
{

clock_t begin2 = clock();
*/
//////////////////////////////////////////////////////////////////////////////////

	plt2 = g_byte_array_new();
	g_byte_array_set_size(plt2, 244);

	plt2 = aes_128_cbc_decrypt(kSgxAbe, m);


///////////////////////////////////////////////////////////////
/////Decryption of plt2 suing SGX (obtaining keyArray)
///////////////////////////////////////////////////////////////
	int file_len2 = plt2->len;
	e1 = g_byte_array_new();
	g_byte_array_set_size(e1, 244);

	ret3dec = ecall_dec(global_eid, &ecall_return3, plt2->data,file_len2,e1->data);

///////////////////////////////////////////////////////////////
/////Decryption of the original message using AES with keyArray
///////////////////////////////////////////////////////////////
/////////////////////////////////

	unsigned int keyArray2[61];

	memcpy(keyArray2, (int*)e1->data,244);

	int file_len3= aes_buf->len;

	plt = g_byte_array_new();
	g_byte_array_set_size(plt, file_len3);

	plt = aes_128_cbc_decrypt_3(aes_buf, keyArray2);

///////////////////////////////////////////////////////////////////////////////////
//clock_t end2 = clock();
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////

/////Writing the results in the output
///////////////////////////////////////////////////////////////
	spit_file(out_file_dec, plt, 1);
//unlink(in_file_dec);

///////////////////////////////////////////////////////////////////////////////////
/*
double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
printf("The execution time with obligations is %f \n", time_spent2);

timeFile = fopen("time-dec-with-obligation.txt", "a");
fprintf(timeFile,"%f\n", time_spent2);
}
*/
///////////////////////////////////////////////////////////////////////////////////

}

return 0;
}
