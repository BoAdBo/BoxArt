from flask_wtf import FlaskForm, RecaptchaField
from wtforms import BooleanField, StringField, PasswordField, validators, RadioField, SelectField, DecimalField, DateTimeField
from wtforms_components import DateRange
from wtforms.validators import DataRequired, Length, Email, EqualTo, InputRequired, NumberRange

class AddFeeForm(FlaskForm):
    cost = DecimalField(
        'Cost',
        places=2,
        rounding=2,
        validators=[InputRequired(), NumberRange(min=0, message='cost can\'t be negative')]
    )

    used_at = DateTimeField(
        'Date',
        format='%Y-%m-%d %H:%M:%S',
        validators=[DateRange(min=None, max=None)]
    )

    cause = StringField(
        'Why',
        validators=[(InputRequired())]
    )
