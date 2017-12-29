from sqlalchemy import create_engine, MetaData, Table
from sqlalchemy.orm import mapper, sessionmaker
from sqlalchemy.ext.declarative import declarative_base

dbPath = '/home/king-kong/.mozilla/firefox/nope.default/places.sqlite'
engine = create_engine('sqlite:///%s' % dbPath, echo=True)
Base = declarative_base(engine)

class Bookmarks(Base):
    """"""
    __tablename__ = 'moz_bookmarks'
    __table_args__ = {'autoload':True}

def loadSession():
    """"""
    #metadata = MetaData(engine)
    metadata = Base.metadata
    #moz_bookmarks = Table('moz_bookmarks', metadata, autoload=True)
    #mapper(Bookmarks, moz_bookmarks)

    Session = sessionmaker(bind=engine)
    session = Session()
    return session

if __name__ == "__main__":
    session = loadSession()
    res = session.query(Bookmarks).all()
    print(res[1].title)
    for x in res:
        print(x.title)
