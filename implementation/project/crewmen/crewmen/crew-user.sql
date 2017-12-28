-- operate with root
drop user 'crew-root'@'localhost';
drop user 'crew-leader'@'localhost';
drop user 'crew-member'@'localhost';
drop user 'crew-login'@'localhost';

create user 'crew-root'@'localhost' identified by 'crew-root';
create user 'crew-leader'@'localhost' identified by 'crew-leader';
create user 'crew-member'@'localhost' identified by 'crew-member';
create user 'crew-login'@'localhost' identified by 'crew-login';


grant all on crewmen.* to 'crew-root'@'localhost';

insert into mysql.tables_priv(Host, Db, User, Table_name, Grantor, Table_priv)
values('localhost', 'crewmen', 'crew-leader', 'user', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'member', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'schedule', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'schedule_maker', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'fee_log', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'paid_by', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'training_item', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'training_record', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'who_train', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'training_plan', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'log_in_plan', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'plan_maker', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'ship_type_table', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-leader', 'ship', CURRENT_USER, 'select,update,delete,insert');

-- the capital letter 'Select' or 'select' is both fine

insert into mysql.tables_priv(Host, Db, User, Table_name, Grantor, Table_priv)
values('localhost', 'crewmen', 'crew-member', 'user', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-member', 'member', CURRENT_USER, 'select,update'),
('localhost', 'crewmen', 'crew-member', 'schedule', CURRENT_USER, 'select'),
('localhost', 'crewmen', 'crew-member', 'schedule_maker', CURRENT_USER, 'select'),
('localhost', 'crewmen', 'crew-member', 'fee_log', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-member', 'paid_by', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-member', 'training_item', CURRENT_USER, 'select'),
('localhost', 'crewmen', 'crew-member', 'training_record', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-member', 'who_train', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-member', 'training_plan', CURRENT_USER, 'select'),
('localhost', 'crewmen', 'crew-member', 'log_in_plan', CURRENT_USER, 'select,update,delete,insert'),
('localhost', 'crewmen', 'crew-member', 'plan_maker', CURRENT_USER, 'select'),
('localhost', 'crewmen', 'crew-member', 'ship_type_table', CURRENT_USER, 'select'),
('localhost', 'crewmen', 'crew-member', 'ship', CURRENT_USER, 'select,update');

flush privileges;

-- debug below
-- show grants for 'crew-root'@'localhost';
-- show grants for 'crew-member'@'localhost';
-- show grants for 'crew-leader'@'localhost';
