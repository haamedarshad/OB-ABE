#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include </usr/include/glib-2.0/glib.h>
#include </usr/local/include/pbc/pbc.h>
#include </usr/local/include/pbc/pbc_random.h>

#include "bswabe.h"
#include "common.h"
#include "policy_lang.h"
#include "sample.h"
#include "EnclaveOBABE_u.h"

#include "time.h"

/////////////////////////////////////////////
/*typedef struct _GByteArray{
					  guint8 *data;
					  guint	  len;
					  guint   obg;
					};
*/
//#define GByteArray GByteArray2

////////NOTE: I have changed the definition of struct _GByteArray in garray.h. I have added "guint obg;"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char  pub_file_enc[1048576];
char  in_file_enc[1048576];
char  out_file_enc[1048576];
char* policy_enc[1000];
char* out_file_enc1 = 0;
char* policy = 0;
uint8_t bufferOut[100];

GByteArray* c2;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int scandata(){
	printf("Please enter the input file, public key, and policy\n");
	scanf("%s",in_file_enc);
	scanf("%s",pub_file_enc);
	scanf(" %[^\n]s",policy_enc);
	policy = parse_policy_lang(policy_enc);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int scanoblg(){

	int obg = 0;

	while (obg==0){

		printf("Please enter the obligation number\n1. Sending an email\n2. Writing a log\n3. Showing an error message\n");

		scanf("%d", &obg);

		if(obg==1){

			printf("An email will be sent!\n");

			obg = 17;

		}
		else if(obg==2){

			printf("A log will be written!\n");

			obg = 18;
		}
		else if(obg==3){

			printf("An error message will be shown!\n");

			obg=19;

		}
		else if(obg !=1 && obg != 2 && obg != 3 && obg != 0){

			printf("You have entered a wrong number!\n");

			obg =0;

		}
	}

	return obg;
}

///////////////////////////////////////////////////////////////////////////////

int encryption()
{
	bswabe_pub_t* pub;
	bswabe_cph_t* cph;
	int file_len;
	GByteArray* plt;
	GByteArray* cph_buf;
	GByteArray* c1;
	GByteArray* aes_buf;
	element_t m;

	int obopt=0;
	int obselected=0;

	int ret3;
	int ecall_return3 = 0;

	printf("Do you want to add obligations? 1. Yes\t2. No\n");

	while(obopt == 0){

		scanf("%d",&obopt);

		if(obopt == 1){

			printf("Encryption with obligations\n");

			obselected =scanoblg();

			scandata();

///////////////////////////////////////////////////////////////////////////////////
			clock_t begin1 = clock();
//////////////////////////////////////////////////////////////////////////////////

			pub = bswabe_pub_unserialize(suck_file(pub_file_enc), 1);
			if( !(cph = bswabe_enc(pub, m, policy)) )
				die("%s", bswabe_error());
				//free(policy_enc);
			cph_buf = bswabe_cph_serialize(cph);
			bswabe_cph_free(cph);
			plt = suck_file(in_file_enc);
			file_len = plt->len;

			plt->obg = obselected;
			c1 = g_byte_array_new();
			g_byte_array_set_size(c1,file_len);

			////Calling SGX.Encryption
			ret3 =	ecall_enc(global_eid, &ecall_return3, plt->data,file_len,c1->data);

			c2 = g_byte_array_new();
			g_byte_array_set_size(c2,file_len);
			c2=c1;
			aes_buf = aes_128_cbc_encrypt(c2, m);
			aes_buf->obg = plt->obg;
			cph_buf->obg = plt->obg;
			element_clear(m);

			///////////////////////////////////////////////////////////////////////////////////
			clock_t end1 = clock();
			///////////////////////////////////////////////////////////////////////////////////

			out_file_enc1 = g_strdup_printf("%s_ob.cpabe", in_file_enc);
			write_cpabe_file(out_file_enc1, cph_buf, file_len, aes_buf);

			g_byte_array_free(cph_buf, 1);
			g_byte_array_free(aes_buf, 1);

			printf("The results are stored in a file named '%s'\n", out_file_enc1);

			///////////////////////////////////////////////////////////////////////////////////
			double time_spent1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
			printf("The execution time with obligations is %f \n", time_spent1);
			///////////////////////////////////////////////////////////////////////////////////

		}
		else if(obopt == 2){

			printf("Encryption without obligations\n");

			scandata();

			///////////////////////////////////////////////////////////////////////////////////
			clock_t begin2 = clock();
			///////////////////////////////////////////////////////////////////////////////////

			pub = bswabe_pub_unserialize(suck_file(pub_file_enc), 1);

			if( !(cph = bswabe_enc(pub, m, policy)) )
				die("%s", bswabe_error());
				//free(policy_enc);

			cph_buf = bswabe_cph_serialize(cph);

			bswabe_cph_free(cph);

			plt = suck_file(in_file_enc);

			file_len = plt->len;

			aes_buf = aes_128_cbc_encrypt(plt, m);

			g_byte_array_free(plt, 1);

			element_clear(m);

			///////////////////////////////////////////////////////////////////////////////////
			clock_t end2 = clock();
			///////////////////////////////////////////////////////////////////////////////////

			out_file_enc1 = g_strdup_printf("%s.cpabe", in_file_enc);
			write_cpabe_file(out_file_enc1, cph_buf, file_len, aes_buf);
			g_byte_array_free(cph_buf, 1);
			g_byte_array_free(aes_buf, 1);

			printf("The results are stored in a file named '%s'\n", out_file_enc1);

			///////////////////////////////////////////////////////////////////////////////////
			double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
			printf("The execution time without obligations is %f\n", time_spent2);
			///////////////////////////////////////////////////////////////////////////////////

		}
		else{

			printf("You have entered a wrong number!\nPlease enter 1 if you want to add obligations or 2 if you do not want.\n");

			obopt =0;
		}
	}

	return 0;

	}
