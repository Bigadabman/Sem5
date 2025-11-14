
-- Использовался старый юзер и PDB

ALTER PLUGGABLE DATABASE KEO_PDB OPEN;


--1----------------------------------------------------------------



grant create session to keo;
grant create any table to keo;
grant drop any table to keo;
grant create cluster to keo;
grant create synonym to keo; 
grant create public SYNONYM to keo; 
grant create view to keo;
grant create materialized view to keo;
grant create SEQUENCE 
to keo;


select * from dba_sys_privs where grantee = 'KEO';

--2-----------------------------------------------------------------

create sequence S1 start with 1000 increment by 10
nominvalue nomaxvalue
nocycle nocache noorder;

select S1.nextval from dual;
select S1.nextval from dual;

select S1.currval from dual;


--3------------------------------------------------------------------


create sequence S2 start with 10 
increment by 10
maxvalue 100
nocycle;


select S2.nextval from dual;

--5-------------------------------------------------------------------

create sequence S3 start with 10
increment by -10
minvalue -100
maxvalue 100
nocycle
order;


select S3.nextval from dual;


--6-------------------------------------------------------------------

create sequence S4 start with 1
increment by 1
maxvalue 10
cycle
cache 5
noorder;

select S4.nextval from dual;

--7-------------------------------------------------------------------

select * from user_sequences;

--8------------------------------------------------------------------

create table T1(
N1 number(20),
N2 number(20),
N3 number(20),
N4 number(20)
) cache storage (buffer_pool KEEP );


insert into T1 values(S1.nextval, S2.nextval, S3.nextval, S4.nextval);

select * from T1;

--9-------------------------------------------------------------------


create cluster ABC(
X number(10),
V varchar(12)
) hashkeys 200;


--10-----------------------------------------------------------------

create table A(
XA number(10),
VA varchar(12),
YA number(10)
) cluster ABC(XA,VA);

--11----------------------------------------------------------------

create table B(
XB number(10),
VB varchar(12),
YB number(10)
) cluster ABC(XB, VB);

insert into B values(1, '1', 1);

--12----------------------------------------------------------------

create table C(
XC number(10),
VC varchar(12),
YC number(10)
) cluster ABC(XC, VC);

insert into C values(1, '1', 1);

--13----------------------------------------------------------------

select * from user_clusters;
select * from user_tables;

--14----------------------------------------------------------------

create synonym SC for KEO.C;

select * from SC;

--15----------------------------------------------------------------

create public synonym SB for KEO.B;

select * from SB;

--16----------------------------------------------------------------

create table A4(
XA number(10) primary key,
VA varchar(12),
YA number(10)
);


create table B4(
XB number(10) ,
VB varchar(12),
YB number(10),
constraint fk_b4 foreign key (XB) references A4(XA)
);

insert into A4 values(1,'1',1);
insert into A4 values(2,'2',2);
insert into A4 values(3,'3',3);
insert into A4 values(4,'4',4);

insert into B4 values(1,'1',1);
insert into B4 values(4,'4',4);


create view V1 as
Select * from A4 inner join B4 on XA=XB;


select * from V1;

--17-----------------------------------------------------------------

create materialized view MV
refresh force on demand
next sysdate + 2/1440
as 
Select * from A4 inner join B4 on XA=XB;


select * from MV;



