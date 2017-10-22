################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../joystick.c \
../LCD.c \
../main.c \
../TWI.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
joystick.o \
LCD.o \
main.o \
TWI.o

OBJS_AS_ARGS +=  \
joystick.o \
LCD.o \
main.o \
TWI.o

C_DEPS +=  \
joystick.d \
LCD.d \
main.d \
TWI.d

C_DEPS_AS_ARGS +=  \
joystick.d \
LCD.d \
main.d \
TWI.d

OUTPUT_FILE_PATH +=GccApplication3.elf

OUTPUT_FILE_PATH_AS_ARGS +=GccApplication3.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler









./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DNDEBUG  -I"D:\7.0\Packs\atmel\ATmega_DFP\1.2.132\include"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -mmcu=atmega328p -B "D:\7.0\Packs\atmel\ATmega_DFP\1.2.132\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-static -Wl,-Map="GccApplication3.map" -Wl,-u,vfprintf -Wl,--start-group -Wl,-lm -Wl,-lprintf_flt  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega328p -B "D:\7.0\Packs\atmel\ATmega_DFP\1.2.132\gcc\dev\atmega328p"  
	@echo Finished building target: $@
	"D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "GccApplication3.elf" "GccApplication3.hex"
	"D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "GccApplication3.elf" "GccApplication3.eep" || exit 0
	"D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "GccApplication3.elf" > "GccApplication3.lss"
	"D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "GccApplication3.elf" "GccApplication3.srec"
	"D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "GccApplication3.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "GccApplication3.elf" "GccApplication3.a" "GccApplication3.hex" "GccApplication3.lss" "GccApplication3.eep" "GccApplication3.map" "GccApplication3.srec" "GccApplication3.usersignatures"
	