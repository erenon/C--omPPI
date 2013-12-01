################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include src/comppi/service/systemtype/subdir.mk
-include src/comppi/service/species/subdir.mk
-include src/comppi/service/protein/subdir.mk
-include src/comppi/service/log/subdir.mk
-include src/comppi/service/localization/subdir.mk
-include src/comppi/service/gexf/subdir.mk
-include src/comppi/service/driver/map/subdir.mk
-include src/comppi/service/driver/localization/subdir.mk
-include src/comppi/service/driver/interaction/subdir.mk
-include src/comppi/service/database/subdir.mk
-include src/comppi/service/config/subdir.mk
-include src/comppi/entity/gen/subdir.mk
-include src/comppi/controller/subdir.mk
-include src/comppi/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pre-build main-build

# Main-build Target
main-build: comppi

# Tool invocations
comppi: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "comppi" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) comppi
	-@echo ' '

pre-build:
	-@echo 'Generate ODB related code'
	-../bin/generate-entities.sh ../src/comppi/entity/*.h
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

-include ../makefile.targets
