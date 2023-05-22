
nieparzysta_lista(L) :- length(L,Y), Z is Y mod 2, Z \= 0.

srodkowy(L,X) :- nieparzysta_lista(L), length(L,Y), S is round(((Y/2) - 0.5)), nth0(S,L,X).
