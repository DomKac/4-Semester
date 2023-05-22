max_sum(L,S):-
    max_sum(L,0,0,S).

max_sum([],MaxSoFar,_,MaxSoFar).
max_sum([H|T],MaxSoFar,CurrentMax,S):-
    NewCurrentMax is max(0,(CurrentMax + H)),
    NewMaxSoFar is max(MaxSoFar,NewCurrentMax),
    max_sum(T,NewMaxSoFar,NewCurrentMax,S).