class Trie:
    def __init__(self):
        self.children = {}
        self.is_word = False

    def insert_word(self, word):
        node = self
        for letter in word:
            if letter not in node.children:
                node.children[letter] = Trie()
            node = node.children[letter]

        node.is_word = True

    def contains(self, word):
        node = self
        for letter in word:
            if letter not in node.children:
                return False
            node = node.children[letter]

        return node.is_word
