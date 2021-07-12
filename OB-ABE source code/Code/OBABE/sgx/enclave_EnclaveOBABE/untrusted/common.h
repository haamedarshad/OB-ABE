/*
Include glib.h and pbc.h before including this file.

This contains data structures and procedures common throughout the
tools.
*/
#include <openssl/aes.h>

/*
TODO if ssl sha1 not available, use built in one (sha1.c)
*/

char*       suck_file_str( char* file );
char*       suck_stdin();
GByteArray* suck_file( char* file );

void        spit_file( char* file, GByteArray* b, int free );

void read_cpabe_file( char* file,    GByteArray** cph_buf,
int* file_len, GByteArray** aes_buf );

void write_cpabe_file( char* file,   GByteArray* cph_buf,
int file_len, GByteArray* aes_buf );
///////////for OBABE
void read_cpabe_file_OBABE( char* file,    GByteArray** cph_buf,
int* file_len, GByteArray** aes_buf, GByteArray** kSgxAbe);
void write_cpabe_file_OBABE( char* file,   GByteArray* cph_buf,
int file_len, GByteArray* aes_buf, GByteArray* kSgxAbe);
///////////////////

void die(char* fmt, ...);

GByteArray* aes_128_cbc_encrypt( GByteArray* pt, element_t k );
GByteArray* aes_128_cbc_encrypt_3( GByteArray* pt, element_t k, unsigned int* keyArray);
GByteArray* aes_128_cbc_decrypt( GByteArray* ct, element_t k );
GByteArray* aes_128_cbc_decrypt_3( GByteArray* ct, unsigned int* keyArray );
