################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/mc/changed_mc/m_commands.c \
../src/mc/changed_mc/m_interpreter.c 

OBJS += \
./src/mc/changed_mc/m_commands.o \
./src/mc/changed_mc/m_interpreter.o 

C_DEPS += \
./src/mc/changed_mc/m_commands.d \
./src/mc/changed_mc/m_interpreter.d 


# Each subdirectory must supply rules for building sources it contributes
src/mc/changed_mc/%.o: ../src/mc/changed_mc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\Synergy\e2studio_v6.2.0_ssp_v1.4.0\eclipse\/../\Utilities\\/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy_cfg\ssp_cfg\bsp" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\inc\driver\api\api_changed" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\src\driver\changed_src_files" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\src\mc" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy_cfg\ssp_cfg\driver" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\inc" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\inc\bsp" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\inc\driver\api" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\inc\driver\instances" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\src" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\src\synergy_gen" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy_cfg\ssp_cfg\framework\el" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\inc\framework\el" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\src\framework\el\tx" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy_cfg\ssp_cfg\framework" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\inc\framework\api" -I"C:\Users\britton.chesley\e2_studio\workspace\BLDC_Motor_Control\synergy\ssp\inc\framework\instances" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


