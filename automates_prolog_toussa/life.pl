
len([], 0).
len([_Head|Tail], L):-
    L is Lq+1,
    len(Tail, Lq).

concat(L1, [], L1).
concat([], L2, L2).
concat([H|T1], L2, [H|T2]):-
    concat(T1, L2, T2).
    

appartient(Element, [Element|_Reste]).
appartient(Element, [_PasElement|Reste]):-
    appartient(Element, Reste).


split(L, [], L, 0).

split([Head|Tail], [Head|A], B, N):-
    split(Tail, A, B, N_1),
    N is N_1+1.


halve(L, A, B):-
    len(L, Len),
    HLen is Len/2,
    split(L, A, B, HLen).




😂(_).
🐎(_).
🦄(_).
