#Arvore B+

Implementação de uma árvore B+ com requisitos funcionais:

1. Inserir.
2. Remover.
3. Listar os elementos em ordem (in­order).
4. Listar os elementos de um determinado nível.
5. Procurar por elementos.
6. Imprimir a árvore, em formato compativel com o GraphViz (dotty). 
7. Verificar o balanceamento da árvore.

O protótipo é uma ferramenta de linha de comando. 

arvorebp [arquivo] [operador] [parametros]

Sendo que: 

O formato usado para cada nodo é livre, contanto que represente de maneira suficiente a estrutura de árvore e que cada nodo caiba em um bloco de 1KB (kilo byte).

O operador especifica uma operação a ser executada na árvore.
**­i - inserir**: Insere uma lista de inteiros arbitrários na árvore, especificados nos parâmetros.

**­r - remover**: Remove uma lista de inteiros arbitrários da árvore, especificados no parâmetros.
­
**o - inorder**: Escreve todos os elementos da árvore, ordenados, separados por uma quebra de linha.
­
**l - level**: Escreve todos os elementos de determinado nível da árvore, ordenados, separados por uma quebra de linha. 

**­s - search**: Faz uma busca por elementos na árvore. Os elementos estão especificados nos parâmetros. Caso todos os elementos buscados estiverem presentes, o programa deve retornar código 0. Caso contrário, deve retornar ­1.

**­p - print**: Imprime a árvore em formato compatível com o GraphViz em um arquivo, passado na opção parâmetros.

Exemplos:
- arvorebp arq1.tree ­i 1 2 3 4 5
- Insere os inteiros 1, 2, 3, 4 e 5 na árvore contida no arquivo arq1.tree
- arvorebp arq2.tree ­r 4 9 2
- Removo da árvore contida no arquivo arq2.tree os elementos 4, 9 e 2.
- arvorebp arq1.tree ­l 0
- Imprime o nodo raiz da árvore (nível 0)
- arvorebp arq1.tree ­p arvoreout.dot

Imprime, em formato do graphviz, no arquivo arvoreout.dot, a árvore contida no arquivo arq1.tree
