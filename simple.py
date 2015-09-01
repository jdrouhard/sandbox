from trie import Trie
from editdistance import distance

words = Trie()
with open('twl06.txt', 'r') as f:
    for line in f:
        words.insert_word(line.strip().lower())

print distance("a", words)
