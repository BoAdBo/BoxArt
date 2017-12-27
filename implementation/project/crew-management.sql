-- with debug if and if not

create database crewmen character set utf8 collate utf8_general_ci;
use crewmen

drop table if exists user;
drop table if exists member;
drop table if exists schedule;
drop table if exists user;
drop table if exists schedule_maker;
drop table if exists fee_log;
drop table if exists paid_by;
drop table if exists training_item;
drop table if exists training_record;
drop table if exists who_train;
drop table if exists training_plan;
drop table if exists log_in_plan;
drop table if exists plan_maker;
drop table if exists ship_type_table;
drop table if exists ship;


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
       training_level enum('newbie', 'medium', 'old bird') default 'newbie',
       primary key(ID)
       );-- character set utf8 collate utf8_general_ci;

create table if not exists user
       (username varchar(20) not null,
       password binary(128) not null, -- half byte each, so 128 * 0.5 * 8 is 512 using sha2('pass', 512)
       priority tinyint unsigned not null, -- the lower the better
       ID int unsigned,
       primary key(username),
       foreign key(ID) references member(ID)
       );

-- how to enforce constraint on full participation, every schedule should have at least a maker...
create table if not exists schedule
       (add_time datetime default current_timestamp,
       happen_at datetime, -- time could be unsure of
       event_ID int unsigned auto_increment,
       event varchar(100) not null,
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
       item_ID smallint unsigned,
       is_strength enum('y', 'n'), -- strength or aerobic
       is_test enum('y', 'n'),     -- test or regular
       primary key(item_ID)
       );

create table if not exists training_record
       (record_ID int unsigned auto_increment,
       train_at datetime,
       item_ID smallint unsigned,
       -- big chunk of record fields some might be null for some item
       distance int unsigned,
       time_cost time,
       count smallint unsigned,
       item_weight smallint unsigned,
       -- big chunk of record fields
       ID int unsigned,
       primary key(record_ID),
       foreign key(item_ID) references training_item(item_ID)
       );

create table if not exists who_train
       (record_ID int unsigned,
       ID int unsigned,
       primary key(record_ID, ID),
       foreign key(record_ID) references training_record(record_ID),
       foreign key(ID) references member(ID)
       );

create table if not exists training_plan
       (
       plan_ID int unsigned auto_increment,
       train_at datetime,
       item_ID smallint unsigned,
       -- the same chunk of record fields, as requirement
       distance int unsigned,
       time_cost time,
       count smallint unsigned,
       item_weight smallint unsigned,
       required_time smallint unsigned, -- 组数
       -- the same chunk of record fields, as requirement
       time_length time,
       training_level enum('newbie', 'medium', 'old bird'),
       primary key(plan_ID),
       foreign key(item_ID) references training_item(item_ID)
       );

create table if not exists log_in_plan
       (plan_ID int unsigned,
       record_ID int unsigned,
       primary key(plan_ID, record_ID),
       foreign key(plan_ID) references training_plan(plan_ID),
       foreign key(record_ID) references training_record(record_ID)
       );

create table if not exists plan_maker
       (ID int unsigned,
       plan_ID int unsigned,
       primary key(ID, plan_ID),
       foreign key(ID) references member(ID),
       foreign key(plan_ID) references member(plan_ID)
       );

create table if not exists ship_type_table
       (ship_type_ID tinyint unsigned,
       ship_type_name varchar(100),
       primary key(ship_type_ID)
       );

create table if not exists ship
       (ship_name varchar(100),
       ship_type_ID tinyint unsigned,
       condition_description varchar(1000),
       primary key(ship_name),
       foreign key(ship_type_ID) references ship_type_table(ship_type_ID)
       );
