create table SC
(Sno char(9),
Cno char(4),
Grade smallint,
primary key(Sno,Cno),
foreign key(Sno)references Student(Sno),
foreign key(Cno)references Course(Cno)
);