:- use_module(library(clpfd)).

lista_zadan([ 
   %D R1 R2
   [2, 1, 3],
   [3, 2, 1],
   [4, 2, 2],
   [3, 3, 2],
   [3, 1, 1],
   [3, 4, 2],
   [5, 2, 1]]).

resources(5, 5).

mt([], _, [], [], [], _).
mt([[D, X1, X2] | L1], H, [task(S, D, E, X1, _) | L2],
	[task(S, D, E, X2, _) | L3], [S | L4], MS) :-
    S in 0..H,
    E #= S + D, MS #>= E,
    mt(L1, H, L2, L3, L4, MS).

schedule(H, Ss, MS) :-
    lista_zadan(L),
    resources(X1, X2),
    MS in 0..H,
    mt(L, H, Y1, Y2, Ss, MS),
    cumulative(Y1, [limit(X1)]),
    cumulative(Y2, [limit(X2)]),
    once(labeling([min(MS), ff], [MS | Ss])).




