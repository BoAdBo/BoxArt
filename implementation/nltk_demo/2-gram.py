import nltk
from nltk.util import ngrams
#from nltk.book import text1

n = 2

def train(corpus):
    def app_end(corpus_list):
        for c in corpus_list:
            corpus_list.append()

    sen_tok = nltk.sent_tokenize(corpus)

    #print(sen_tok)
    tokens = list()

    for c in sen_tok:
        tokens += (['<s>'] + nltk.word_tokenize(c) + ['</s>'])

    #print(tokens)
    #print(tokens)
    # Thank god for the implementation
    context = ngrams(tokens, n, pad_left=True, pad_right=True, left_pad_symbol='<s>', right_pad_symbol='</s>')

    freq1 = nltk.FreqDist(tokens)
    freq2 = nltk.FreqDist(context)

    #print(list(context))
    return (freq1, freq2, tokens)

def P_ML(context, word_context, freq_word, freq_ngrams):
        """
        word is str
        context is tuple of the previous 2 words"""
        #print('hi')
        #return freq_word.freq(context + word) / freq_ngrams.freq(context)
        num = freq_ngrams.freq(word_context)
        den = freq_word.freq(context)
        if den == 0:
            return 0
        return num/den


def predict(sentence, freq_word, freq_ngrams):
    # the current word and the context
    tokens = nltk.word_tokenize(sentence)
    context = list(ngrams(tokens, n, pad_left=True, pad_right=True, left_pad_symbol='<s>', right_pad_symbol='</s>'))

    P = 1
    for gram in context:
        word_context = gram
        if n == 2:
            context = gram[-1]
        else:
            context = gram[-(n-1):]
        print(context, word_context)
        P *= P_ML(context, word_context, freq_word, freq_ngrams)
        print(P)


#print(P_ML('.', ('three', 'four')))

raw = open('text', 'r').read()#.replace('\n', ' ')
#corpus = 'one two three four. hello'
#corpus = (nltk.corpus.gutenberg.raw('austen-emma.txt'))
corpus = raw
#sen = 'one two three four.'
#sen = 'I look the other way'
freq1, freq2, tokens = train(corpus)

predict(sen, freq1, freq2)

def generate(tokens):
    def predict_next(context):
    max = -1
    best = '<s>'
    for word in tokens:
        if P_ML(word, context) > max:
            max = P_ML
            best = word
            print(bets)

    return best
