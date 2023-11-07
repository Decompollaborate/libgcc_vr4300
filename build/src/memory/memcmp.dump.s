
build/src/memory/memcmp.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <memcmp>:
   0:	00001025 	move	v0,zero
   4:	14460003 	bne	v0,a2,14 <memcmp+0x14>
   8:	00821821 	addu	v1,a0,v0
   c:	03e00008 	jr	ra
  10:	00001025 	move	v0,zero
  14:	00a23821 	addu	a3,a1,v0
  18:	90630000 	lbu	v1,0(v1)
  1c:	90e70000 	lbu	a3,0(a3)
  20:	0067402b 	sltu	t0,v1,a3
  24:	15000005 	bnez	t0,3c <memcmp+0x3c>
  28:	00e3182b 	sltu	v1,a3,v1
  2c:	14600005 	bnez	v1,44 <memcmp+0x44>
  30:	00000000 	nop
  34:	1000fff3 	b	4 <memcmp+0x4>
  38:	24420001 	addiu	v0,v0,1
  3c:	03e00008 	jr	ra
  40:	2402ffff 	li	v0,-1
  44:	03e00008 	jr	ra
  48:	24020001 	li	v0,1
  4c:	00000000 	nop
