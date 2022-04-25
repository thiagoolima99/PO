import sys
import matplotlib as mpl
import matplotlib.pyplot as plt
import timeit
mpl.use('Agg')

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
        
x = [10000, 20000, 30000, 40000, 50000]

yMelhorCaso = []
yMedioCaso = []
yPiorCaso = []

for i in x:
    yMelhorCaso.append(timeit.timeit("heapSort({})".format(sorted(geraLista(i))),setup="from __main__ import heapSort",number=1))
    
    yMedioCaso.append(timeit.timeit("heapSort({})".format(geraLista(i)),setup="from __main__ import heapSort",number=1))
    
    yPiorCaso.append(timeit.timeit("heapSort({})".format(sorted(geraLista(i), reverse=True)),setup="from __main__ import heapSort",number=1))
    
casos = [yMelhorCaso, yMedioCaso, yPiorCaso]
casosLabel = ['Pior caso', 'Medio caso', 'Melhor caso']
desenhaGrafico(x, casos, casosLabel, 'heapSortCasos.png')
    
