import os
import sqlite3
import pymysql
from flask import Flask, redirect, url_for, render_template, session, g, request
from flask_bootstrap import Bootstrap



#app.config.from_object(__name__)

def create_app():
    app = Flask(__name__)
    Bootstrap(app)
    return app

app = create_app()

@app.teardown_appcontext
def close_connection(error):
    """Closes the database again at the end of the request."""
    if hasattr(g, 'mysql_con'):
        g.mysql_con.close()

def get_connection(priority):
    db_name = 'crewmen'
    user_passwd = [
        ('crew-root', 'crew-root'),
        ('crew-leader', 'crew-leader'),
        ('crew-member', 'crew-member')
    ]

    if priority < 0 or priority > 2:
        raise "priority out of bound!"

    if not hasattr(g, 'mysql_con'):
        g.mysql_con = pymysql.connect(host='localhost', user=user_passwd[priority][0], password=user_passwd[priority][1], db=db_name, charset='utf8')
    return g.mysql_con

def init_db():
    """ Need root access to initialize database """
    connection = get_connection(0)

    try:
        with app.open_resource('crew-management.sql', mode='r') as f:
            with connection.cursor() as cursor:
                cursor.execute(f.read())
                connection.commit()
    finally:
        connection.close()

@app.cli.command('initdb')
def initdb_command():
    """ This would drop all table and reconstruct the schema is mysql"""
    init_db()
    print("All table drop and initialized")


@app.route('/login', methods=['GET', 'POST'])
def login():
    #db = get_db(0)
    #cur = db.execute('select * from ')
    error = None
    con = get_connection(2)
    if request.method = 'POST':
        username = request.form['username']
        password = request.form['password']
        with con.cursor() as cursor:
            cursor.execute('select password from user where username = %s', username)

        

@app.route('/')
def show():
    if not session.get('logged_in'):
        abort(401)

    return render_template('base.html', error=None)



# print(__name__)
# print(os.path.join(app.root_path, 'something'))

# if __name__ == '__main__':
#     print(__name__)
#     #run('localhost', 4000, app)
