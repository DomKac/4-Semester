%a^nb^n
g1-->[].
g1-->[a],g1,[b].

%a^nb^nc^n
g2-->a(N),b(N),c(N).

a(0)-->[].
a(N)-->[a],a(N1),{N is N1+1}.

b(0)-->[].
b(N)-->[b],b(N1),{N is N1+1}.

c(0)-->[].
c(N)-->[c],c(N1),{N is N1+1}.

%a^nb^fib(n)
g3-->a(N),{fib(N,F)}, b(F).

fib(0,0):-!.
fib(1,1):-!.
fib(N,X):-
	N1 is N-1,
	fib(N1,[1,0],[X|_]).

fib(N,L,L):-
	N=<0,!.

fib(N,[F2,F1|T],L):-
	F3 is F2+F1,
	N1 is N-1,
	fib(N1,[F3,F2,F1|T],L).

%ostatnia gramatyka
p([])-->[].
p([X|Xs])-->[X],p(Xs).