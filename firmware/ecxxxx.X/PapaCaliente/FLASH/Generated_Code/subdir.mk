################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/AS1.c" \
"../Generated_Code/AS2.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/FC321.c" \
"../Generated_Code/IO_Map.c" \
"../Generated_Code/Inhr1.c" \
"../Generated_Code/Inhr2.c" \
"../Generated_Code/Inhr3.c" \
"../Generated_Code/Inhr4.c" \
"../Generated_Code/MBit1.c" \
"../Generated_Code/PE_Timer.c" \
"../Generated_Code/PWM1.c" \
"../Generated_Code/TI1.c" \
"../Generated_Code/TI2.c" \
"../Generated_Code/TI3.c" \
"../Generated_Code/TI4.c" \
"../Generated_Code/TI5.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/AS1.c \
../Generated_Code/AS2.c \
../Generated_Code/Cpu.c \
../Generated_Code/FC321.c \
../Generated_Code/IO_Map.c \
../Generated_Code/Inhr1.c \
../Generated_Code/Inhr2.c \
../Generated_Code/Inhr3.c \
../Generated_Code/Inhr4.c \
../Generated_Code/MBit1.c \
../Generated_Code/PE_Timer.c \
../Generated_Code/PWM1.c \
../Generated_Code/TI1.c \
../Generated_Code/TI2.c \
../Generated_Code/TI3.c \
../Generated_Code/TI4.c \
../Generated_Code/TI5.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/AS1_c.obj \
./Generated_Code/AS2_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/FC321_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/Inhr1_c.obj \
./Generated_Code/Inhr2_c.obj \
./Generated_Code/Inhr3_c.obj \
./Generated_Code/Inhr4_c.obj \
./Generated_Code/MBit1_c.obj \
./Generated_Code/PE_Timer_c.obj \
./Generated_Code/PWM1_c.obj \
./Generated_Code/TI1_c.obj \
./Generated_Code/TI2_c.obj \
./Generated_Code/TI3_c.obj \
./Generated_Code/TI4_c.obj \
./Generated_Code/TI5_c.obj \
./Generated_Code/Vectors_c.obj \

OBJS_QUOTED += \
"./Generated_Code/AS1_c.obj" \
"./Generated_Code/AS2_c.obj" \
"./Generated_Code/Cpu_c.obj" \
"./Generated_Code/FC321_c.obj" \
"./Generated_Code/IO_Map_c.obj" \
"./Generated_Code/Inhr1_c.obj" \
"./Generated_Code/Inhr2_c.obj" \
"./Generated_Code/Inhr3_c.obj" \
"./Generated_Code/Inhr4_c.obj" \
"./Generated_Code/MBit1_c.obj" \
"./Generated_Code/PE_Timer_c.obj" \
"./Generated_Code/PWM1_c.obj" \
"./Generated_Code/TI1_c.obj" \
"./Generated_Code/TI2_c.obj" \
"./Generated_Code/TI3_c.obj" \
"./Generated_Code/TI4_c.obj" \
"./Generated_Code/TI5_c.obj" \
"./Generated_Code/Vectors_c.obj" \

C_DEPS += \
./Generated_Code/AS1_c.d \
./Generated_Code/AS2_c.d \
./Generated_Code/Cpu_c.d \
./Generated_Code/FC321_c.d \
./Generated_Code/IO_Map_c.d \
./Generated_Code/Inhr1_c.d \
./Generated_Code/Inhr2_c.d \
./Generated_Code/Inhr3_c.d \
./Generated_Code/Inhr4_c.d \
./Generated_Code/MBit1_c.d \
./Generated_Code/PE_Timer_c.d \
./Generated_Code/PWM1_c.d \
./Generated_Code/TI1_c.d \
./Generated_Code/TI2_c.d \
./Generated_Code/TI3_c.d \
./Generated_Code/TI4_c.d \
./Generated_Code/TI5_c.d \
./Generated_Code/Vectors_c.d \

C_DEPS_QUOTED += \
"./Generated_Code/AS1_c.d" \
"./Generated_Code/AS2_c.d" \
"./Generated_Code/Cpu_c.d" \
"./Generated_Code/FC321_c.d" \
"./Generated_Code/IO_Map_c.d" \
"./Generated_Code/Inhr1_c.d" \
"./Generated_Code/Inhr2_c.d" \
"./Generated_Code/Inhr3_c.d" \
"./Generated_Code/Inhr4_c.d" \
"./Generated_Code/MBit1_c.d" \
"./Generated_Code/PE_Timer_c.d" \
"./Generated_Code/PWM1_c.d" \
"./Generated_Code/TI1_c.d" \
"./Generated_Code/TI2_c.d" \
"./Generated_Code/TI3_c.d" \
"./Generated_Code/TI4_c.d" \
"./Generated_Code/TI5_c.d" \
"./Generated_Code/Vectors_c.d" \

OBJS_OS_FORMAT += \
./Generated_Code/AS1_c.obj \
./Generated_Code/AS2_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/FC321_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/Inhr1_c.obj \
./Generated_Code/Inhr2_c.obj \
./Generated_Code/Inhr3_c.obj \
./Generated_Code/Inhr4_c.obj \
./Generated_Code/MBit1_c.obj \
./Generated_Code/PE_Timer_c.obj \
./Generated_Code/PWM1_c.obj \
./Generated_Code/TI1_c.obj \
./Generated_Code/TI2_c.obj \
./Generated_Code/TI3_c.obj \
./Generated_Code/TI4_c.obj \
./Generated_Code/TI5_c.obj \
./Generated_Code/Vectors_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/AS1_c.obj: ../Generated_Code/AS1.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/AS1.args" -ObjN="Generated_Code/AS1_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/%.d: ../Generated_Code/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Generated_Code/AS2_c.obj: ../Generated_Code/AS2.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/AS2.args" -ObjN="Generated_Code/AS2_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Cpu_c.obj: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Cpu.args" -ObjN="Generated_Code/Cpu_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/FC321_c.obj: ../Generated_Code/FC321.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/FC321.args" -ObjN="Generated_Code/FC321_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_Map_c.obj: ../Generated_Code/IO_Map.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/IO_Map.args" -ObjN="Generated_Code/IO_Map_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Inhr1_c.obj: ../Generated_Code/Inhr1.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Inhr1.args" -ObjN="Generated_Code/Inhr1_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Inhr2_c.obj: ../Generated_Code/Inhr2.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Inhr2.args" -ObjN="Generated_Code/Inhr2_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Inhr3_c.obj: ../Generated_Code/Inhr3.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Inhr3.args" -ObjN="Generated_Code/Inhr3_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Inhr4_c.obj: ../Generated_Code/Inhr4.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Inhr4.args" -ObjN="Generated_Code/Inhr4_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/MBit1_c.obj: ../Generated_Code/MBit1.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/MBit1.args" -ObjN="Generated_Code/MBit1_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_Timer_c.obj: ../Generated_Code/PE_Timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/PE_Timer.args" -ObjN="Generated_Code/PE_Timer_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PWM1_c.obj: ../Generated_Code/PWM1.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/PWM1.args" -ObjN="Generated_Code/PWM1_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TI1_c.obj: ../Generated_Code/TI1.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/TI1.args" -ObjN="Generated_Code/TI1_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TI2_c.obj: ../Generated_Code/TI2.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/TI2.args" -ObjN="Generated_Code/TI2_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TI3_c.obj: ../Generated_Code/TI3.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/TI3.args" -ObjN="Generated_Code/TI3_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TI4_c.obj: ../Generated_Code/TI4.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/TI4.args" -ObjN="Generated_Code/TI4_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TI5_c.obj: ../Generated_Code/TI5.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/TI5.args" -ObjN="Generated_Code/TI5_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors_c.obj: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Vectors.args" -ObjN="Generated_Code/Vectors_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


