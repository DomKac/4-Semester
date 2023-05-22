prime(LO, HI, N) :- between(LO, HI, N), isPrime(N).

divisible(X,Y) :- 0 is X mod Y.

divisible(X,Y) :- Y < X/2, divisible(X, Y+1).

isPrime(2) :- true.
isPrime(X) :- X > 1, not(divisible(X, 2)).



