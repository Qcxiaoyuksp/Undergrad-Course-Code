create table Course
(Cno char(4) primary key,
Cname char(40) not null,
Cpno char(4),
Ccredit smallint,
foreign key(Cpno)references Course(Cno)
);