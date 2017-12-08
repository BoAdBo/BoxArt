import nltk
from nltk.tokenize import sent_tokenize
#from nltk.corpus import twitter_samples
from nltk.tag import pos_tag_sents
from nltk.util import ngrams

# mytext = 'How are you my dear. Dear friend of mine.'

# tokens = sent_tokenize(mytext)
# tokens = nltk.word_tokenize(tokens[0])

# print(tokens)

# #tagged = pos_tag_sents(tokens)
# tagged = nltk.pos_tag(tokens)

# print(tagged)

def print_all(cs):
    for c in cs:
        print(c)

print_all(ngrams('one two three four'.split(' '), 1))
