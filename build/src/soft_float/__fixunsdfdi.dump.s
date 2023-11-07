
build/src/soft_float/__fixunsdfdi.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <__fixunsdfdi>:
   0:	3c010000 	lui	at,0x0
			0: R_MIPS_HI16	.rodata
   4:	d4200000 	ldc1	fv0,0(at)
			4: R_MIPS_LO16	.rodata
   8:	4620603e 	c.le.d	fa0,fv0
   c:	45010008 	bc1t	30 <__fixunsdfdi+0x30>
  10:	00001825 	move	v1,zero
  14:	27bdfff8 	addiu	sp,sp,-8
  18:	46006025 	cvt.l.s	fv0,fa0
  1c:	f7a00000 	sdc1	fv0,0(sp)
  20:	8fa30004 	lw	v1,4(sp)
  24:	8fa20000 	lw	v0,0(sp)
  28:	03e00008 	jr	ra
  2c:	27bd0008 	addiu	sp,sp,8
  30:	03e00008 	jr	ra
  34:	00001025 	move	v0,zero
  38:	00000000 	nop
  3c:	00000000 	nop
