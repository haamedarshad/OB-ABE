#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include </usr/include/glib-2.0/glib.h>
#include </usr/local/include/pbc/pbc.h>
#include </usr/local/include/pbc/pbc_random.h>

#include "bswabe.h"
#include "common.h"


char* pub_file = "pub_key";
char* msk_file = "master_key";
void setup(){
	bswabe_pub_t* pub;
	bswabe_msk_t* msk;
	bswabe_setup(&pub, &msk);
	spit_file(pub_file, bswabe_pub_serialize(pub), 1);
	spit_file(msk_file, bswabe_msk_serialize(msk), 1);
}
