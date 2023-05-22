% open('ex1.prog', read, X), scanner(X, Y), close(X), write(Y).

scanner(Stream,Tokens) :-
	current_input(Input),
	set_input(Stream),
	czytaj(Tokens),
	set_input(Input).

czytaj(X) :-
	get_char(C),
	czytaj_dalej(C,[],X).

czytaj_dalej(end_of_file,L,L) :- 
    !.

czytaj_dalej(C,ACC,X) :-
	bialy(C),
    !,
	get_char(C2),
	czytaj_dalej(C2,ACC,X).

czytaj_dalej(C,ACC,X) :-
	czytaj_slowo(C,C2,'',H),
	check_token(ACC,H,L),
	czytaj_dalej(C2,L,X).

czytaj_slowo(end_of_file,end_of_file,N,N) :- 
    !.
czytaj_slowo(C,C,N,N) :-
    bialy(C),
    !.
czytaj_slowo(C1,C2,N1,N2) :-
	atom_concat(N1,C1,N3),
	get_char(C3),
	czytaj_slowo(C3,C2,N3,N2).

check_token(L,end_of_file,L) :-
    !.
check_token(L,X,L2):-
	atom_chars(X,CS),
	last(CS,Y),
	Y = ';' -> (select(Y,CS,NL),
				!,
		        atom_chars(T,NL),
		        add_token(L,T,L3),
		        add_sep(L3,Y,L2));
                add_token(L,X,L2).

add_token(L,end_of_file,L) :- 
    !.
add_token(L,X,L2) :-
	((key(X)->add_key(L,X,L2));
	(sep(X)->add_sep(L,X,L2));
	(((atom_number(X,N),integer(N),N>=0)->add_int(L,N,L2));
	((atom_chars(X,CS),id(CS))->add_id(L,X,L2);
	L = L2))).

key(X) :-
    member(X,['read','write','if','then','else','fi','while','do','od','and','or','mod']).
sep(X) :-
	member(X,[';','+','-','*','/','(',')','<','>','=<','>=',':=','=','/=']).

id(X) :-
	\+ (member(C,X),
	char_type(C,lower)).

bialy(X) :- member(X,['\t','\n',' ']).

add_key(L,X,L2) :-
	Y = key(X),
	append(L,[Y],L2).

add_sep(L,X,L2) :-
	Y = sep(X),
	append(L,[Y],L2).

add_int(L,X,L2) :-
	Y = int(X),
	append(L,[Y],L2).

add_id(L,X,L2) :-
	Y = id(X),
	append(L,[Y],L2).