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
from .form import UpdatePasswordForm

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
    """
    If the user doesn't exist, return error accordingly, if the user exists, with wrong password, return error
    if successfully logged in, query db for ID and priority, store in session
    """
    error = None
    try:
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']

            login_user = User.query.filter_by(username=username).first()

            db_hash = login_user.password.decode("utf8")

            hashcode = hashing.hash_value(password)

            if hashing.check_value(db_hash, password):
                session['logged_in'] = True
                session['login_job'] = login_user.member.job
                session['login_username'] = login_user.username
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
    form = UpdatePasswordForm()

    """ https://stackoverflow.com/questions/43002323/difference-between-form-validate-on-submit-and-form-validate"""
    """https://stackoverflow.com/questions/10722968/flask-wtf-validate-on-submit-is-never-executed"""
    """
    valid needs CSRF
    is_sumbit check 'POST'
    """

    if form.validate_on_submit():
        current_user = User.query.filter_by(username = session['login_username']).first_or_404()
        db_hash = current_user.password.decode("utf8")
        if hashing.check_value(db_hash, form.old_password.data):
            current_user.password = bytes(hashing.hash_value(form.new_password.data), 'utf8')
            db.session.commit()
            flash("you have successfully changed your password!")
            return redirect(url_for('welcome'))

    return render_template('password_update.html', error=error, form=form)

@app.route('/logout')
@login_required
def logout():
    session.pop('login_job', None)
    session.pop('login_username', None)
    session.pop('logged_in', None)
    flash('You were just logged out!')
    return redirect(url_for('welcome'))
