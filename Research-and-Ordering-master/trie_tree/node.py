class Node():
    def __init__(self, char):
        self.children = []
        self.char = char
        self.last_char = False

    def delete(self, string, index):
        for child in self.children:
            if child.char == string[index]:
                # print(child.char)
                if (len(string) == index + 1):
                    # print(child.last_char)
                    aux = child.last_char
                    aux1 = len(child.children) == 0
                    if aux1:
                        self.children.pop(self.children.index(child))
                    else:
                        child.last_char = False
                    return (not self.last_char and len(self.children) == 0)
                else:
                    # print(string[index+1])
                    if child.delete(string, index + 1):
                        self.children.pop(self.children.index(child))
                        return (not self.last_char and len(self.children) == 0)
                    else:
                        # print(self.char)
                        return False

    def add(self, char_list):

        if len(char_list) == 0:
            return
        found = False
        for child in self.children:
            if child.char == char_list[0]:
                found = True
                if len(char_list) == 1:
                    child.last_char = True
                char_list.pop(0)
                child.add(char_list)
                break

        if not found:
            child = Node(char_list[0])
            self.children.append(child)
            char_list.pop(0)
            if len(char_list) == 0:
                child.last_char = True
            else:
                child.add(char_list)

    def print(self, tabs):
        print('')
        for child in self.children:
            for i in range(tabs):
                print('\t', end='│')
            if child.last_char:
                print((child.char).upper(), end=' ')
            else:
                print((child.char), end='')

            child.print(tabs + 1)

    def search(self, string):
        print("Procurando {} em {}.".format(string[0], [i.char for i in self.children]))
        for child in self.children:
            if child.char == string[0]:
                if len(string) == 1:
                    return child.last_char
                else:
                    string.pop(0)
                    if child.search(string):
                        return True
                    else:
                        return False

        return False
