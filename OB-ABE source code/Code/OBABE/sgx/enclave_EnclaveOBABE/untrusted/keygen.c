#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include </usr/include/glib-2.0/glib.h>
#include </usr/include/glib-2.0/glib/gslist.h>
#include </usr/local/include/pbc/pbc.h>
#include </usr/local/include/pbc/pbc_random.h>

#include "bswabe.h"
#include "common.h"
#include "policy_lang.h"


char  pub_file_k[1000];
char  msk_file_k[1000];
char  out_file[1000];
char** attributes[1000];
//char** attributes[100];
char** attrs=0;

gint comp_string( gconstpointer a, gconstpointer b)
{
    return strcmp((char*)a, (char*)b);
}
void
parse_args_keygen(){
	int i;
	GSList* alist;
	GSList* ap;
	int n;
	int number=0;
	char* input[10];
	alist = 0;

	printf("Please enter the output name, public key, and master key\n");
	scanf("%s",out_file);
	scanf("%s",pub_file_k);
	scanf("%s",msk_file_k);
	/////////////////////////////////////////////////////////
	printf("How many attributes does this key have?\n");
	scanf("%d",&number);

	for(i=0;i<number;i++)
	{
		attributes[i] = (char*)malloc(10 * sizeof(char));
		printf("Please enter attribute number %i\n",i+1);
		scanf("%s",input);
		strcpy(attributes[i],input);
	}
}
int
keygen()
{
	bswabe_pub_t* pub;
	bswabe_msk_t* msk;
	bswabe_prv_t* prv;

	parse_args_keygen();

	pub = bswabe_pub_unserialize(suck_file(pub_file_k), 1);
	msk = bswabe_msk_unserialize(pub, suck_file(msk_file_k), 1);
	prv = bswabe_keygen(pub, msk, attributes);
	spit_file(out_file, bswabe_prv_serialize(prv), 1);

	return 0;
}
