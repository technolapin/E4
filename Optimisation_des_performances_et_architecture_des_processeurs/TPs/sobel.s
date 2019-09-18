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

	lw r21, voisine_1(r0) 	; décalage des voisines
	lw r22, voisine_2(r0)
	lw r23, voisine_3(r0)
	lw r24, voisine_4(r0)
	lw r25, voisine_5(r0)
	lw r26, voisine_6(r0)
	lw r27, voisine_7(r0)
	lw r28, voisine_8(r0)


	
	lw r7, length(r0) 	; indice du curseur dans l'image d'origine

	sub r7, r7, r5 		; on ne traîte pas les bords
	sub r7, r7, r6


sobel_x:	
	
	add r8, r1, r7 		; l'addresse mémoire de la cellule
	add r9, r1, r7 		; l'addresse mémoire de la cellule

	add r13, r8, r21
	add r14, r9, r23
	add r15, r8, r24
	add r16, r9, r25
	add r17, r8, r26
	add r18, r9, r28

	lw r13, (r13)
	lw r14, (r14)
	lw r15, (r15)
	lw r16, (r16)
	lw r17, (r17)
	lw r18, (r18)
	
	sub r10, r0, r13

	add r10, r0, r14

	sub r10, r10, r15
	sub r10, r10, r15
	
	add r10, r10, r16
	add r10, r10, r16

	sub r10, r10, r17
	add r10, r10, r18	

	
	sge r13, r10, r0
	bnez r13, pasnulX
	sub r10, r0, r10
	
pasnulX:	
	sw sobX(r7), r10

	;;  test

	;; lw r10, (r8)
	;; sw sobX(r7), r10
	;; 	sw r28(r8), r7
	;; /test
	

	sub r7, r7, r5 		; on se décale d'une cellule

	sub r11, r7, r6

	bnez r11, sobel_x








	
	lw r7, length(r0) 	; indice

	sub r7, r7, r5 		; on ne traîte pas les bords
	sub r7, r7, r6


sobel_y:
	
	add r8, r1, r7 		; l'addresse mémoire de la cellule
	add r9, r1, r7 		; l'addresse mémoire de la cellule

	add r13, r8, r21
	add r14, r9, r22
	add r15, r8, r23
	add r16, r9, r26
	add r17, r8, r27
	add r18, r9, r28

	lw r13, (r13)
	lw r14, (r14)
	lw r15, (r15)
	lw r16, (r16)
	lw r17, (r17)
	lw r18, (r18)

	sub r10, r0, r13		; debut du calcul de la somme
	
	sub r10, r10, r14	
	sub r10, r10, r14	

	sub r10, r10, r15

	add r10, r10, r16
	
	add r10, r10, r17
	add r10, r10, r17


	add r10, r10, r18

	sge r13, r10, r0
	bnez r13, pasnulY	
	sub r10, r0, r10
pasnulY:	
	sw sobY(r7), r10

	;;  test

	;; lw r10, (r8)
	;; sw sobX(r7), r10
	;; 	sw r28(r8), r7
	;; /test
	

	sub r7, r7, r5 		; on se décale d'une cellule

	sub r11, r7, r6

	bnez r11, sobel_y










	lw r7, length(r0) 	; indice

	sub r7, r7, r5 		; on ne traîte pas les bords
	sub r7, r7, r6


	addi r14, r0, #255
sobel:
	
	lw r8, sobX(r7) 		; l'addresse mémoire de la cellule X
	lw r9, sobY(r7) 		; l'addresse mémoire de la cellule Y

	add r10, r8, r9
	srli r11, r10, #1

	sle r12, r11, r14
	bnez r12, passature

	add r11, r14, r0
	
passature:

	sw sob(r7), r11


	
	sub r7, r7, r5 		; on se décale d'une cellule

	sub r11, r7, r6

	bnez r11, sobel



	lw r2, length(r0) 	; indice du curseur dans l'image d'origine

	
	;; lw r7, width(r0) 	;indice
	add r7, r0, r6
	sub r9, r2, r5
	sub r10, r2, r6
virebord:
	sub r8, r2, r7
	sub r7, r7, r5
	sw sob(r7), r0
	sw sob(r8), r0
	sw sob(r9), r0
	sw sob(r10), r0
	sub r9, r9, r6
	sub r10, r10, r6
	bnez r7, virebord


	
	

	
	nop
	trap #0
