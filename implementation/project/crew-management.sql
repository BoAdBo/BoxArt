-- with debug if and if not

create database crewmen character set utf8 collate utf8_general_ci;
use crewmen

drop table if exists user;
drop table if exists member;
drop table if exists schedule;
drop table if exists user;
drop table if exists schedule_maker;
drop table if exists paid_by;
drop table if exists fee_log;
drop table if exists training_record;
drop table if exists training_plan;

create table if not exists member
       (name varchar(20) not null,
       -- big chunk for information
       sex enum('男', '女') default '男',
       enter_club date, -- the crew
       enter_school date, -- school
       birth date,
       height smallint unsigned,
       weight smallint unsigned,
       ID int unsigned,
       -- big chunk for information
       job enum('couch', 'crew leader', 'crew member'),
       training_level enum('newbie', 'medium', 'old bird'),
       primary key(ID)
       );-- character set utf8 collate utf8_general_ci;

create table if not exists user
       (username varchar(20) not null,
       password binary(128) not null, -- half byte each, so 128 * 0.5 * 8 is 512 using sha2('pass', 512)
       priority tinyint unsigned not null,
       ID int unsigned,
       primary key(username),
       foreign key(ID) references member(ID)
       );

-- how to enforce constraint on full participation, every schedule should have at least a maker...
create table if not exists schedule
       (happen_at datetime,
       event_ID int unsigned,
       event varchar(100),
       spec varchar(1000),
       length time,
       primary key(event_ID)
       );

create table if not exists schedule_maker
       (event_ID int unsigned,
       ID int unsigned,
       primary key(event_ID, ID),
       foreign key(event_ID) references schedule(event_ID),
       foreign key(ID) references member(ID)
       );


-- same question as schedule, every fee should have a payer
create table if not exists fee_log
       (cost decimal(13,2), -- cost could range from cent to 10^13 which is 10^4 billion yuan, should be enough
        used_at datetime,
        cause varchar(200),
        fee_ID int unsigned,
        primary key(fee_ID)
       );

create table if not exists paid_by
       (ID int unsigned,
       fee_ID int unsigned,
       primary key(ID, fee_ID),
       foreign key(ID) references member(ID),
       foreign key(fee_ID) references fee_log(fee_ID)
       );

-- may need to define training item
create table if not exists training_item
       (item_name varchar(100),
       is_less_better enum('y', 'n') not null default 'y', -- running or push-ups
       item_ID smallint unsigned,
       primary key(item_ID)
       );



create table if not exists training_record
       (train_at datetime,
       item_ID smallint unsigned,
       record decimal(10, 2),
       ID int unsigned,
       primary key(train_at, i)
       );

create table if not exists training_plan
       (
       );
