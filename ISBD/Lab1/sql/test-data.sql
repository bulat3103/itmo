insert into profession values (DEFAULT, 'journalist');
insert into profession values (DEFAULT, 'operator');
insert into profession values (DEFAULT, 'coder');
insert into profession values (DEFAULT, 'doctor');
insert into profession values (DEFAULT, 'cooker');
insert into profession values (DEFAULT, 'blogger');

insert into person values (DEFAULT, 'Vasya Pupkin', 33, 'MALE');
insert into person values (DEFAULT, 'Anna Anina', 25, 'FEMALE');
insert into person values (DEFAULT, 'Masha Mashina', 23, 'FEMALE');

insert into science values (DEFAULT, 'Biotechnology', '1917-01-08');
insert into science values (DEFAULT, 'Computers', '1927-01-08');
insert into science values (DEFAULT, 'Nuclear Power', '1954-07-26');

insert into life_sphere values (DEFAULT, 'food');
insert into life_sphere values (DEFAULT, 'medicine');
insert into life_sphere values (DEFAULT, 'health');
insert into life_sphere values (DEFAULT, 'entertainments');
insert into life_sphere values (DEFAULT, 'body');
insert into life_sphere values (DEFAULT, 'history');

insert into action values (DEFAULT, 'изменить');
insert into action values (DEFAULT, 'провести революцию');

insert into result values (DEFAULT, (SELECT id from science where name='Biotechnology'), (SELECT id from action where name='провести революцию'), (SELECT id from life_sphere where name='history'), 'решены проблемы с голоданием', 98);
insert into result values (DEFAULT, (SELECT id from science where name='Biotechnology'), (SELECT id from action where name='изменить'), (SELECT id from life_sphere where name='food'), 'стали выращивать больше пищи с разными полезными ферментами', 88);
insert into result values (DEFAULT, (SELECT id from science where name='Nuclear Power'), (SELECT id from action where name='изменить'), (SELECT id from life_sphere where name='health'), 'стало много вредных выбросов в атмосферу', 92);
insert into result values (DEFAULT, (SELECT id from science where name='Computers'), (SELECT id from action where name='изменить'), (SELECT id from life_sphere where name='entertainments'), 'появились компьютерные игры', 95);
insert into result values (DEFAULT, (SELECT id from science where name='Computers'), (SELECT id from action where name='изменить'), (SELECT id from life_sphere where name='health'), 'появились медики-роботы', 97);

insert into person_profession values ((SELECT id from person where name='Vasya Pupkin'), (SELECT id from profession where name='journalist'));
insert into person_profession values ((SELECT id from person where name='Anna Anina'), (SELECT id from profession where name='operator'));
insert into person_profession values ((SELECT id from person where name='Masha Mashina'), (SELECT id from profession where name='operator'));
insert into person_profession values ((SELECT id from person where name='Masha Mashina'), (SELECT id from profession where name='cooker'));
insert into person_profession values ((SELECT id from person where name='Masha Mashina'), (SELECT id from profession where name='blogger'));
insert into person_profession values ((SELECT id from person where name='Masha Mashina'), (SELECT id from profession where name='doctor'));
insert into person_profession values ((SELECT id from person where name='Masha Mashina'), (SELECT id from profession where name='coder'));

insert into opinion values ((SELECT id from person where name='Vasya Pupkin'), (SELECT id from science where name='Biotechnology'), 'Биотех АУФ!!!');
insert into opinion values ((SELECT id from person where name='Masha Mashina'), (SELECT id from science where name='Computers'), 'Го дотку!!!');
insert into opinion values ((SELECT id from person where name='Anna Anina'), (SELECT id from science where name='Computers'), 'Компьютер зло!!!');
insert into opinion values ((SELECT id from person where name='Anna Anina'), (SELECT id from science where name='Nuclear Power'), 'Хватит вредить природе!!!');