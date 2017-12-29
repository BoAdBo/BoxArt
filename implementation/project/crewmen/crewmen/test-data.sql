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

insert into training_item(item_name, item_ID, is_strength, is_test) values
('卧拉', '1', 'y', 'n'),
('平板支撑', '2', 'y', 'n');

insert into training_plan(train_at, item_ID) values
('2017-12-29 12:00:00', 1);
