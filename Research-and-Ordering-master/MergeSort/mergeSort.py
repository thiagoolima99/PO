from random import randint
import timeit
import matplotlib as mpl
import matplotlib.pyplot as plt

def desenhaGrafico(x, y, graphLabel, fileName, xl = "Quantidade de números", yl = "Tempo"):
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111)
    for i in range(3):
        print(y[i], graphLabel[i])
        ax.plot(x, y[i], label = graphLabel[i])
    ax.legend(bbox_to_anchor=(1, 1),bbox_transform=plt.gcf().transFigure)
    plt.ylabel(yl)
    plt.xlabel(xl)
    fig.savefig(fileName)  

def geraLista(tam):
    lista = []
    while tam > 0:
        lista.append(tam)
        tam-=1
    return lista

def mergeSort(lista):
    if len(lista) < 2: return lista
    
    meio = len(lista)//2
    
    esquerda = mergeSort(lista[:meio])
    direita = mergeSort(lista[meio:])
    
    return merge(esquerda, direita)

def merge(esquerda, direita):
    resultado = []
    i = j = 0

    while i < len(esquerda) and j < len(direita):
        if esquerda[i] < direita[j]:
            resultado.append(esquerda[i])
            i+=1
        else:
            resultado.append(direita[j])
            j+=1
    
    resultado += esquerda[i:]
    resultado += direita[j:]
    
    return resultado

x = [10000, 20000, 30000, 40000, 50000]

yMelhorCaso = []
yMedioCaso = []
yPiorCaso = []

for i in x:
    yMelhorCaso.append(timeit.timeit("mergeSort({})".format(sorted(geraLista(i))),setup="from __main__ import mergeSort",number=1))
    
    yMedioCaso.append(timeit.timeit("mergeSort({})".format(geraLista(i)),setup="from __main__ import mergeSort",number=1))
    
    yPiorCaso.append(timeit.timeit("mergeSort({})".format(sorted(geraLista(i), reverse=True)),setup="from __main__ import mergeSort",number=1))
    
casos = [yMelhorCaso, yMedioCaso, yPiorCaso]
casosLabel = ['Pior caso', 'Medio caso', 'Melhor caso']
desenhaGrafico(x, casos, casosLabel, 'mergeSortCasos.png')


    


