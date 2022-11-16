/*
 * RELOBJ.CMD For Relocatonal Object
 *
 *			Nintendo64
 */

OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips",
	      "elf32-littlemips")
SECTIONS
{
    .text 0 : {
	*(.text)
    }
    .rodata 0 : { 
	*(.rodata)
    }
    .data 0 : {
	*(.data)
    }
    .sdata 0 : {
	*(.sdata) 
    }
    .sbss 0 : {
	*(.sbss)
	*(.scommon)
    }
    .bss 0 : {
	*(.bss)
	*(COMMON)
    }

  /* DWARF debug sections */

  .debug          0 : { *(.debug) }
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  .line           0 : { *(.line) }
  .gptab.sdata 0 : { *(.gptab.data) *(.gptab.sdata) }
  .gptab.sbss 0 : { *(.gptab.bss) *(.gptab.sbss) }
}
