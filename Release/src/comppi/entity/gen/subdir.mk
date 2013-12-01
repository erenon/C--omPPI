################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
../src/comppi/entity/gen/Interaction-odb.cxx \
../src/comppi/entity/gen/Localization-odb.cxx \
../src/comppi/entity/gen/NameToProtein-odb.cxx \
../src/comppi/entity/gen/Protein-odb.cxx \
../src/comppi/entity/gen/ProteinName-odb.cxx \
../src/comppi/entity/gen/ProteinNameMap-odb.cxx \
../src/comppi/entity/gen/Species-odb.cxx \
../src/comppi/entity/gen/SystemType-odb.cxx 

OBJS += \
./src/comppi/entity/gen/Interaction-odb.o \
./src/comppi/entity/gen/Localization-odb.o \
./src/comppi/entity/gen/NameToProtein-odb.o \
./src/comppi/entity/gen/Protein-odb.o \
./src/comppi/entity/gen/ProteinName-odb.o \
./src/comppi/entity/gen/ProteinNameMap-odb.o \
./src/comppi/entity/gen/Species-odb.o \
./src/comppi/entity/gen/SystemType-odb.o 

CXX_DEPS += \
./src/comppi/entity/gen/Interaction-odb.d \
./src/comppi/entity/gen/Localization-odb.d \
./src/comppi/entity/gen/NameToProtein-odb.d \
./src/comppi/entity/gen/Protein-odb.d \
./src/comppi/entity/gen/ProteinName-odb.d \
./src/comppi/entity/gen/ProteinNameMap-odb.d \
./src/comppi/entity/gen/Species-odb.d \
./src/comppi/entity/gen/SystemType-odb.d 


# Each subdirectory must supply rules for building sources it contributes
src/comppi/entity/gen/%.o: ../src/comppi/entity/gen/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDATABASE_MYSQL -DBOOST_LOG_DYN_LINK -I"/home/erenon/arbeit/c++/c++omppi/src" -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -Wno-unknown-pragmas -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MMD -MT "$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


