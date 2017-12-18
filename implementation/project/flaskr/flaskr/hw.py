from flask import Flask
app = Flask(__name__)

@app.route("/")
def hello():
    #print(__name__)
    return "Hello World!"

