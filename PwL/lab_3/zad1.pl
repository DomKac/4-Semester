wyrazenie([X], X, X).

wyrazenie(Lista, R, X + Y):-
    podziel_elementy(Lista, X, Y, R1, R2),
    R is R1 + R2.

wyrazenie(Lista, R, X - Y):-
    podziel_elementy(Lista, X, Y, R1, R2),
    R is R1 - R2.

wyrazenie(Lista, R, X * Y):-
    podziel_elementy(Lista, X, Y, R1, R2),
    R is R1 * R2. 

wyrazenie(Lista, R, X / Y):-
    podziel_elementy(Lista, X, Y, R1, R2),
    R2 =\= 0,
    R is R1 / R2.

podziel_elementy(Lista, W1, W2, R1, R2):-
    append([X1|X2], [Y1|Y2], Lista),
    wyrazenie([X1|X2], R1, W1),
    wyrazenie([Y1|Y2], R2, W2).
