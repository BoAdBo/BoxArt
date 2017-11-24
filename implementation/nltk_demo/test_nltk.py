import nltk
from bs4 import BeautifulSoup
import urllib.request
from nltk.corpus import stopwords
import nltk
from nltk.tokenize import sent_tokenize

response = urllib.request.urlopen("http://php.net/")
html = response.read()
soup = BeautifulSoup(html, "html5lib")

text = soup.get_text(strip=True)
sr = stopwords.words('english')
tokens = text.split()
clean_tokens = list()

for token in tokens:
    if token not in sr:
        clean_tokens.append(token)

freq = nltk.FreqDist(clean_tokens)

# for key, val in freq.items():
#      print(str(key) + ':' + str(val))

mytext = "Hello Mrs. Good morning. How are you?"
print(sent_tokenize(mytext))

freq.plot(20, cumulative=False)

#print(tokens)
