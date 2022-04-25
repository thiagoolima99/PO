from trie_tree.node import Node


class Trie():
    nodes = []
    def __init__(self):
        self.last_char = False

    def delete(self,string):
        print("Deletando a palavra {} da árvore".format(string))

        string = string.lower()

        string = list(string)
        for node in self.nodes:
            if node.char == string[0]:
                if node.delete(string,1):
                    self.nodes.pop(self.nodes.index(node))

    def add(self,string):
        print("Inserindo a palavra {} na árvore".format(string))
        string = string.lower()
        string = list(string)
        found = False
        for node in self.nodes:
            if node.char == string[0]:
                found = True
                node.char = string[0]
                string.pop(0)
                if len(string) == 0:
                    node.last_char = True
                else:
                    node.add(string)
                break
        if not found:
            node = Node(string[0])
            self.nodes.append(node)
            string.pop(0)
            if len(string) == 1:
                node.last_char = True
            else:
                node.add(string)

    def print(self):
        for node in self.nodes:
            print("____________________________")
            if node.last_char:
                print(node.char.upper(),end=' ')
            else:
                print(node.char, end=' ')

            node.print(1)
    def search(self,string):
        print("\n\nProcurando {} na árvore.\n".format(string))
        if len(string) == 1:
            print("!O tamanho da palavra deve ser maior que 1 char!")
            return False
        string_aux = string
        string = string.lower()
        string = list(string)
        print("Procurando {} em {}.".format(string[0], [i.char for i in self.nodes]))

        for node in self.nodes:
            if node.char == string[0]:
                string.pop(0)
                output = "" if node.search(string) else " NÃO"

                print("╔",end='')

                for i in range(len("╠A palavra {}{} foi encontrada na árvore╣".format(string_aux,output))-2):
                    print("═",end='')

                print("╗",end='')

                print("\n╠A palavra {}{} foi encontrada na árvore╣".format(string_aux,output))
                print("╚",end='')
                for i in range(len("╠A palavra {}{} foi encontrada na árvore╣".format(string_aux,output)) - 2):
                    print("═", end='')
                print('╝',end='')
                break
        else:
            output = ' não'
            print("\n╠A palavra {}{} foi encontrada na árvore╣".format(output, string_aux))
            print("╚", end='')
            for i in range(len("╠A palavra {}{} foi encontrada na árvore╣".format(string_aux,output)) - 2):
                print("═", end='')
            print('╝', end='')