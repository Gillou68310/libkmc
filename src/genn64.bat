set gccsw=-mips3 -mgp32 -mfp32 -G0
copy mips_as.fpu mips_as.h
@echo on
gcc -O -c crtkmc.c
gcc -O -c abs.c
gcc -O -c asin.c
gcc -O -c atan.c
gcc -O -c atbl.c
gcc -O -c atoi.c
gcc -O -c bsearch.c
gcc -O -c calloc.c
gcc -O -c cgets.c
gcc -O -c cputs.c
gcc -O -c ctype.c
gcc -O -c div.c
gcc -O -c errno.c
gcc -O -c etbl.c
gcc -O -c exp.c
gcc -O -c fabs.c
gcc -O -c fmod.c
gcc -O -c free.c
gcc -O -c frexp.c
gcc -O -c getch.c
gcc -O -c getchar.c
gcc -O -c getche.c
gcc -O -c gets.c
gcc -O -c getw.c
gcc -O -c itoa.c
gcc -O -c kbhit.c
gcc -O -c labs.c
gcc -O -c ldexp.c
gcc -O -c ldiv.c
gcc -O -c log.c
gcc -O -c ltoa.c
gcc -O -c malloc.c
gcc -O -c matherr.c
gcc -O -c memccpy.c
gcc -O -c memchr.c
gcc -O -c memcmp.c
gcc -O -c memcpy.c
gcc -O -c memicmp.c
gcc -O -c memmove.c
gcc -O -c memset.c
gcc -O -c modf.c
gcc -O -c pow.c
gcc -O -c printf.c
gcc -O -c putch.c
gcc -O -c putchar.c
gcc -O -c puts.c
gcc -O -c putw.c
gcc -O -c qsort.c
gcc -O -c rand.c
gcc -O -c realloc.c
gcc -O -c scanf.c
gcc -O -c sin.c
gcc -O -c sinh.c
gcc -O -c sqrt.c
gcc -O -c stpcpy.c
gcc -O -c strcat.c
gcc -O -c strchr.c
gcc -O -c strcmp.c
gcc -O -c strcpy.c
gcc -O -c strcspn.c
gcc -O -c strdup.c
gcc -O -c strerr.c
gcc -O -c stricmp.c
gcc -O -c strlen.c
gcc -O -c strlwr.c
gcc -O -c strncat.c
gcc -O -c strncmp.c
gcc -O -c strncpy.c
gcc -O -c strnicmp.c
gcc -O -c strnset.c
gcc -O -c strpbrk.c
gcc -O -c strrchr.c
gcc -O -c strrev.c
gcc -O -c strset.c
gcc -O -c strspn.c
gcc -O -c strstr.c
gcc -O -c strtok.c
gcc -O -c strtol.c
gcc -O -c strtoul.c
gcc -O -c strupr.c
gcc -O -c tolower.c
gcc -O -c toupper.c
gcc -O -c ultoa.c
gcc -O -c ungetch.c
gcc -O -c syscall.c
gcc -O -c abort.c
gcc -O -c _matherr.c
gcc -O -c _m_init.c
gcc -O -c _toa.c
as -mips3 -o setjmp.o setjmp.s
as -mips3 -o mcmpl.o mcmpl.s
as -mips3 -o mmuldi3.o mmuldi3.s
as -mips3 -o mcvtld.o mcvtld.s
as -mips3 -o mcvtls.o mcvtls.s
as -mips3 -o madddf3.o madddf3.s
as -mips3 -o maddsf3.o maddsf3.s
as -mips3 -o mmuldf3.o mmuldf3.s
as -mips3 -o mmulsf3.o mmulsf3.s
as -mips3 -o ms2d.o ms2d.s
as -mips3 -o md2s.o md2s.s
as -mips3 -o mneg.o mneg.s
as -mips3 -o mcmpd.o mcmpd.s
as -mips3 -o mcmps.o mcmps.s
as -mips3 -o mcvts.o mcvts.s
as -mips3 -o mcvtd.o mcvtd.s
echo >libkmc.a
del libkmc.a >nul
ar rc libkmc.a @arfile
ranlib libkmc.a
@echo off
echo ******************************************************************
echo ***** when using the newly created library libkmc.a copy     *****
echo ***** libkmc.a to the directory of /lib.                     *****
echo ******************************************************************
:done
