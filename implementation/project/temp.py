# coding: utf-8
from sqlalchemy import BINARY, Column, Date, DateTime, ForeignKey, Integer, Numeric, SmallInteger, String, Table, Time, text
from sqlalchemy.dialects.mysql.enumerated import ENUM
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base


Base = declarative_base()
metadata = Base.metadata


class FeeLog(Base):
    __tablename__ = 'fee_log'

    cost = Column(Numeric(13, 2))
    used_at = Column(DateTime)
    cause = Column(String(200))
    fee_ID = Column(Integer, primary_key=True)


t_log_in_plan = Table(
    'log_in_plan', metadata,
    Column('plan_ID', ForeignKey('training_plan.plan_ID'), primary_key=True, nullable=False),
    Column('record_ID', ForeignKey('training_record.record_ID'), primary_key=True, nullable=False, index=True)
)


class Member(Base):
    __tablename__ = 'member'

    name = Column(String(20), nullable=False)
    sex = Column(ENUM('?', '?'), server_default=text("'?'"))
    enter_club = Column(Date)
    enter_school = Column(Date)
    birth = Column(Date)
    height = Column(SmallInteger)
    weight = Column(SmallInteger)
    ID = Column(Integer, primary_key=True)
    job = Column(ENUM('couch', 'crew leader', 'crew member'), server_default=text("'crew member'"))
    training_level = Column(ENUM('newbie', 'medium', 'old bird'), server_default=text("'newbie'"))

    training_record = relationship('TrainingRecord', secondary='who_train')
    fee_log = relationship('FeeLog', secondary='paid_by')
    training_plan = relationship('TrainingPlan', secondary='plan_maker')
    schedule = relationship('Schedule', secondary='schedule_maker')


t_paid_by = Table(
    'paid_by', metadata,
    Column('ID', ForeignKey('member.ID', ondelete='CASCADE'), primary_key=True, nullable=False),
    Column('fee_ID', ForeignKey('fee_log.fee_ID'), primary_key=True, nullable=False, index=True)
)


t_plan_maker = Table(
    'plan_maker', metadata,
    Column('ID', ForeignKey('member.ID', ondelete='CASCADE'), primary_key=True, nullable=False),
    Column('plan_ID', ForeignKey('training_plan.plan_ID'), primary_key=True, nullable=False, index=True)
)


class Schedule(Base):
    __tablename__ = 'schedule'

    add_time = Column(DateTime, server_default=text("CURRENT_TIMESTAMP"))
    happen_at = Column(DateTime)
    event_ID = Column(Integer, primary_key=True)
    event = Column(String(100), nullable=False)
    spec = Column(String(1000))
    length = Column(Time)


t_schedule_maker = Table(
    'schedule_maker', metadata,
    Column('event_ID', ForeignKey('schedule.event_ID'), primary_key=True, nullable=False),
    Column('ID', ForeignKey('member.ID', ondelete='CASCADE'), primary_key=True, nullable=False, index=True)
)


class Ship(Base):
    __tablename__ = 'ship'

    ship_name = Column(String(100), primary_key=True)
    ship_type_ID = Column(ForeignKey('ship_type_table.ship_type_ID'), index=True)
    condition_description = Column(String(1000))

    ship_type_table = relationship('ShipTypeTable')


class ShipTypeTable(Base):
    __tablename__ = 'ship_type_table'

    ship_type_ID = Column(Integer, primary_key=True)
    ship_type_name = Column(String(100))


t_test = Table(
    'test', metadata,
    Column('c', Integer)
)


class TrainingItem(Base):
    __tablename__ = 'training_item'

    item_name = Column(String(100))
    item_ID = Column(SmallInteger, primary_key=True)
    is_strength = Column(ENUM('y', 'n'))
    is_test = Column(ENUM('y', 'n'))


class TrainingPlan(Base):
    __tablename__ = 'training_plan'

    plan_ID = Column(Integer, primary_key=True)
    train_at = Column(DateTime)
    item_ID = Column(ForeignKey('training_item.item_ID'), index=True)
    distance = Column(Integer)
    time_cost = Column(Time)
    count = Column(SmallInteger)
    item_weight = Column(SmallInteger)
    required_time = Column(SmallInteger)
    time_length = Column(Time)
    training_level = Column(ENUM('newbie', 'medium', 'old bird'))

    training_item = relationship('TrainingItem')
    training_record = relationship('TrainingRecord', secondary='log_in_plan')


class TrainingRecord(Base):
    __tablename__ = 'training_record'

    record_ID = Column(Integer, primary_key=True)
    train_at = Column(DateTime)
    item_ID = Column(ForeignKey('training_item.item_ID'), index=True)
    distance = Column(Integer)
    time_cost = Column(Time)
    count = Column(SmallInteger)
    item_weight = Column(SmallInteger)
    ID = Column(Integer)

    training_item = relationship('TrainingItem')


class User(Base):
    __tablename__ = 'users'

    username = Column(String(20), primary_key=True)
    password = Column(BINARY(128), nullable=False)
    priority = Column(ENUM('couch', 'crew leader', 'crew member'), server_default=text("'crew member'"))
    ID = Column(ForeignKey('member.ID', ondelete='CASCADE'), index=True)

    member = relationship('Member')


t_who_train = Table(
    'who_train', metadata,
    Column('record_ID', ForeignKey('training_record.record_ID'), primary_key=True, nullable=False),
    Column('ID', ForeignKey('member.ID', ondelete='CASCADE'), primary_key=True, nullable=False, index=True)
)
