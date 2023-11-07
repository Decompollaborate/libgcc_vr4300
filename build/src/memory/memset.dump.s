
build/src/memory/memset.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <memset>:
   0:	00801025 	move	v0,a0
   4:	00863021 	addu	a2,a0,a2
   8:	00801825 	move	v1,a0
   c:	54660003 	bnel	v1,a2,1c <memset+0x1c>
  10:	a0650000 	sb	a1,0(v1)
  14:	03e00008 	jr	ra
  18:	00000000 	nop
  1c:	1000fffb 	b	c <memset+0xc>
  20:	24630001 	addiu	v1,v1,1
  24:	00000000 	nop
  28:	00000000 	nop
  2c:	00000000 	nop
