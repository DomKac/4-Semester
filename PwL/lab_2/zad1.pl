wariancja(L,D):- 
   length(L,X), X > 0, 
   sum_list(L,Sum), Avg is Sum/X, 
   kwadraty_odchylen(L,Avg,K), D is K/X.

kwadraty_odchylen([],_,0).
kwadraty_odchylen([H|T],S,K) :- kwadraty_odchylen(T,S,R), 
K is (H - S)*(H - S) + R.

sum_list([], 0).
sum_list([H|T], Sum) :-
   sum_list(T, Rest),
   Sum is H + Rest.