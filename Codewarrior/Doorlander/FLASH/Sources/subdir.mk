################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/Idle_Task.c" \
"../Sources/frtos_tasks.c" \
"../Sources/main.c" \
"../Sources/tools.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/Idle_Task.c \
../Sources/frtos_tasks.c \
../Sources/main.c \
../Sources/tools.c \

OBJS += \
./Sources/Events_c.obj \
./Sources/Idle_Task_c.obj \
./Sources/frtos_tasks_c.obj \
./Sources/main_c.obj \
./Sources/tools_c.obj \

OBJS_QUOTED += \
"./Sources/Events_c.obj" \
"./Sources/Idle_Task_c.obj" \
"./Sources/frtos_tasks_c.obj" \
"./Sources/main_c.obj" \
"./Sources/tools_c.obj" \

C_DEPS += \
./Sources/Events_c.d \
./Sources/Idle_Task_c.d \
./Sources/frtos_tasks_c.d \
./Sources/main_c.d \
./Sources/tools_c.d \

OBJS_OS_FORMAT += \
./Sources/Events_c.obj \
./Sources/Idle_Task_c.obj \
./Sources/frtos_tasks_c.obj \
./Sources/main_c.obj \
./Sources/tools_c.obj \

C_DEPS_QUOTED += \
"./Sources/Events_c.d" \
"./Sources/Idle_Task_c.d" \
"./Sources/frtos_tasks_c.d" \
"./Sources/main_c.d" \
"./Sources/tools_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/Events.args" -o "Sources/Events_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/Idle_Task_c.obj: ../Sources/Idle_Task.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/Idle_Task.args" -o "Sources/Idle_Task_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/frtos_tasks_c.obj: ../Sources/frtos_tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/frtos_tasks.args" -o "Sources/frtos_tasks_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/tools_c.obj: ../Sources/tools.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/tools.args" -o "Sources/tools_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


