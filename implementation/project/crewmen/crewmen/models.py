from crewmen import db
from sqlalchemy.orm import relationship
from sqlalchemy import Table, MetaData

meta = MetaData(bind=db.engine)

##############################################
##### Take note of the naming convention ##### no underscore for models' name
##############################################

class User(db.Model):
    __tablename__ = 'users'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

    member = relationship("Member", backref="user")

class Member(db.Model):
    __tablename__ = 'member'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class ItemInPlan(db.Model):
    __tablename__ = 'item_in_plan'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class TrainingPlan(db.Model):
    #__table__ = Table('training_plan', meta, autoload=True)
    __tablename__ = 'training_plan'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

    # cannot pass in the class
    items = relationship("TrainingItem", secondary=ItemInPlan.__table__)

class WhoTrain(db.Model):
    __tablename__ = 'who_train'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class TrainingItem(db.Model):
    __tablename__ = 'training_item'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class PlanMaker(db.Model):
    __tablename__ = 'plan_maker'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}
