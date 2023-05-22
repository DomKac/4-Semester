

arc(a,b).
arc(b,a).
arc(b,c).
arc(c,d).
osiagalny(X,X) :- true.
osiagalny(X,Y) :- lista(X,Y,[X]).

lista(X,Y,L) :- arc(X,Z), not(member(Z,L)), (Z = Y; lista(Z, Y, [Z|L])).

