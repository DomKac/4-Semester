% open('ex1.prog', read, X), scanner(X, Y), close(X),phrase(program(PROGRAM), Y).

program([])-->[].
program([INSTRUKCJA|PROGRAM])-->
	instrukcja(INSTRUKCJA),
	[sep(';')],
	program(PROGRAM).

instrukcja(assign(ID,WYRAŻENIE))-->
	[id(ID),sep(':=')],
	wyrażenie(WYRAŻENIE).

instrukcja(read(ID))-->
	[key(read),id(ID)].

instrukcja(write(WYRAŻENIE))-->
	[key(write)],
	wyrażenie(WYRAŻENIE).

instrukcja(if(WARUNEK,PROGRAM))-->
	[key(if)],
	warunek(WARUNEK),
	[key(then)],
	program(PROGRAM),
	[key(fi)].

instrukcja(if(WARUNEK,PROGRAM1,PROGRAM2))-->
	[key(if)],
	warunek(WARUNEK),
	[key(then)],
	program(PROGRAM1),
	[key(else)],
	program(PROGRAM2),
	[key(fi)].

instrukcja(while(WARUNEK,PROGRAM))-->
	[key(while)],
	warunek(WARUNEK),
	[key(do)],
	program(PROGRAM),
	[key(od)].


wyrażenie(WYRAŻENIE)-->składnik(WYRAŻENIE).

wyrażenie(WYRAŻENIE1 + WYRAŻENIE2)-->
	składnik(WYRAŻENIE1),
	[sep('+')],
	wyrażenie(WYRAŻENIE2).

wyrażenie(WYRAŻENIE1 - WYRAŻENIE2)-->
	składnik(WYRAŻENIE1),
	[sep('-')],
	wyrażenie(WYRAŻENIE2).

składnik(WYRAŻENIE)-->
	czynnik(WYRAŻENIE).
składnik(WYRAŻENIE1 * WYRAŻENIE2)-->
	czynnik(WYRAŻENIE1),
	[sep('*')],
	składnik(WYRAŻENIE2).
składnik(WYRAŻENIE1 / WYRAŻENIE2)-->
	czynnik(WYRAŻENIE1),
	[sep('/')],
	składnik(WYRAŻENIE2).
składnik(WYRAŻENIE1 mod WYRAŻENIE2)-->
	czynnik(WYRAŻENIE1),
	[key('mod')],
	składnik(WYRAŻENIE2).


czynnik(id(ID))-->
	[id(ID)].
czynnik(int(NUM))-->
	[int(NUM)].
czynnik(WYRAŻENIE)-->
	[sep('(')],
	wyrażenie(WYRAŻENIE),
	[sep(')')].

warunek(WARUNEK)--> 
	koniunkcja(WARUNEK).
warunek((WARUNEK1 ; WARUNEK2))-->
	koniunkcja(WARUNEK1),
	[key(or)],
	warunek(WARUNEK2).

koniunkcja(WARUNEK)-->
	prosty(WARUNEK).
koniunkcja((WARUNEK1 , WARUNEK2))-->
	prosty(WARUNEK1),
	[key(and)],
	koniunkcja(WARUNEK2).

prosty((WYRAŻENIE1=:=WYRAŻENIE2))-->
	wyrażenie(WYRAŻENIE1),
	[sep('=')],
	wyrażenie(WYRAŻENIE2).
prosty((WYRAŻENIE1=\=WYRAŻENIE2))-->
	wyrażenie(WYRAŻENIE1),
	[sep('/=')],
	wyrażenie(WYRAŻENIE2).
prosty((WYRAŻENIE1<WYRAŻENIE2))-->
	wyrażenie(WYRAŻENIE1),
	[sep('<')],
	wyrażenie(WYRAŻENIE2).
prosty((WYRAŻENIE1>WYRAŻENIE2))-->
	wyrażenie(WYRAŻENIE1),
	[sep('>')],
	wyrażenie(WYRAŻENIE2).
prosty((WYRAŻENIE1=<WYRAŻENIE2))-->
	wyrażenie(WYRAŻENIE1),
	[sep('=<')],
	wyrażenie(WYRAŻENIE2).
prosty((WYRAŻENIE1>=WYRAŻENIE2))-->
	wyrażenie(WYRAŻENIE1),
	[sep('>=')],
	wyrażenie(WYRAŻENIE2).