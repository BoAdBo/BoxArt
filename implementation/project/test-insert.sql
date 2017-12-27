use crewmen



insert into member (name, ID) values ('杨麒平', '150000');
insert into member (name, ID) values ('张婷', '140520');

insert into user (username, password, priority, ID) values ('newjoy7', sha2('pass the exam', 512), '1', '150000');

insert into schedule (happen_at, event) values ('2020-12-01 00:00:00', '寒假特训');
insert into schedule_maker (event_ID, ID) values ('1', '150000');
