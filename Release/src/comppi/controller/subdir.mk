################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/comppi/controller/Builder.cc \
../src/comppi/controller/CheckLoc.cc \
../src/comppi/controller/CheckSource.cc \
../src/comppi/controller/Gexf.cc \
../src/comppi/controller/Interaction.cc \
../src/comppi/controller/Localization.cc \
../src/comppi/controller/Map.cc \
../src/comppi/controller/Namelist.cc \
../src/comppi/controller/Namelookup.cc 

OBJS += \
./src/comppi/controller/Builder.o \
./src/comppi/controller/CheckLoc.o \
./src/comppi/controller/CheckSource.o \
./src/comppi/controller/Gexf.o \
./src/comppi/controller/Interaction.o \
./src/comppi/controller/Localization.o \
./src/comppi/controller/Map.o \
./src/comppi/controller/Namelist.o \
./src/comppi/controller/Namelookup.o 

CC_DEPS += \
./src/comppi/controller/Builder.d \
./src/comppi/controller/CheckLoc.d \
./src/comppi/controller/CheckSource.d \
./src/comppi/controller/Gexf.d \
./src/comppi/controller/Interaction.d \
./src/comppi/controller/Localization.d \
./src/comppi/controller/Map.d \
./src/comppi/controller/Namelist.d \
./src/comppi/controller/Namelookup.d 


# Each subdirectory must supply rules for building sources it contributes
src/comppi/controller/%.o: ../src/comppi/controller/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDATABASE_MYSQL -DBOOST_LOG_DYN_LINK -I"/home/erenon/arbeit/c++/c++omppi/src" -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -Wno-unknown-pragmas -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MMD -MT "$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


