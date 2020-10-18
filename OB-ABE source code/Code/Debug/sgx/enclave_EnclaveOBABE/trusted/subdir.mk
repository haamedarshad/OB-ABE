################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sgx/enclave_EnclaveOBABE/trusted/EnclaveOBABE.c \
../sgx/enclave_EnclaveOBABE/trusted/EnclaveOBABE_t.c 

O_SRCS += \
../sgx/enclave_EnclaveOBABE/trusted/EnclaveOBABE.o \
../sgx/enclave_EnclaveOBABE/trusted/EnclaveOBABE_t.o 

OBJS += \
./sgx/enclave_EnclaveOBABE/trusted/EnclaveOBABE.o \
./sgx/enclave_EnclaveOBABE/trusted/EnclaveOBABE_t.o 

C_DEPS += \
./sgx/enclave_EnclaveOBABE/trusted/EnclaveOBABE.d \
./sgx/enclave_EnclaveOBABE/trusted/EnclaveOBABE_t.d 


# Each subdirectory must supply rules for building sources it contributes
sgx/enclave_EnclaveOBABE/trusted/%.o: ../sgx/enclave_EnclaveOBABE/trusted/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/opt/intel/sgxsdk/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


