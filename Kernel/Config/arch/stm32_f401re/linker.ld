/*******************************************************************************
 * LUTk linker file for STM32 F401RE target
 *
 * Created: 23/05/2020
 *
 * Author: Alexy Torres Aurora Dugo
 *
 ******************************************************************************/

/* Entry point */
ENTRY(__rst_handler)

/* Memory map */
MEMORY
{
    SDRAM   (rx)    :   ORIGIN = 0x20000000,    LENGTH = 96K
    FLASH   (rx)    :   ORIGIN = 0x08000000,    LENGTH = 512K
}

/* Memory layout */
SECTIONS
{
    /* Contains the interrupt vector, must be located at CPU reset address */
    .startup :
    {
        . = ALIGN(4);
        KEEP(*(.int_vect))
        KEEP(*(.boot_code))
        . = ALIGN(4);
    } > FLASH

    /* Contains the kernel and user's code */
    .text :
    {
        . = ALIGN(4);
        _start_text = .;

        *(.text)
        *(.text*)        
        . = ALIGN(4);

        _end_text = .;
    } > FLASH

    /* Contains the kernel and user's read only data */
    .rodata :
    {
        . = ALIGN(4);
        _start_rodata = .;

        *(.eh_frame)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);

        _end_rodata = .;
    } > FLASH

    _start_init_data = LOADADDR(.data);

    /* Contains the kernel and user's data */
    .data : 
    {
        . = ALIGN(4);
        _start_data = .; 

        *(.data)         
        *(.data*)          
        . = ALIGN(4);

        _end_data = .;   
        
    } >SDRAM AT> FLASH

    /* Contains the kernel and user's BSS */
    .bss : 
    {
        . = ALIGN(4);
        _start_bss = .; 

        *(COMMON)
        *(.bss)         
        . = ALIGN(4);

        _end_bss = .;   
        
    } > SDRAM    
}