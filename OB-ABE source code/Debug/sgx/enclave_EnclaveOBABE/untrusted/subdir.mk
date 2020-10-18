################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sgx/enclave_EnclaveOBABE/untrusted/EnclaveOBABE_u.c \
../sgx/enclave_EnclaveOBABE/untrusted/common.c \
../sgx/enclave_EnclaveOBABE/untrusted/dec.c \
../sgx/enclave_EnclaveOBABE/untrusted/enc.c \
../sgx/enclave_EnclaveOBABE/untrusted/keygen.c \
../sgx/enclave_EnclaveOBABE/untrusted/policy_lang.c \
../sgx/enclave_EnclaveOBABE/untrusted/sample.c \
../sgx/enclave_EnclaveOBABE/untrusted/setup.c 

O_SRCS += \
../sgx/enclave_EnclaveOBABE/untrusted/EnclaveOBABE_u.o \
../sgx/enclave_EnclaveOBABE/untrusted/common.o \
../sgx/enclave_EnclaveOBABE/untrusted/dec.o \
../sgx/enclave_EnclaveOBABE/untrusted/enc.o \
../sgx/enclave_EnclaveOBABE/untrusted/keygen.o \
../sgx/enclave_EnclaveOBABE/untrusted/policy_lang.o \
../sgx/enclave_EnclaveOBABE/untrusted/sample.o \
../sgx/enclave_EnclaveOBABE/untrusted/setup.o 

OBJS += \
./sgx/enclave_EnclaveOBABE/untrusted/EnclaveOBABE_u.o \
./sgx/enclave_EnclaveOBABE/untrusted/common.o \
./sgx/enclave_EnclaveOBABE/untrusted/dec.o \
./sgx/enclave_EnclaveOBABE/untrusted/enc.o \
./sgx/enclave_EnclaveOBABE/untrusted/keygen.o \
./sgx/enclave_EnclaveOBABE/untrusted/policy_lang.o \
./sgx/enclave_EnclaveOBABE/untrusted/sample.o \
./sgx/enclave_EnclaveOBABE/untrusted/setup.o 

C_DEPS += \
./sgx/enclave_EnclaveOBABE/untrusted/EnclaveOBABE_u.d \
./sgx/enclave_EnclaveOBABE/untrusted/common.d \
./sgx/enclave_EnclaveOBABE/untrusted/dec.d \
./sgx/enclave_EnclaveOBABE/untrusted/enc.d \
./sgx/enclave_EnclaveOBABE/untrusted/keygen.d \
./sgx/enclave_EnclaveOBABE/untrusted/policy_lang.d \
./sgx/enclave_EnclaveOBABE/untrusted/sample.d \
./sgx/enclave_EnclaveOBABE/untrusted/setup.d 


# Each subdirectory must supply rules for building sources it contributes
sgx/enclave_EnclaveOBABE/untrusted/%.o: ../sgx/enclave_EnclaveOBABE/untrusted/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/opt/intel/sgxsdk/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


