create table T_STUDENT_INFO
(
  STU_ID   VARCHAR2(50) not null,
  STU_NAME VARCHAR2(50) not null,
  STU_SEX  VARCHAR2(2) not null,
  STU_AGE  NUMBER(3) not null
);

create table T_USER_INFO
(
  USERNAME VARCHAR2(50) not null,
  PASSWORD VARCHAR2(50) not null
);

insert into T_STUDENT_INFO (STU_ID, STU_NAME, STU_SEX, STU_AGE) values ('5', '555', 'Å®', 23);
insert into T_STUDENT_INFO (STU_ID, STU_NAME, STU_SEX, STU_AGE) values ('3', '333', 'ÄÐ', 21);
insert into T_STUDENT_INFO (STU_ID, STU_NAME, STU_SEX, STU_AGE) values ('4', '444', 'ÄÐ', 24);
insert into T_STUDENT_INFO (STU_ID, STU_NAME, STU_SEX, STU_AGE) values ('2', '222', 'Å®', 28);
insert into T_STUDENT_INFO (STU_ID, STU_NAME, STU_SEX, STU_AGE) values ('1', '111', 'ÄÐ', 26);
commit;

insert into T_USER_INFO (USERNAME, PASSWORD) values ('admin', '1');
commit;