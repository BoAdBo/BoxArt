import os
import sqlite3
import pymysql
from flask import Flask, redirect, url_for, render_template, session, g, request, flash, Blueprint, abort
from jinja2 import TemplateNotFound
from flask_bootstrap import Bootstrap
from flask_sqlalchemy import SQLAlchemy
from functools import wraps
from init_crew import init_db
import datetime

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

app.register_blueprint(users_blueprint)


@app.route('/home')
@login_required
def home():
    return render_template('home.html', error=None)

@app.route('/add_plan')
def add_plan():

    return render_template('add_plan.html')

@app.route('/training_plan')
@login_required
def show_training_plan():
    today = datetime.date.today()
    nextday = today + datetime.timedelta(days=1)
    today_plan = TrainingPlan.query.filter(TrainingPlan.train_at >= today, TrainingPlan.train_at < nextday).all()
    #today_plan = TrainingPlan.query.all()
    print(today_plan)
    return render_template('training_plan.html', strength_plan=today_plan)

@app.route('/')
def welcome():
    return render_template('welcome.html', error=None)

@app.cli.command('initdb')
def initdb_command():
    """ This would drop all table and reconstruct the schema is mysql"""
    init_db()
    print("All table drop and initialized")
