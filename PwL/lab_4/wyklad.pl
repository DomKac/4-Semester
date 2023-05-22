czytaj(X) :-
    get_char(C),
    czytaj_dalej(C, X).

czytaj_dalej(end_of_file, []) :-
    !.
    czytaj_dalej(C1, X) :-
    bialy(C1),
    !,
    get_char(C2),
    czytaj_dalej(C2, X).
    czytaj_dalej(C1, [H | T]) :-
    czytaj_slowo(C1, C2, '', H),
    czytaj_dalej(C2, T).

bialy(''). % spacja
bialy('\t'). % tabulacja
bialy('\n').  % nowa linia

czytaj_slowo(end_of_file, end_of_file, N, N) :-
    !.
    czytaj_slowo(C, C, N, N) :-
    bialy(C),
    !.
    czytaj_slowo(C1, C3, N1, N) :-
    atom_concat(N1, C1, N2),
    get_char(C2),
    czytaj_slowo(C2, C3, N2, N).

