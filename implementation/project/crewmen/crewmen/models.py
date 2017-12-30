from crewmen import db

class User(db.Model):
    __tablename__ = 'users'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class Member(db.Model):
    __tablename__ = 'member'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class Training_plan(db.Model):
    __tablename__ = 'training_plan'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class Who_train(db.Model):
    __tablename__ = 'who_train'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class Training_item(db.Model):
    __tablename__ = 'training_item'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}

class Plan_maker(db.Model):
    __tablename__ = 'plan_maker'
    __table_args__ = {'autoload':True,
                      'autoload_with': db.engine}
