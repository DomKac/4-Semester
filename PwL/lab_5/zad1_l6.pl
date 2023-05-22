

scanner(Stream,Tokens) :-
	current_input(Input),
	set_input(Stream),
	czytaj(Tokens),
	set_input(Input).

czytaj(X) :-
	get_char(C),
	czytaj_dalej(C,X).

czytaj_dalej(end_of_file,[]) :- 
    !.

czytaj_dalej(C,X) :-
	bialy(C),
    !,
	get_char(C2),
	czytaj_dalej(C2,X).

czytaj_dalej(C,[H|T]) :-
    category(C,CAT),
	czytaj_slowo(C,C2,'',S,CAT),
    label(H,S,CAT),
	czytaj_dalej(C2,T).

czytaj_slowo(end_of_file,end_of_file,N,N,_) :- 
    !.
czytaj_slowo(C,C,N,N,_) :-
    bialy(C),
    !.
czytaj_slowo(C,C,N,N,CAT) :- 
    \+ category(C,CAT),!.
czytaj_slowo(C1,C2,N1,N2,CAT) :- 
	atom_concat(N1,C1,N3),
	get_char(C3),
	czytaj_slowo(C3,C2,N3,N2,CAT).

category(C,id):-
    char_type(C,upper).
category(C,key):-
    char_type(C,lower).
category(C,sep):-
    sepchar(C).
category(C,int):- 
    atom_number(C,N),
	integer(N).

keyword(X) :-
    member(X,['read','write','if','then','else','fi','while','do','od','and','or','mod']).
separator(X) :-
	member(X,[';','+','-','*','/','(',')','<','>','=<','>=',':=','=','/=']).
sepchar(X):-
	member(X,[';','+','-','*','/','(',')','<','>','=',':']).

id(X) :-
	\+ (member(C,X),
	char_type(C,lower)).

bialy(X) :- member(X,['\t','\n',' ']).

label(H,S,id):-H=id(S).

label(H,S,key):-
	keyword(S),
	H=key(S).
label(H,S,sep):-
	separator(S),
	H=sep(S).
label(H,S,int):-
	atom_number(S,N),
	integer(N),
	N >=0,
	H=int(N).