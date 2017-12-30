##############
### import ###
##############
from flask import Flask, redirect, url_for, render_template, session, g, request, flash, Blueprint, abort
from flask_hashing import Hashing
from crewmen import app
from crewmen import login_required
from models import *
from flask_bcrypt import Bcrypt
from flask_nav import Nav
from flask_nav.elements import *

nav = Nav()
topbar = Navbar('Home Center', Navbar('',
                              View('home', 'home'),
                              View('Log out', 'logout'),
                              View('Change Password', 'password_update'),)
)

nav.register_element('top', topbar)
nav.init_app(app)

hashing = Hashing(app)
bcrypt = Bcrypt(app)

##############
### config ###
##############

users_blueprint = Blueprint(
    'users', __name__,
    template_folder='templates'
)

##########################
#### helper functions ####
##########################

"""
User system information, to log in/out, to register, (unimplemented)to change password, email(no username updating)
"""

###########################
#### Users interaction ####
###########################


@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    try:
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']

            db_pass = User.query.filter_by(username=username).first().password
            db_pass = db_pass.decode("utf8")

            hashcode = hashing.hash_value(password)

            if hashing.check_value(db_pass, password):
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
    # information provided break integrity constraint:
    """
    1. A member can only have one user account
    2. A user account's ID must be in the database, AKA load member info before register
    """
    ID_error = None
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
                ID_error = 'No ID exists in the database!'
            # avoid second registration on the same ID
            elif User.query.filter_by(ID=ID).first() is not None:
                ID_error = 'This ID is taken. Please use another ID!'
            else:
                hashpass = bytes(hashing.hash_value(password), 'utf8')

                newuser = User(username=username
                               ,password=hashpass
                               ,email=email
                               ,ID=ID)

                db.session.add(newuser)
                db.session.commit()
                flash('You have just registered. Welcome!')
    return render_template('register.html', password_error=password_error, ID_error=ID_error)

@app.route('/password_update', methods=['GET', 'POST'])
@login_required
def password_update():
    error = None
    return render_template('password_update.html', error=error)

@app.route('/logout')
@login_required
def logout():
    session.pop('logged_in', None)
    flash('You were just logged out!')
    return redirect(url_for('welcome'))
