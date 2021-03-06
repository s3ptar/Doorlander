################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Battery.c" \
"../Sources/Events.c" \
"../Sources/FT800_HAL.c" \
"../Sources/copro_commands.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/Battery.c \
../Sources/Events.c \
../Sources/FT800_HAL.c \
../Sources/copro_commands.c \
../Sources/main.c \

OBJS += \
./Sources/Battery_c.obj \
./Sources/Events_c.obj \
./Sources/FT800_HAL_c.obj \
./Sources/copro_commands_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/Battery_c.obj" \
"./Sources/Events_c.obj" \
"./Sources/FT800_HAL_c.obj" \
"./Sources/copro_commands_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/Battery_c.d \
./Sources/Events_c.d \
./Sources/FT800_HAL_c.d \
./Sources/copro_commands_c.d \
./Sources/main_c.d \

OBJS_OS_FORMAT += \
./Sources/Battery_c.obj \
./Sources/Events_c.obj \
./Sources/FT800_HAL_c.obj \
./Sources/copro_commands_c.obj \
./Sources/main_c.obj \

C_DEPS_QUOTED += \
"./Sources/Battery_c.d" \
"./Sources/Events_c.d" \
"./Sources/FT800_HAL_c.d" \
"./Sources/copro_commands_c.d" \
"./Sources/main_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Battery_c.obj: ../Sources/Battery.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/Battery.args" -o "Sources/Battery_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/Events.args" -o "Sources/Events_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/FT800_HAL_c.obj: ../Sources/FT800_HAL.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/FT800_HAL.args" -o "Sources/FT800_HAL_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/copro_commands_c.obj: ../Sources/copro_commands.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/copro_commands.args" -o "Sources/copro_commands_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


