import itertools as it
import timeit

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

lista = list(it.permutations([1, 2, 3, 4, 5, 6], 6))
listaAux = []
listaPermut = []

for i in lista:
    listaAux.append(list(i))
    listaPermut.append(list(i))

tempos = []


for i in listaPermut:
    tempos.append(timeit.timeit('shellSort({})'.format(i),setup="from __main__ import shellSort",number=1))

maxIdx = tempos.index(max(tempos))
minIdx = tempos.index(min(tempos))

print('Pior caso: ', listaAux[maxIdx])
print('Melhor caso: ', listaAux[minIdx])