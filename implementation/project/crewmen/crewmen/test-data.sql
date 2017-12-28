-- executed with crew-leader
insert into member(name, ID, training_level) values
('于H', '0', 'old bird'),
('郭D胜', '1', 'old bird'),
('X德昊', '2', 'old bird'),
('S炜焜', '3', 'old bird'),
('胡泽Q', '4', 'old bird');

insert into user(username, password, priority, ID) values
('yuH', sha2('hello', 512), '1', '0'),
('guoD', sha2('hello', 512), '2', '1'),
('Xde', sha2('hello', 512), '2', '2'),
('Swei', sha2('hello', 512), '2', '3'),
('Huze', sha2('hello', 512), '2', '4');

