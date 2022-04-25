import random
import timeit
import matplotlib as mpl
import matplotlib.pyplot as plt
import itertools as it

def desenhaGrafico(x, y, graphLabel, fileName, xl = "Quantidade de números", yl = "Tempo"):
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111)
    for i in range(3):
        ax.plot(x, y[i], label = graphLabel[i])
    ax.legend(bbox_to_anchor=(1, 1),bbox_transform=plt.gcf().transFigure)
    plt.ylabel(yl)
    plt.xlabel(xl)
    fig.savefig(fileName)

def shellSort(arr): 
    
    n = len(arr)
    gap = n//2

    while gap > 0: 
        for i in range(gap,n): 
            temp = arr[i] 
            j = i 
            while  j >= gap and arr[j-gap] >temp: 
                arr[j] = arr[j-gap] 
                j -= gap 
            arr[j] = temp 
        gap //= 2

def geraListaInvertida(tam):
    lista = []
    while tam > 0:
        lista.append(tam)
        tam-=1
    return lista

def geraListaOrdenada(tam):
    lista = []
    for i in range(tam):
        lista.append(i)
    return lista

x = [10000, 20000, 30000, 40000, 50000]
yMelhorCaso = []
yMedioCaso = []
yPiorCaso = []

for i in x:
    yMelhorCaso.append(timeit.timeit("shellSort({})".format(geraListaOrdenada(i)),setup="from __main__ import shellSort",number=1))
    
    lista = geraListaOrdenada(i)
    random.shuffle(geraListaOrdenada(i))
    yMedioCaso.append(timeit.timeit("shellSort({})".format(lista), setup="from __main__ import shellSort", number=1))

    yPiorCaso.append(timeit.timeit("shellSort({})".format(geraListaInvertida(i)),setup="from __main__ import shellSort",number=1))

casos = [yMelhorCaso, yMedioCaso, yPiorCaso]
casosLabel = ['Melhor caso', 'Medio caso', 'Pior caso']
desenhaGrafico(x, casos, casosLabel, 'ShellSortCasos.png')