na_lewo(X,Y,[X,Y|_]).
na_lewo(X,Y,[_|Z]) :-
    na_lewo(X,Y,Z).

obok(X,Y,Domy) :-
    na_lewo(X,Y,Domy).
obok(X,Y,Domy) :-
    na_lewo(Y,X,Domy).
% obok([_, _, _, _, _, _],[_, _, _, _, _, _]),
% member(dom(_, _, _, _, _, _), Domy),            

% dom(Numer_domu, narodowosc, kolor_domu, zwierze, co_pije, co_pali)
rybki(Kto) :-
    Domy = [[1, norweg, _, _, _, _],                                    % 1
            [2, _, niebieski, _, _, _],                                 % wywnioskowane z 12
            [3, _, _, _, mleko, _],                                     % 8
            [4, _, _, _, _, _],
            [5, _, _, _, _, _]],
    member([_, anglik, czerwony, _, _, _], Domy),                       % 2
    na_lewo([_, _, zielony, _, _, _],[_, _, bialy, _, _, _], Domy),     % 3
    member([_, dunczyk, _, _, herbata, _], Domy),                       % 4
    obok([_, _, _, _, _, papierosy_light],[_, _, _, koty, _, _], Domy), % 5
    member([_, _, zolty, _, _, cygara], Domy),                          % 6     
    member([_, niemiec, _, _, _, fajka], Domy),                         % 7
    obok([_, _, _, _, _, papierosy_light],[_, _, _, _, woda, _], Domy), % 9
    member([_, _, _, ptaki, _, papierosy_bez_filtra], Domy),            % 10
    member([_, szwed, _, psy, _, _], Domy),                             % 11
    obok([_, norweg, _, _, _, _],[_, _, niebieski, _, _, _], Domy),     % 12
    obok([_, _, _, konie, _, _],[_, _, zolty, _, _, _], Domy),          % 13
    member([_, _, _, _, piwo, mentolowe], Domy),                        % 14
    member([_, _, zielony, _, kawa, _], Domy),                          % 15
    member([_, Kto, _, rybki, _, _], Domy).                     % Tego szukamy

% 1. Norweg zamieszkuje pierwszy dom
% 2. Anglik mieszka w czerwonym domu.
% 3. Zielony dom znajduje się bezpośrednio po lewej stronie domu białego.
% 4. Duńczyk pija herbatkę.
% 5. Palacz papierosów light mieszka obok hodowcy kotów.
% 6. Mieszkaniec żółtego domu pali cygara.
% 7. Niemiec pali fajkę.
% 8. Mieszkaniec środkowego domu pija mleko.
% 9. Palacz papierosów light ma sąsiada, który pija wodę.
% 10. Palacz papierosów bez filtra hoduje ptaki.
% 11. Szwed hoduje psy.
% 12. Norweg mieszka obok niebieskiego domu.
% 13. Hodowca koni mieszka obok żółtego domu.
% 14. Palacz mentolowych pija piwo.
% 15. W zielonym domu pija się kawę.