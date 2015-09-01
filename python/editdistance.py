#from trie import Trie
import sys

class Trie:
    def __init__(self):
        self.children = {}
        self.is_word = False

    def insert_word(self, word):
        if len(word) == 0:
            self.is_word = True
            return
        letter = word[0]
        if letter not in self.children:
            self.children[letter] = Trie()
        self.children[letter].insert_word(word[1:])

    def contains(self, word):
        if len(word) == 0:
            return self.is_word
        letter = word[0]
        if letter in self.children:
            return self.children[letter].contains(word[1:])
        return False

def distance_helper(dict_node, letter, word, word_length, prev_row, dist):
    next_row = list(range(word_length+1))
    next_row[0] = prev_row[0]+1

    row_min = sys.maxsize
    for i in range(word_length):
        if word[i] == letter:
            cur_row_min = prev_row[i]
        else:
            cur_row_min = min(next_row[i]+1, prev_row[i]+1, prev_row[i+1]+1)
        next_row[i+1] = cur_row_min
        if cur_row_min < row_min:
            row_min = cur_row_min

    if next_row[-1] < dist and dict_node.is_word:
        dist = next_row[-1]

    if row_min < dist:
        for child in dict_node.children:
            dist = distance_helper(dict_node.children[child], child, word, word_length, next_row, dist)
            if dist == 1:
                return 1

    return dist

def distance(word, dict_words):
    if dict_words.contains(word):
        return 0

    word_length = len(word)
    row = list(range(word_length+1))
    dist = sys.maxsize
    for child in dict_words.children:
        temp_dist = distance_helper(dict_words.children[child], child, word, word_length, row, dist)
        if temp_dist == 1:
            return 1
        elif temp_dist < dist:
            dist = temp_dist

    return dist


def main():
    dictionary = Trie()

    #with open('twl06.txt', 'r') as f:
        #for line in f:
            #dict_words.insert_word(line.strip().lower())

    lines = sys.stdin.readlines()
    num_dict_words = int(lines[0])
    dict_words = [x.strip() for x in lines[:num_dict_words+1]]
    #map(lambda word: dictionary.insert_word(word), dict_words)
    for word in dict_words:
        dictionary.insert_word(word)
    words = [x.strip() for x in lines[num_dict_words+2:]]

    distances = [distance(word, dictionary) for word in words]
    print(sum(distances))


if __name__ == '__main__':
    sys.exit(main())
