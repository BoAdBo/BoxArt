import os
import sqlite3
import MySQLdb
from flask import Flask, redirect, url_for

app = Flask(__name__)
#app.config.from_object(__name__)


def get_db(priority):
    root = 'root'
    db_name = 'crewmen'
    return {
        0, MySQLdb.connect(host='localhost', *root, db=db_name)
    }


def init_db():
    """ Need root access to initialize database """
    db = get_db(0)
    with app.open_resource('crewmen.sql', mode='r') as f:
        db.cursor().executescripte(f.read())
    db.commit()

@app.cli.command('initdb')
def initdb_command():
    """ This would drop all table and reconstruct the schema is mysql"""
    init_db()
    print("All table drop and initialized")


@app.route('/login')
def login():
    

# print(__name__)
# print(os.path.join(app.root_path, 'something'))

# if __name__ == '__main__':
#     print(__name__)
#     #run('localhost', 4000, app)
