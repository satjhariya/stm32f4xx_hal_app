ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Initial stack pointer */
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    /* Interrupt vector table */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    /* Program code and constants */
    .text :
    {
        . = ALIGN(4);

        *(.text*)
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)

        /* C++ constructor tables */
        . = ALIGN(4);

        /* C/C++ static constructors */
        __preinit_array_start = .;
        KEEP(*(.preinit_array*))
        __preinit_array_end = .;

        . = ALIGN(4);

        __init_array_start = .;
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        __init_array_end = .;

        . = ALIGN(4);

        __fini_array_start = .;
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array*))
        __fini_array_end = .;

        . = ALIGN(4);
    } > FLASH

    /* ARM exception unwinding tables required by libgcc/newlib */
    .ARM.extab :
    {
        . = ALIGN(4);
        *(.ARM.extab*)
        *(.gnu.linkonce.armextab.*)
        . = ALIGN(4);
    } > FLASH

    .ARM.exidx :
    {
        . = ALIGN(4);
        __exidx_start = .;
        *(.ARM.exidx*)
        *(.gnu.linkonce.armexidx.*)
        __exidx_end = .;
        . = ALIGN(4);
    } > FLASH

    /* End of code region / start of initialized data image in FLASH */
    _etext = .;
    _sidata = _etext;

    /* Initialized data copied from FLASH to RAM during startup */
    .data : AT(_sidata)
    {
        . = ALIGN(4);
        _sdata = .;

        *(.data*)
        *(.ramfunc*)

        . = ALIGN(4);
        _edata = .;
    } > RAM

    /* Zero-initialized data */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;

        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;
    } > RAM

    /* Optional heap/stack markers for _sbrk and debugging */
    . = ALIGN(8);
    _end = .;
    end = .;
    __end__ = .;

    /* Discard unused standard library metadata */
    /DISCARD/ :
    {
        *(.note*)
        *(.comment*)
        *(.eh_frame*)
    }
}
