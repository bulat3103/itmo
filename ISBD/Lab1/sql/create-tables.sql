create table if not exists profession
(
    id		serial primary key,
    name	varchar(50) not null
);

create table if not exists person
(
    id			serial primary key,
    name		varchar(50) not null,
    age			int not null,
    gender      varchar(50) not null
);

create table if not exists science
(
    id			serial primary key,
    name		varchar(50) not null,
    start_time	date not null
);

create table if not exists action
(
    id			serial primary key,
    name		varchar(50) not null
);

create table if not exists life_sphere
(
    id			serial primary key,
    name		varchar(50) not null
);

create table if not exists result
(
    id			serial primary key,
    science_id	int not null
        references science (id),
    action_id	int not null
        references action (id),
    life_sphere_id	int not null
        references life_sphere (id),
    name		varchar(255) not null,
    effect  int not null
);

create table if not exists opinion
(
    person_id 	int
        references person (id),
    science_id 	int
        references science (id),
    name text not null,
    primary key (person_id, science_id)
);

create table if not exists person_profession
(
    person_id 	int
        references person (id),
    profession_id 	int
        references profession (id),
    primary key (person_id, profession_id)
);