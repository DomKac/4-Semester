even_permutation([], []).
even_permutation([H|T], Ys) :- even_permutation(T, P), insert_odd(H, P, Ys).
even_permutation([H|T], Ys) :- odd_permutation(T, P), insert_even(H, P, Ys).

odd_permutation([H|T], Ys) :- odd_permutation(T, P), insert_odd(H, P, Ys).
odd_permutation([H|T], Ys) :- even_permutation(T, P), insert_even(H, P, Ys).

insert_odd(X, InList, [X|InList]).
insert_odd(X, [Y,Z|InList], [Y,Z|OutList]) :- insert_odd(X, InList, OutList).

insert_even(X, [Y|InList], [Y,X|InList]).
insert_even(X, [Y,Z|InList], [Y,Z|OutList]) :- insert_even(X, InList, OutList).