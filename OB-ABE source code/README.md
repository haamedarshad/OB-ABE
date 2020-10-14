* To test the prototype, the two following files are required:

  * sample (/OBABE code/OBABE/sgx/enclave_EnclaveOBABE/sample)

  * EnclaveOBABE.signed (/OBABE/sgx/enclave_EnclaveOBABE/EnclaveOBABE.signed)

* The definition of **struct _GByteArray** in *garray.h* file (/usr/include/glib-2.0/glib/garray.h) needs to be changed as follows:

    struct \_GByteArray
    {
      guint8 \*data;
      guint	len;
      guint obg;
    };

In other words, **guint obg;** is added to the definition of *struct _GByteArray*. 


* The code for the baseline CP-ABE scheme, which we have extended, is available at:
http://acsc.cs.utexas.edu/cpabe/#general
