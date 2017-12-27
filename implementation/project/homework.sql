-- creating table in debug

create database if not exists crewmen default character set utf8;

use crewmen

drop table if exists user;
--drop table if exists

create table if not exists user
       (username varchar(20) not null,
       password binary(512) not null, -- not prepare collision
       priority tinyint not null,
       primary key(username)
       );

create table if not exists member
       (name varchar(20),
       info varchar(1000),
       train_level unsign tinyint,
       ID unsign int,
       primary key(ID)
       );
