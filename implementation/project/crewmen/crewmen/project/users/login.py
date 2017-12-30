##############
### import ###
##############
from flask import Flask, redirect, url_for, render_template, session, g, request, flash, Blueprint, abort
from flask_hashing import Hashing
from crewmen import app
from crewmen import login_required
from models import User
from flask_bcrypt import Bcrypt

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
            #print(db_pass)
            #hashcode = bytes(hashing.hash_value(password), 'utf8')
            hashcode = hashing.hash_value(password)
            #print(hashcode)
            # if db_pass == hashcode:
            #     session['logged_in'] = True
            #     return redirect(url_for('home'))
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

@app.route('/register', methods=['GET', 'POppST'])
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
