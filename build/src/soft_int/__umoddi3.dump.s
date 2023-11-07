
build/src/soft_int/__umoddi3.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <__umoddi3>:
   0:	afa40000 	sw	a0,0(sp)
   4:	afa50004 	sw	a1,4(sp)
   8:	afa60008 	sw	a2,8(sp)
   c:	afa7000c 	sw	a3,12(sp)
  10:	dfaf0008 	ld	t7,8(sp)
  14:	dfae0000 	ld	t6,0(sp)
  18:	15e00002 	bnez	t7,24 <__umoddi3+0x24>
  1c:	01cf001f 	ddivu	zero,t6,t7
  20:	0007000d 	break	0x7
  24:	00001010 	mfhi	v0
  28:	0002183c 	dsll32	v1,v0,0x0
  2c:	0003183f 	dsra32	v1,v1,0x0
  30:	03e00008 	jr	ra
  34:	0002103f 	dsra32	v0,v0,0x0
  38:	00000000 	nop
  3c:	00000000 	nop
