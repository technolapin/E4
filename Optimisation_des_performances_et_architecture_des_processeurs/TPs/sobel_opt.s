	.data
TEST:	.word 0
img:	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,255,255,255,0,0
	.word 0,0,0,255,255,255,0,0
	.word 0,0,0,255,255,255,0,0
	.word 0,0,0,255,255,255,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0

sobX:	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0

sobY:	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0


sob:	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0
	.word 0,0,0,0,0,0,0,0

wLen:	.word 4
width:	.word 32
length:	.word 256

voisine_1:	.word -36
voisine_2:	.word -32
voisine_3:	.word -28
voisine_4:	.word -4
voisine_5:	.word 4
voisine_6:	.word 28
voisine_7:	.word 32
voisine_8:	.word 36

	
	.text
main:
	add r1, r0, img
	add r2, r0, sobX
	add r3, r0, sobY
	add r4, r0, sob
	lw r5, wLen(r0)
	lw r6, width(r0)

	lw r7, length(r0) 	; indice du curseur dans l'image d'origine
	lw r21, voisine_1(r0) 	; décalage des voisines
	lw r22, voisine_2(r0)
	lw r23, voisine_3(r0)
	lw r24, voisine_4(r0)
	sub r7, r7, r5 		; on ne traîte pas les bords
	lw r25, voisine_5(r0)
	lw r26, voisine_6(r0)
	lw r27, voisine_7(r0)
	lw r28, voisine_8(r0)


	

	sub r7, r7, r6

	addi r30, r0, #255 	; pour avoir un 255 quelque part

sobel:	
	
	add r8, r1, r7 		; l'addresse mémoire de la cellule
	add r9, r1, r7 		; l'addresse mémoire de la cellule

	add r13, r8, r21
	add r14, r8, r22
	add r15, r9, r23
	add r16, r8, r24
	add r17, r9, r25
	add r18, r8, r26
	add r19, r8, r27
	add r20, r9, r28

	lw r13, (r13)
	lw r14, (r14)
	lw r15, (r15)

	lw r16, (r16)
	lw r17, (r17)

	lw r18, (r18)
	lw r19, (r19)
	lw r20, (r20)
	
	sub r10, r0, r13

	add r10, r10, r15

	sub r10, r10, r16
	sub r10, r10, r16
	
	add r10, r10, r17
	add r10, r10, r17

	sub r10, r10, r18
	add r10, r10, r20	
	
	
	srai r11, r10, #8
	xor r12, r11, r10

        ;; teeest
	srli r10, r11, #7
	add r12, r12, r10

	sub r11, r0, r13

	sub r11, r11, r14
	sub r11, r11, r14

	sub r11, r11, r15

	add r11, r11, r18
	
	add r11, r11, r19
	add r11, r11, r19

	add r11, r11, r20
	
	srai r10, r11, #8
	xor r9, r11, r10


	;; teeest
	srli r10, r11, #7
	add r12, r12, r10

	
	add r12, r12, r9


	srli r12, r12, #1
	

	sgeu r13, r12, r30

	sub r14, r0, r13

	or r15, r14, r12
	and r15, r15, r30
	sw sobX(r7), r15

	

	sub r7, r7, r5 		; on se décale d'une cellule

	sub r11, r7, r6

	bnez r11, sobel

finsobel:
	




	


	
	add r7, r0, r6
	sub r9, r2, r5
	sub r10, r2, r6
virebord:
	sub r8, r2, r7
	sub r7, r7, r5
	sw sobX(r7), r0
	sw sobX(r8), r0
	sw sobX(r9), r0
	sw sobX(r10), r0
	sub r9, r9, r6
	sub r10, r10, r6
	bnez r7, virebord


	
	

	
	nop
	trap #0
