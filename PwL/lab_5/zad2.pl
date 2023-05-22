% wykonaj('ex1.prog').

:-consult('zad1_l6.pl').
:-consult('program.pl').
:-consult('interpreter_wyklad.pl').

wykonaj(X):-
	open(X,read,Stream),
	scanner(Stream,Tokeny),
	close(Stream),
	phrase(program(PROGRAM),Tokeny),
	interpreter(PROGRAM).