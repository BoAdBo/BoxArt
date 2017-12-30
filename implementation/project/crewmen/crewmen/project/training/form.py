from flask_wtf import FlaskForm, RecaptchaField
from wtforms import BooleanField, StringField, PasswordField, validators, RadioField, SelectField
from wtforms.validators import DataRequired, Length, Email, EqualTo, InputRequired

class UpdateItemForm(FlaskForm):
    item_name = StringField(
        'The name of the item',
        validators=[InputRequired()]
    )
    is_strength = RadioField(
        'Is it strength',
        choices=[('y', 'Yes'), ('n', 'No')],
        validators=[InputRequired()]
    )
    is_test = RadioField(
        'Is it test',
        choices=[('y', 'Yes'), ('n', 'No')],
        validators=[InputRequired()]
    )

