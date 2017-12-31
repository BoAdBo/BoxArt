##############
### import ###
##############

from flask import Flask, redirect, url_for, render_template, session, g, request, flash, Blueprint, abort
from crewmen import app, login_required
from models import *

##############
### config ###
##############

member_blueprint = Blueprint(
    'member', __name__,
    template_folder='templates'
)

@member_blueprint.route('/member_profile')
def member_profile():
    member = User.query.filter_by(username=session['login_username']).first().member
    return render_template('member_profile.html', member=member)

