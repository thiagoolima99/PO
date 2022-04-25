import itertools as it
import timeit

def heapify(arr, n, i): 
    largest = i
    l = 2 * i + 1 
    r = 2 * i + 2     
    if l < n and arr[i] < arr[l]: 
        largest = l 
  
    if r < n and arr[largest] < arr[r]: 
        largest = r 
  
    if largest != i: 
        arr[i],arr[largest] = arr[largest],arr[i] # swap 
  
        heapify(arr, n, largest) 
  
def heapSort(arr): 
    n = len(arr) 
   
    for i in range(n, -1, -1): 
        heapify(arr, n, i) 
  
    for i in range(n-1, 0, -1): 
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0) 

lista = list(it.permutations([1, 2, 3, 4, 5, 6], 6))
listaPermut = []

for i in lista:
    listaPermut.append(list(i))

listaAux = listaPermut.copy()

tempos = []

for i in listaPermut:
    tempos.append(timeit.timeit('heapSort({})'.format(i),setup="from __main__ import heapSort",number=30))

maxIndex = tempos.index(max(tempos))
minIndex = tempos.index(min(tempos))

print('Pior caso: ', listaAux[maxIndex])
print('Melhor caso: ', listaAux[minIndex]) 