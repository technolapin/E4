	.data
A:	.word 10
B:	.word 8
C:	.word 0

	.text
	.global main
main:
	lw r4,A(r0)
	lw r5,B(r0)
	add r3,r4,r5
	sw r3,C(r0)
	trap 0x0
	nop
