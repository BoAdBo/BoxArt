from crewmen import *
from sqlalchemy import inspect

# for x in inspect(ItemInPlan).columns:
#     print(x)

#print(TrainingPlan.__table__)
#print(ItemInPlan.__table__)
#print(TrainingPlan.__tablename__)
# for x in inspect(ItemInPlan).relationships:
#     print(x)

for x in inspect(TrainingPlan).relationships:
    print(x)

item=TrainingPlan.query.filter(TrainingPlan.train_at.between('2017-12-28', '2017-12-31')).first().items

TrainingPlan.query.filter(TrainingPlan.train_at.between('2017-12-29 00:00:00', '2017-12-29 23:59:59')).all()

# for x in inspect(TrainingPlan).columns:
#     print(x)

# for x in inspect(TrainingItem).columns:
#     print(x)



#print(contents)
#cur.execute(contents)

