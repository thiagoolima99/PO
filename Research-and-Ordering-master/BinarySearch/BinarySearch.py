import timeit
import matplotlib.pyplot as plt
import matplotlib as mpl

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
  i = 1
  while i <= tam: 
      lista.append(i)
      i+=1
  return lista

def buscaBinaria(lista, chave):
  inicio = 0
  fim = len(lista)
  
  while inicio <= fim:
    meio = (inicio + fim)//2
    if lista[meio] == chave:
      return meio
    elif lista[meio] > chave:
      fim = meio - 1
    else:
      inicio = meio + 1

  return -1

def buscaBinariaRecursiva(lista, inicio, fim, chave):
  if inicio > fim:
    return -1
    
  meio = (inicio + fim)//2

  if lista[meio] == chave:
    return meio
  elif lista[meio] > chave:
    return buscaBinariaRecursiva(lista, inicio, meio - 1, chave)
  else:
    return buscaBinariaRecursiva(lista, meio + 1, fim, chave)

def buscaSequencial(lista, chave):
  i = 0
  tam = len(lista)
  while i < tam:
    if lista[i] == chave:
      return i
    i+=1
  return -1

# Problema Soma das casas, https://www.urionlinejudge.com.br/judge/pt/problems/view/2422
# resolver com força bruta, depois com busca binária e comparar os resultado 

# força bruta, não sei se tá certo
def problemaCasasBruteForce(quantidade, soma):
  lista = []
  for i in range(lista):
    lista.append(int(input()))
  
  for i in range(quantidade):
    for j in range(quantidade):
      if lista[i] + lista[j] == soma:
        return [lista[i], lista[j]]


# não sei se tá certo
def problemaCasasBB(quantidade, soma):
  lista = []
  for i in range(lista):
    lista.append(int(input()))
  
  for i in lista:
    resultado = buscaBinariaRecursiva(lista, 0, len(lista), soma-i)
    if resultado != -1:
      return [i, resultado]

x = [100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000]

yBuscaBinariaIterativaa = []
yBuscaBinariaRecursiva = []
yBuscaSequencial = []

for i in x:
  yBuscaBinariaIterativaa.append(timeit.timeit("buscaBinaria({}, {})".format(geraLista(i), i),setup="from __main__ import buscaBinaria",number=100))

  yBuscaBinariaRecursiva.append(timeit.timeit("buscaBinariaRecursiva({}, {}, {}, {})".format(geraLista(i), 0, i, i),setup="from __main__ import buscaBinariaRecursiva",number=100))

  yBuscaSequencial.append(timeit.timeit("buscaSequencial({}, {})".format(geraLista(i), i),setup="from __main__ import buscaSequencial",number=100))

tempos = [yBuscaBinariaIterativaa, yBuscaBinariaRecursiva, yBuscaSequencial]
labels = ['Busca Binária Iterativa', 'Busca Binária Recursiva', 'Busca Sequencial']

desenhaGrafico(x, tempos, labels, 'comparação.png')