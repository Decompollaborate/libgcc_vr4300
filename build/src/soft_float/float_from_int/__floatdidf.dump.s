
build/src/soft_float/float_from_int/__floatdidf.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <__floatdidf>:
   0:	27bdfff8 	addiu	sp,sp,-8
   4:	afa50004 	sw	a1,4(sp)
   8:	afa40000 	sw	a0,0(sp)
   c:	d7a00000 	ldc1	fv0,0(sp)
  10:	27bd0008 	addiu	sp,sp,8
  14:	03e00008 	jr	ra
  18:	46a00021 	cvt.d.l	fv0,fv0
  1c:	00000000 	nop
