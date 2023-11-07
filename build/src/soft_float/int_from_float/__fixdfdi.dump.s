
build/src/soft_float/int_from_float/__fixdfdi.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <__fixdfdi>:
   0:	27bdfff8 	addiu	sp,sp,-8
   4:	46206025 	cvt.l.d	fv0,fa0
   8:	f7a00000 	sdc1	fv0,0(sp)
   c:	8fa30004 	lw	v1,4(sp)
  10:	8fa20000 	lw	v0,0(sp)
  14:	03e00008 	jr	ra
  18:	27bd0008 	addiu	sp,sp,8
  1c:	00000000 	nop
