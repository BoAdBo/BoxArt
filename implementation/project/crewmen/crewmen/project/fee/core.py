##############
### import ###
##############

from flask import Flask, redirect, url_for, render_template, session, g, request, flash, Blueprint, abort
from crewmen import app, login_required
from models import *
from .form import AddFeeForm

##############
### config ###
##############

fee_blueprint = Blueprint(
    'fee', __name__,
    template_folder='templates'
)

@fee_blueprint.route('/show_fee_log')
def show_fee_log():
    logs = FeeLog.query.all()
    return render_template('show_fee_log.html', logs=logs)

@fee_blueprint.route('/add_fee_log', methods=['GET', 'POST'])
def add_fee_log():
    """csrf_token must be placed under under form"""
    form = AddFeeForm()
    forms = [form.cost, form.used_at, form.cause]


    if form.validate_on_submit():
        member = User.query.filter_by(username=session['login_username']).first().member
        print(form.cost.data)
        print(form.used_at.data)
        print(form.cause.data)
        print(member.name)

        fee = FeeLog(cost=form.cost.data,
                     used_at=form.used_at.data,
                     cause=form.cause.data,
                     member=member)
        print(fee)



        return render_template('add_fee_log.html', forms=forms, csrf_token=form.csrf_token)
    return render_template('add_fee_log.html', forms=forms, csrf_token=form.csrf_token)
