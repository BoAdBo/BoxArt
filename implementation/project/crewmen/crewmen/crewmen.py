import os
import sqlite3
import pymysql
from flask import Flask, redirect, url_for, render_template, session, g, request, flash, Blueprint, abort
from jinja2 import TemplateNotFound
from flask_bootstrap import Bootstrap
from flask_sqlalchemy import SQLAlchemy
from functools import wraps
from init_crew import init_db
from flask_nav import Nav
from flask_nav.elements import *

########################
### helper function ####
########################

def login_required(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'logged_in' in session:
            return f(*args, **kwargs)
        else:
            flash('You need to login first.')
            return redirect(url_for('login'))
    return wrap

########################
########################
########################


def Init_app():
    app = Flask(__name__)
    app.config.from_object('config.DevelopmentConfig')
    Bootstrap(app)
    return app

app = Init_app()
db = SQLAlchemy(app)
from models import *
from project.users.login import users_blueprint
from project.training.core import training_blueprint

app.register_blueprint(users_blueprint)
app.register_blueprint(training_blueprint)

nav = Nav()
@nav.navigation()
def top():
    items = [View('home', 'home'),
             View('Log out', 'logout'),
             View('Change Password', 'password_update'),
             View('Training', 'show_training_plan'),
             View('Training Item', 'show_item')]

    if session['login_job'] in ['crew leader', 'couch']:
        items = items + [View('Add training plan', 'add_plan'),
                         View('Add Training item', 'add_item')]

    return Navbar('Home', *items)
nav.init_app(app)


@app.route('/home')
@login_required
def home():
    return render_template('home.html', error=None)

@app.route('/')
def welcome():
    return render_template('welcome.html', error=None)

@app.cli.command('initdb')
def initdb_command():
    """ This would drop all table and reconstruct the schema is mysql"""
    init_db()
    print("All table drop and initialized")
