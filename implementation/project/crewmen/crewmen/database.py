#from flask import Flask
# from sqlalchemy import create_engine
# from sqlalchemy.ext.declarative import declarative_base
# from sqlalchemy.orm import sessionmaker

# Session = sessionmaker()
# Base = declarative_base()
# Session.configure(bind=engine)

# session = Session()

# from sqlalchemy import Column, Integer, String
# class User(Base):
#     __tablename__ = 'users'

#     id = Column(Integer, primary_key=True)
#     name = Column(String(50))
#     fullname = Column(String(50))
#     password = Column(String(50))

#     def __repr__(self):
#         return "<User(name '%s'), fullname='%s>', password='%s'" % (
#             self.name, self.fullname, self.password)


# ed_user = User(name='ed', fullname='Ed Jones', password='edspassword')

"""This is for later progress, since database and SQL statement is what
   I am going to learn, so using a ORM is not good for the final assignment"""

# This class is going to take care of database connections
from crewmen import db

class User(db.Model):
    __tablename__ = ""
