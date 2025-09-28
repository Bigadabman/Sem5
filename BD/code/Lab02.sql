create tablespace TS_KEO
datafile 'TS_KEO.dbf'
size 7 m
autoextend on next 5 m
maxsize 20m;

drop tablespace TS_KEO including contents and datafiles;


create temporary tablespace TS_KEO_TEMP1
tempfile 'TS_KEO_TEMP.dbf'
size 5 m 
autoextend on next 3 m 
maxsize 30 m;

drop tablespace TS_KEO_TEMP1 including contents and datafiles;


-----------------------------------------------------------------------------------

select file_name, tablespace_name, status, maxbytes, user_bytes from dba_data_files
union
select file_name, tablespace_name, status, maxbytes, user_bytes from dba_temp_files;


-------------------------------------------------------------------------------------

create role RL_KEOCORE;



grant
        create session,
        create table,
        create view,
        create procedure,
        drop any table,
        drop any view,
        drop any procedure
        to RL_KEOCORE;


-------------------------------------------------------------------------------------

select * from dba_roles where role like '%RL%';

select * from dba_sys_privs where grantee = 'RL_KEOCORE';


-------------------------------------------------------------------------------------

create profile PF_KEOCORE limit
    password_life_time 180
    sessions_per_user 3
    failed_login_attempts 7
    password_lock_time 1
    password_reuse_time 10
    password_grace_time default
    connect_time 180
    idle_time 30;
    
------------------------------------------------------------------------------------


select * from dba_profiles;

select * from dba_profiles where profile = 'PF_KEOCORE';

select * from dba_profiles where profile = 'DEFAULT';


------------------------------------------------------------------------------------

create user KEOCORE identified by 12345
    default tablespace TS_KEO
    temporary tablespace TS_KEO_TEMP1
    profile PF_KEOCORE
    account unlock
    password expire;
    
    grant RL_KEOCORE to KEOCORE;
    
----------------------------------------------------------------------------------
  
  
create table BANK
(
username varchar2(20),
balance int check(balance >=0) not null
);

create view Rich_Users as
select * from BANK where balance >= 1000;


--------------------------------------------------



create tablespace KEO_QDATA
datafile 'KEO_QDATA.dbf'
size 10m
autoextend on next 5m
maxsize 100m
offline;


alter tablespace KEO_QDATA online;



alter user KEOCORE quota 10M on TS_KEO;




create table SHOP
(
item varchar2(15) primary key,
price float check( price >0) not null
);

drop table SHOP;

insert into SHOP values ('Яблоко', 3.99);
insert into SHOP values ('Тарелка', 10.00);
insert into SHOP values ('Дверь', 200.00);