/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    crtkmc.c (startup)
*/

asm("    .text
    .align    2
    .globl    _start
    .ent    _start
_start:
    la    $29,_stack_init    /* Stack Initialization */
    la    $28,_gp
    .end    _start
");

static void start1()
{
    extern char _erdata[],_data[],_xfer[];
    extern char _edata[],_fbss[],_end[],_heep[],_heep_size[];

/* Transfer the intialization of the ROM to the RAM area(data)
   Note:  If there is no need of transfer make the following memcpy function a comment
*/
    if((unsigned int)&_xfer & 1){
    memcpy(&_data,&_erdata,(unsigned)&_edata-(unsigned)&_data);
    }

/* Clear the RAM area of the bss */
    memset((unsigned)&_fbss,0,(unsigned)&_end-(unsigned)&_fbss);

/* Range specification of the heap area that is used for malloc function
   Note:  It is specified with 0x20000 bytes from the end of the bss area on default.
          Modify this part according to the user's system.
*/
    _m_init(&_heep,&_heep_size);    /* _minit(heep start,size) */

/* To the main routine */
    main();

    exit();
}

__main()
{
}

exit()
{
    for(;;){
    }
}
