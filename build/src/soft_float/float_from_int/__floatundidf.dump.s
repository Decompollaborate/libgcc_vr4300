
build/src/soft_float/float_from_int/__floatundidf.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <__floatundidf>:
   0:	27bdfff8 	addiu	sp,sp,-8
   4:	afa50004 	sw	a1,4(sp)
   8:	afa40000 	sw	a0,0(sp)
   c:	d7a00000 	ldc1	fv0,0(sp)
  10:	04810004 	bgez	a0,24 <__floatundidf+0x24>
  14:	46a00021 	cvt.d.l	fv0,fv0
  18:	3c010000 	lui	at,0x0
			18: R_MIPS_HI16	.rodata
  1c:	d4220000 	ldc1	fv1,0(at)
			1c: R_MIPS_LO16	.rodata
  20:	46220000 	add.d	fv0,fv0,fv1
  24:	03e00008 	jr	ra
  28:	27bd0008 	addiu	sp,sp,8
  2c:	00000000 	nop
