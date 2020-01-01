%ex_to_af(R, I, J, Sigma).

initial(0).

ex_to_af(epsilon, I, J, _Sigma):-
    assert(initial(I)),
    assert(terminal(I)),
    J is I+1.

ex_to_af(vide, I, J, _Sigma):-
    assert(initial(I)),
    J is I+1.

ex_to_af(X, I, J, Sigma):-
    assert(initial(I)),
    member(X, Sigma),
    I1 is I+1,
    assert(delta(I, X, I1)),
    assert(terminal(I1)),
    J is I+2.


ex_to_af(R1+R2, I, J, Sigma):-
    assert(initial(I)),
    I1 is I+1,
    er_to_af(R1, I1, J1, Sigma),
    er_to_af(R2, J1, J, Sigma),
    assert(delta(I, epsilon, I1)),
    assert(delta(I, epsilon, J1)),
    retract(initial(I1)),
    retract(initial(J1)).


entre(A, B, C):-
    between(A, B-1, C).


pour_tout(A, B):-
    A, B, fail.

pour_tout(_A, _B).

    

ex_to_af(R1*R2, I, J, Sigma):-
    assert(initial(I)),
    er_to_af(R1, I, J1, Sigma),
    er_to_af(R2, J1, J, Sigma),
    retract(initial(J1)),
    pour_tout((entre(I, J1, T), terminal(T)), assert(delta(T, epsilon, J1))),
    pour_tout((entre(I, J1, T), terminal(T)), retract(terminal(T))).


