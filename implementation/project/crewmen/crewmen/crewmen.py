import os
import sqlite3
import pymysql
from flask import Flask, redirect, url_for, render_template, session, g, request, flash
from flask_bootstrap import Bootstrap
from flask_sqlalchemy import SQLAlchemy
from flask_hashing import Hashing
from functools import wraps
from init_crew import init_db

def Init_app():
    app = Flask(__name__)
    app.config.from_object('config.DevelopmentConfig')
    Bootstrap(app)
    return app

app = Init_app()
hashing = Hashing(app)
db = SQLAlchemy(app)

class User(db.Model):
    __tablename__ = 'users'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class Member(db.Model):
    __tablename__ = 'member'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class Training_plan(db.Model):
    __tablename__ = 'training_plan'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class Who_train(db.Model):
    __tablename__ = 'who_train'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class Training_item(db.Model):
    __tablename__ = 'training_item'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class Plan_maker(db.Model):
    __tablename__ = 'plan_maker'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}



def login_required(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'logged_in' in session:
            return f(*args, **kwargs)
        else:
            flash('You need to login first.')
            return redirect(url_for('login'))
    return wrap

@app.route('/home')
@login_required
def home():
    #return "hello world"
    return render_template('home.html', error=None)

@app.route('/training_plan')
@login_required
def show_training_plan():
    today_plan = Training_plan.query.all()
    return render_template('training_plan.html', strength_plan=today_plan)


@app.route('/')
def welcome():
    return render_template('welcome.html', error=None)

@app.route('/logout')
@login_required
def logout():
    session.pop('logged_in', None)
    flash('You were just logged out!')
    return redirect(url_for('welcome'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    try:
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']

            db_pass = User.query.filter_by(username=username).first().password
            print(db_pass)
            hashcode = bytes(hashing.hash_value(password), 'utf8')
            print(hashcode)
            if db_pass == hashcode:
                session['logged_in'] = True
                return redirect(url_for('home'))
            else:
                error = 'Invalid credentials. Please try again'
        else:
            return render_template('login.html')

    except AttributeError:
        error = 'This user is not registered!'

    return render_template('login.html', error=error)

@app.route('/register', methods=['GET', 'POST'])
def register():
    password_error = None
    noID_error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        sec_password = request.form['sec_password']
        email = request.form['email']
        ID = request.form['ID']
        if password != sec_password:
            password_error = 'The second password does not match the first one! Please retry'
        else:
            # Need to check if ID exists
            if not Member.query.filter_by(ID=ID).first():
                noID_error = 'No ID exists in the database'
            else:
                hashpass = bytes(hashing.hash_value(password), 'utf8')

                newuser = User(username=username
                               ,password=hashpass
                               ,email=email
                               ,ID=ID)

                db.session.add(newuser)
                db.session.commit()
                flash('You have just registered. Welcome!')
    return render_template('register.html', password_error=password_error, noID_error=noID_error)

@app.cli.command('initdb')
def initdb_command():
    """ This would drop all table and reconstruct the schema is mysql"""
    init_db()
    print("All table drop and initialized")
