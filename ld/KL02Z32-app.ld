/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * KL25Z128 memory setup.
 */

ENTRY(_start)

MEMORY
{
  osflash  :  org = 0x00000000,                  len = 0x5900
  flash    :  org = LENGTH(osflash),             len = 32k - LENGTH(osflash)
  osram    :  org = 0x1FFFFC00,                  len = 1024
  ram      :  org = 0x1FFFFC00 + LENGTH(osram),  len = 4k - LENGTH(osram)
}

/* Make the RAM size available to the OS */
__ram_start__           = ORIGIN(ram);
__ram_size__            = LENGTH(ram);
__ram_end__             = __ram_start__ + __ram_size__;

SECTIONS
{
  . = ORIGIN(flash);

  .text : ALIGN(4) SUBALIGN(4)
  {
    KEEP(*(.progheader))

    _text = .;

    PROVIDE(__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    PROVIDE(__init_array_end = .);

    *(.text .stub .text.* .gnu.linkonce.t.*)
    KEEP(*(SORT(.chibi_list*)));
    *(.rodata)
    *(.rodata.*)

    *(.ARM.extab* .gnu.linkonce.armextab.*)

    PROVIDE(__exidx_start = .);
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    PROVIDE(__exidx_end = .);

    *(.eh_frame_hdr)

    *(.eh_frame)
    . = ALIGN(16);
  } > flash

  .textalign : ONLY_IF_RO
  {
    . = ALIGN(8);
  } > flash

  _etext = .;
  _textdata = _etext;

  .data :
  {
    . = ALIGN(16);
    PROVIDE(_data = .);
    *(.data .data.* .gnu.linkonce.d.*)
    . = ALIGN(4);
    *(.ramtext)

    PROVIDE(_edata = .);
    . = ALIGN(16);
  } > ram AT > flash

  .bytecode :
  {
    . = ALIGN(16);
    PROVIDE(_bytecode_start = .);
    *(.bytecode .bytecode.*)
    . = ALIGN(4);
    PROVIDE(_bytecode_end = .);
    . = ALIGN(16);
  } > flash

  .flasheeprom (NOLOAD) : ALIGN(1024)
  {
    *(.flasheeprom)
  } > flash

  .bss :
  {
    . = ALIGN(4);
    PROVIDE(_bss_start = .);
    *(.bss .bss.* .gnu.linkonce.b.*)
    . = ALIGN(4);
    *(COMMON)
    . = ALIGN(4);
    PROVIDE(_bss_end = .);
  } > ram

  PROVIDE(end = .);
  _end            = .;

  /DISCARD/ : {
    *(.note.GNU-stack)
    *(.gnu_debuglink)
    *(.note.gnu.build-id)
    *(.note.gnu.build-id.*);
    *(.glue_7t)
    *(.glue_7)
    *(.gcc*)
    *(.interp)
    *(.fini_array)
    *(.fini_array.*)
  }

  /* ld.bfd will segfault without these */
  .rel.plt :
  {
    . = ALIGN(4);
  }
  .got.plt :
  {
    . = ALIGN(4);
  }
}

/* RAM region to be used for Main stack. This stack accommodates the processing
      of all exceptions and interrupts*/
REGION_ALIAS("MAIN_STACK_RAM", ram);

/* RAM region to be used for the process stack. This is the stack used by
      the main() function.*/
REGION_ALIAS("PROCESS_STACK_RAM", ram);

/* RAM region to be used for data segment.*/
REGION_ALIAS("DATA_RAM", ram);

/* RAM region to be used for BSS segment.*/
REGION_ALIAS("BSS_RAM", ram);

__heap_base__   = _end;
__heap_end__    = __ram_end__;
