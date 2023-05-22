filozofowie():-
    mutex_create(Fork1),
    mutex_create(Fork2),
    mutex_create(Fork3),
    mutex_create(Fork4),
    mutex_create(Fork5),
    thread_create(filozof(1,Fork1,Fork5),_,[detached(true)]),
    thread_create(filozof(2,Fork2,Fork1),_,[detached(true)]),
    thread_create(filozof(3,Fork3,Fork2),_,[detached(true)]),
    thread_create(filozof(4,Fork4,Fork3),_,[detached(true)]),
    thread_create(filozof(5,Fork5,Fork4),_,[detached(true)]).

filozof(ID,ForkLeft,ForkRight):-
    random(R),
    sleep(R),
    format('[~w] mysli~n',[ID]),
    format('[~w] chce prawy widelec~n',[ID]),
    mutex_lock(ForkRight),
    format('[~w] podniosl prawy widelec~n',[ID]),
    format('[~w] chce lewy widelec~n',[ID]),
    mutex_lock(ForkLeft),
    format('[~w] podniosl lewy widelec~n',[ID]),
    format('[~w] je~n',[ID]),
    format('[~w] odklada lewy widelec~n',[ID]),
    mutex_unlock(ForkLeft),
    format('[~w] odklada prawy widelec~n',[ID]),
    mutex_unlock(ForkRight),
    filozof(ID,ForkLeft,ForkRight).
