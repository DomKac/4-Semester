on(block4, block3). /* block4 leży na block3 */
on(block3, block2).
on(block2, block1).

above(X,Y) :- on(X,Y).
above(X,Y) :- on(X,Z), above(Z,Y).

