import networkx as nx
import matplotlib.pyplot as plt
import numpy as numpy
import random


# N - macierz natężeń strumienia pakietów
# G - graf (model sieci)

# randomowe liczby z przedziału 1-9, ustawiamy rozmiar macierzy na 20 x 20
N = numpy.random.randint(0, 100, size=(20, 20))
N[numpy.diag_indices_from(N)] = 0  # przekątną grafu uzupełniamy 0
# print(N)
# print(N+10)

G = nx.Graph()
# węzły grafu numerowane liczbami od 1 do 20.
G.add_nodes_from(list(range(1, 21)))
G.add_edge(1, 2)
G.add_edge(1, 3)
G.add_edge(2, 4)
G.add_edge(2, 5)
G.add_edge(3, 5)
G.add_edge(3, 6)
G.add_edge(4, 7)
G.add_edge(4, 8)
G.add_edge(5, 8)
G.add_edge(5, 9)
G.add_edge(6, 9)
G.add_edge(6, 10)
G.add_edge(7, 12)
G.add_edge(8, 12)
G.add_edge(8, 13)
G.add_edge(9, 13)
G.add_edge(9, 14)
G.add_edge(10, 14)
G.add_edge(11, 16)
G.add_edge(11, 18)
G.add_edge(12, 17)
G.add_edge(13, 17)
G.add_edge(13, 18)
G.add_edge(13, 19)
G.add_edge(14, 19)
G.add_edge(15, 18)
G.add_edge(15, 20)
G.add_edge(16, 17)
G.add_edge(17, 18)
G.add_edge(18, 19)
G.add_edge(19, 20)


# Tablica przechowująca usunięte krawędzie
removed_edges = []

# FUNKCJE


def a(v1, v2):

    suma = 0
    for vi in G.nodes():
        for vj in G.nodes():
            try:
                for path in nx.all_shortest_paths(G, vi, vj):
                    if (v1 in path) and (v2 in path):
                        suma = suma + N[vi-1][vj-1]
            except nx.exception.NetworkXNoPath:
                suma = suma
    return suma

# Pytanie: jak własciwie ustalic c(e)?
# czy przyjąc jakąś wartość z góry, a może każdemu n(i,j) przpisać maksymymalną
# ustaloną wartość z random.randint? (ja tak robię)

def c(multiplier):
     return 10 * multiplier


# def c(v1, v2):

#     # suma = 0
#     # for vi in range(1, 21):
#     #     for vj in range(1, 21):
#     #         for path in nx.all_shortest_paths(G, vi, vj):
#     #             if (v1 in path) and (v2 in path):
#     #                 # maksymalna wartośc jaką może przyjąć n(i,j) w macierzy wynosi w moim przypadku 9
#     #                 suma += 9
#     # return suma



# średnie opóźnienie pakietu w sieci
# m ~ 8000
# ctrl + tab <num> nowe okno
# ctrl+ P wybierasz plik z workspace
# ctrl + tab zmienisz focus okna

def T(m):  # 'm' jest średnią wielkością pakietu w bitach
    
    matrix_sum = sum(map(sum,N))
    SumT = 0
    for edge in G.edges():
        v1 = edge[0]
        v2 = edge[1]
        val_a = G[v1][v2]['a'] #a(v1, v2)
        val_c = G[v1][v2]['c'] #c(val_a,multiplier)
        SumT += ((val_a) / ((val_c / m) - val_a))

    return (SumT/matrix_sum)

# dla m = 1 funkca T przyjmuje u mnie wartosci zblizone do 0.02.
# Na potrzeby testów niech T_max przyjmie przykładowo wartość 0.03


def assign_edges_a_and_c(multiplier):
    for edge in G.edges():
        val_a = a(edge[0], edge[1])
        val_c = c(multiplier)
        G[edge[0]][edge[1]]['a'] = val_a
        G[edge[0]][edge[1]]['c'] = val_c



removed_edges = list()

def delete_edges(p):

    for edge in G.edges():
        los = random.randint(0, 100)
        if los > p:
            removed_edges.append(edge)
            G.remove_edge(edge[0], edge[1])


def reconstruct_graph(multiplier):
    for unlucky_edge in removed_edges:
        G.add_edge(unlucky_edge[0], unlucky_edge[1])
    assign_edges_a_and_c(multiplier)
    removed_edges.clear()


# def a_exceeded_c_somewhere(m):
#     for edge in G.edges():
#         if (G[edge[0]][edge[1]]['a'] > ( G[edge[0]][edge[1]]['c'] / m)):
#             return True
#     return False


def works_correctly(T_max, m):
    tm =  T(m)
    return (nx.is_connected(G) and tm > 0 and tm < T_max) # not(a_exceeded_c_somewhere(m))
# nx.is_connected(G) and
# Pytanie: Czy powinniśmy za każdym razem losować nową macierz natężeń?

def Network_Reliability(T_max, m, p, c_multiplier):
    assign_edges_a_and_c(c_multiplier)
    test_passed = 0
    for i in range(0, 100):
        # print(f"proba nr: {i}")
        delete_edges(p)
        assign_edges_a_and_c(c_multiplier)
        #print(f"T(m): {T(m)}")
        #print(f"T(m) < T_max : {T(m) < T_max}")
        #print(f"G is connected: {nx.is_connected(G)}")
        #print(f"not(a_exceeded_c_somewhere): {not(a_exceeded_c_somewhere(m))}")
        if works_correctly(T_max, m):
            #print("passed")
            test_passed = test_passed + 1
        reconstruct_graph(c_multiplier)
    
    return (test_passed/100)

def increase_matrix(matrix, n):
    matrix = matrix * n
    matrix[numpy.diag_indices_from(matrix)] = 0  # przekątną grafu uzupełniamy 0
    return matrix

def add_edges(multiplier):
    non_edges = list(nx.non_edges(G))
    v1,v2 = random.sample(non_edges,1)[0]
    non_edges.remove((v1,v2))
    G.add_edge(v1,v2)
    G[v1][v2]["c"] = c(multiplier)

    # KONIEC FUNKCJI

# print(f"Sredni opoznienie pakietu w sieci: {T(1)}")

# Test I - Zwiększanie wartości w macierzach

# max_t = 0.03
# mm = 2
# pp = 95  # wartosc prawdopodobientwa w procentach
# multi = 10000


# for x in range(0,20):
#     N = increase_matrix(N, 1.1)
#     rel = Network_Reliability(max_t,mm,pp,multi)
#     print( f"Niezawodność sieci w tym teście wynosi: {rel}")

# Test II - Zwiększanie przepustowości

# max_t = 0.03
# mm = 2
# pp = 95  # wartosc prawdopodobientwa w procentach
# multi = 1000

# for x in range(0,20):
#     multi = multi * 1.1
#     rel = Network_Reliability(max_t,mm,pp,multi)
#     print( f"Niezawodność sieci w tym teście wynosi: {rel}")


# Test III - Zwiększanie wartości w macierzach

max_t = 0.03
mm = 2
pp = 95  # wartosc prawdopodobientwa w procentach
multi = 1000


for x in range(0,20):
    rel = Network_Reliability(max_t,mm,pp,multi)
    print( f"Niezawodność sieci w tym teście wynosi: {rel}")
    add_edges(multi)


# \/ Określenie wyglądu grafu (przykładowej "sieci") i wyświetlenie go \/
pos1 = nx.nx_pydot.graphviz_layout(G, prog='sfdp')
labels = nx.get_edge_attributes(G, 'a')
nx.draw_networkx_edge_labels(G, pos=pos1, edge_labels=labels)
nx.draw(G, pos=pos1, with_labels=True)
plt.show()
