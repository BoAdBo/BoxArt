-- executed with crew-leader
insert into member(name, ID, training_level) values
('于H', '0', 'old bird'),
('郭D胜', '1', 'old bird'),
('X德昊', '2', 'old bird'),
('S炜焜', '3', 'old bird'),
('胡泽Q', '4', 'old bird'),
('happygirlzt', '520', 'old bird');

insert into users(username, password, ID, email) values
('yuH', sha2('hello', 512), '0', '123@happygirlzt.com'),
('guoD', sha2('hello', 512), '1', '124@happygirlzt.com'),
('Xde', sha2('hello', 512), '2', '125@happygirlzt.com'),
('Swei', sha2('hello', 512), '3', '126@happygirlzt.com'),
('Huze', sha2('hello', 512), '4', '128@happygirlzt.com');

insert into training_item(item_name, is_strength, is_test) values
('卧拉', 'y', 'n'),
('平板支撑','y', 'n'),
('仰卧两头起', 'y', 'n'),
('深蹲', 'y', 'n');

insert into training_plan(train_at, training_last) values
('2017-12-29 12:00:00', 30),
('2017-12-30 00:00:00', 30);

insert into item_in_plan(plan_ID, item_ID) values
('1', '1'),
('1', '2'),
('1', '3'),
('2', '1');
