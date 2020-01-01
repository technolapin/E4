animal([c, h, e, v, a, l]).


mutant(A1, A2, M):-
    animal(A1),
    animal(A2),
    overlap(A1, A2, M).


overlap(AA1|B, B|AA2, M):-
    overlap(AA1|B, AA2, M).


overlap(A1, A2, M):-
    M is A1|A2.
	
