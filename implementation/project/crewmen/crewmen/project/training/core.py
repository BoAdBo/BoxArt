from flask import Flask, redirect, url_for, render_template, session, g, request, flash, Blueprint, abort
from crewmen import app, login_required, wraps
import datetime
from models import *
from flask_nav import Nav
from flask_nav.elements import *
from .form import UpdateItemForm
##################
### Navbar init###
##################

training_blueprint = Blueprint(
    'training', __name__,
    template_folder='templates'
)

########################
### helper function ####
########################

def power_required(f):
    @wraps(f)
    def wrap(*arg, **kwargs):
        job = session['login_job']
        if job == 'crew leader' or job == 'couch':
            return f(*arg, **kwargs)
        else:
            flash('You have no power.')
            return redirect(url_for('home'))
    return wrap

########################
########################
########################



@training_blueprint.route('/show_item')
@login_required
def show_item():
    items = TrainingItem.query.all()
    return render_template('show_item.html', items=items)

@training_blueprint.route('/add_plan')
@login_required
@power_required
def add_plan():
    error = None
    return render_template('add_plan.html', power=True)

@training_blueprint.route('/add_item', methods=['GET', 'POST'])
@login_required
@power_required
def add_item():
    form = UpdateItemForm()
    forms = [form.item_name, form.is_strength, form.is_test]

    if form.validate_on_submit():
        item = TrainingItem(item_name=form.item_name.data,
                            is_strength=form.is_strength.data,
                            is_test=form.is_test.data)

        db.session.add(item)
        db.session.commit()
        flash("You have added an item.")
        return render_template('add_item.html', forms=forms, form=form)

    return render_template('add_item.html', forms=forms, form=form)

@training_blueprint.route('/training_plan')
@login_required
def show_training_plan():
    today = datetime.date.today()
    nextday = today + datetime.timedelta(days=1)
    today_plan = TrainingPlan.query.filter(TrainingPlan.train_at >= today, TrainingPlan.train_at < nextday).all()
    #today_plan = TrainingPlan.query.all()
    print(today_plan)
    return render_template('training_plan.html', strength_plan=today_plan)
