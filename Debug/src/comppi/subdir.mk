################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/comppi/comppi.cpp 

OBJS += \
./src/comppi/comppi.o 

CPP_DEPS += \
./src/comppi/comppi.d 


# Each subdirectory must supply rules for building sources it contributes
src/comppi/%.o: ../src/comppi/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDATABASE_MYSQL -DBOOST_LOG_DYN_LINK -I"/home/erenon/arbeit/c++/c++omppi/src" -O0 -g -Wall -c -fmessage-length=0 -std=c++11 -Wno-unknown-pragmas -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


