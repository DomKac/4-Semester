lista_pom(N, L) :-
    findall(Num1, between(1, N, Num1), L1),
    findall(Num2, between(1, N, Num2), L2),
    append(L1,L2,L).

odl(X,[X|_], 0).
odl(X, [_ | L], Ile) :- odl(X,L,IleNew), Ile is IleNew+1.

odl2([],0).
odl2([H|T],Ile) :- odl(H,T,Ile).

odlall([],[_|0]).
odlall([H|T],[S|Ile]) :- odl(H,T,S),  odlall(T,Ile).

lista(N,X) :- lista_pom(N,L), permutation(L,X), \+ (append(_,[A|B],X), append(C,[A|_],B), length(C,K), K mod 2 =:= 1).
























