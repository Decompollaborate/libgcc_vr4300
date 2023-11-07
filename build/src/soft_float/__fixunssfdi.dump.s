
build/src/soft_float/__fixunssfdi.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <__fixunssfdi>:
   0:	44800000 	mtc1	zero,fv0
   4:	4600603e 	c.le.s	fa0,fv0
   8:	45010008 	bc1t	2c <__fixunssfdi+0x2c>
   c:	00001825 	move	v1,zero
  10:	27bdfff8 	addiu	sp,sp,-8
  14:	46006025 	cvt.l.s	fv0,fa0
  18:	f7a00000 	sdc1	fv0,0(sp)
  1c:	8fa30004 	lw	v1,4(sp)
  20:	8fa20000 	lw	v0,0(sp)
  24:	03e00008 	jr	ra
  28:	27bd0008 	addiu	sp,sp,8
  2c:	03e00008 	jr	ra
  30:	00001025 	move	v0,zero
  34:	00000000 	nop
  38:	00000000 	nop
  3c:	00000000 	nop
