################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/comppi/service/driver/map/Biogrid.cc \
../src/comppi/service/driver/map/ComppiStandard.cc 

OBJS += \
./src/comppi/service/driver/map/Biogrid.o \
./src/comppi/service/driver/map/ComppiStandard.o 

CC_DEPS += \
./src/comppi/service/driver/map/Biogrid.d \
./src/comppi/service/driver/map/ComppiStandard.d 


# Each subdirectory must supply rules for building sources it contributes
src/comppi/service/driver/map/%.o: ../src/comppi/service/driver/map/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDATABASE_MYSQL -DBOOST_LOG_DYN_LINK -I"/home/erenon/arbeit/c++/c++omppi/src" -O0 -g -Wall -c -fmessage-length=0 -std=c++11 -Wno-unknown-pragmas -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


