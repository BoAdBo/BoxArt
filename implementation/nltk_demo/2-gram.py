import nltk
from nltk.util import ngrams

n = 2

def train(corpus):
    def app_end(corpus_list):
        for c in corpus_list:
            corpus_list.append()
    sen_tok = nltk.sent_tokenize(corpus)

    tokens = list()

    for c in sen_tok:
        tokens += (['<s>'] + nltk.word_tokenize(c) + ['</s>'])

    #print(tokens)
    # Thank god for the implementation
    context = ngrams(tokens, n, pad_left=True, pad_right=True, left_pad_symbol='<s>', right_pad_symbol='</s>')
    freq1 = nltk.FreqDist(tokens)
    freq2 = nltk.FreqDist(context)
    return (freq1, freq2)

def predict(sentence, freq_word, freq_ngrams):

    def P_ML(word, context):
        """
        word is str
        context is tuple of the previous 2 words"""
        #print('hi')
        #return freq_word.freq(context + word) / freq_ngrams.freq(context)
        num = freq_ngrams.freq(context)
        den = freq_word.freq(word)
        return num/den

    # the current word and the context
    tokens = nltk.word_tokenize(sentence)
    context = list(ngrams(tokens, n, pad_left=True, pad_right=True, left_pad_symbol='<s>', right_pad_symbol='</s>'))

    for gram in context:
        print(gram[-1], gram)
        print(P_ML(gram[-1], gram))

#print(P_ML('.', ('three', 'four')))

corpus = 'one two three four.'
sen = 'one two three four.'
freq1, freq2 = train(corpus)

predict(sen, freq1, freq2)
