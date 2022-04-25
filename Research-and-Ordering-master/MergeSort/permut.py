import itertools as it
import timeit

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

lista = list(it.permutations([1, 2, 3, 4, 5, 6], 6))
listaPermut = []

for i in lista:
    listaPermut.append(list(i))

listaAux = listaPermut.copy()

tempos = []

for i in listaPermut:
    tempos.append(timeit.timeit('mergeSort({})'.format(i),setup="from __main__ import mergeSort",number=30))

maxIndex = tempos.index(max(tempos))
minIndex = tempos.index(min(tempos))

print('Pior caso: ', listaAux[maxIndex])
print('Melhor caso: ', listaAux[minIndex]) 

