% hetmany(12, X), board(X).

board(X):-
    length(X,L),
    rysuj(X,1,L).

% hetmany(N, P) zachodzi, gdy permutacja P
% koduje poprawne ustawienie N hetmanów
hetmany(N, P):-
    numlist(1, N, L),
    permutation(L,P),
    dobra(P).

dobra(P) :-
    \+ zla(P).

zla(P) :-
    append(_, [Wi | L1], P),
    append(L2, [Wj | _ ], L1),
    length(L2, K),
    abs(Wi - Wj) =:= K + 1.

% główna petla do rysowania
% Lista hetmanów,aktualna kolumna, rozmiar tablicy
rysuj(_,Nk,Roz):-
    Nk > Roz,
    rysuj_przerywana(Roz),
    nl, % new line
    !.
rysuj(Tab,Nk,Roz):-
    rysuj_przerywana(Roz),
    Y is Roz - Nk +1,
    rysuj_linie(1,Y,Tab,Roz),
    rysuj_linie(1,Y,Tab,Roz),
    Nk1 is Nk +1,
    rysuj(Tab,Nk1,Roz),
    !.

% numer wiersza,numer kolumny-rozmiar+1, tablica hetmanow,rozmiar tablicy
% |:::::|     |:::::|     |:::::| ### |:::::|     |:::::|     |:::::|     |
% |:::::|     |:::::|     |:::::| ### |:::::|     |:::::|     |:::::|     |
rysuj_linie(Nw,_,_,Roz):-
    Roz + 1 =:= Nw,
    write('|'),
    nl,
    !.
rysuj_linie(Nw,Nk,Tab,Roz):-
    nth1(Nw,Tab,Nk), % Is true when Nk is the Nw’th element of Tab. Counting starts at 1.
    (((Nw mod 2 =:= 0, Nk mod 2 =:= 1); (Nw mod 2 =:= 1, Nk mod 2 =:= 0)) -> 
    write('| ### ') ; write('|:###:')),
    Nw1 is Nw + 1,
    rysuj_linie(Nw1,Nk,Tab,Roz),
    !.
rysuj_linie(Nw,Nk,Tab,Roz):-
    (((Nw mod 2 =:= 0, Nk mod 2 =:= 1);
    (Nw mod 2 =:= 1, Nk mod 2 =:= 0)) -> write('|     ') ; write('|:::::')),
    Nw1 is Nw + 1,
    rysuj_linie(Nw1,Nk,Tab,Roz),
    !.

% rysujemy kontury pól szachownicy 
% +-----+-----+-----+-----+-----+
rysuj_przerywana(0):-
    write('+'),
    nl,
    !.
rysuj_przerywana(Rozmiar):-
    write('+-----'),
    R is Rozmiar - 1,
    rysuj_przerywana(R).
