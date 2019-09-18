start:      add       r1,r0,a  
            add       r2,r0,b 
            lw        r10,n(r0)  
            add       r3,r0,c    
            add       r4,r0,r10  
            lw        r11,TLig(r0)       
boucle1:    add       r5,r0,r10    
    
boucle2:    add       r6,r0,r10         
            lf        f0,t   
 	    lf        f4,0(r2)  ; Chargement des f4 et f2 avant la boucle 3
	    lf        f2,0(r1)   
            
boucle3:    multf     f6,f2,f4 ; 5 cycles
 	    lf        f4,0(r2)  ; Chargement des f4 et f2 apres le mult
	    lf        f2,0(r1)   
	    add       r1,r1,#4 
            sub       r6,r6,#1 ; 2 cycles
            add       r2,r2,#4 ;2 c cycles
            addf      f0,f0,f6  ; 2 cycles <--- génère un aléa car utilise f6 dont le calcul par mult n'est pas fini
                                ; De plus, on a qu'un additionneur
            bnez      r6,boucle3 
            nop
               
            sf        0(r3),f0  
            sub       r5,r5,#1     
            sub       r1,r1,r11    
            add       r3,r3,#4
                
            bnez      r5,boucle2    
            nop     ; <----- attend un cycle en fin de boucle 3  
            
	;; gef	      f1,f2
	;; bfpt      boucle3	
	    sub       r4,r4,#1  
            add       r2,r0,b     
            add       r1,r1,r11      
      
            bnez      r4,boucle1    
            nop      
            trap      #0
