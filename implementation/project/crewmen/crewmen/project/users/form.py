from flask_wtf import FlaskForm, RecaptchaField
from wtforms import BooleanField, StringField, PasswordField, validators
from wtforms.validators import DataRequired, Length, Email, EqualTo


class UpdatePasswordForm(FlaskForm):
    old_password = PasswordField(
        'old password',
        validators=[DataRequired(), Length(min=5, max=25)]
    )
    new_password = PasswordField(
        'new password',
        validators=[DataRequired(), Length(min=5, max=25)]
    )
    sec_new_password = PasswordField(
        'Double Check',
        validators=[DataRequired(), EqualTo('new_password', message='Passwords must match.')]
    )

