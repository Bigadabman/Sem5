select * from dba_pdbs;

--------------------------------------------------------------

select * from v$instance;

--------------------------------------------------------------

select *  from dba_registry;

--------------------------------------------------------------

create pluggable database KEO_PDB 
    ADMIN USER root identified by 1111  
    roles=(CONNECT)
    CREATE_FILE_DEST='/opt/oracle/oradata/KEO/';
    
    
--------------------------------------------------------------

select * from dba_pdbs;

--------------------------------------------------------------

drop tablespace ts_KEO including contents and datafiles;

select * from dba_data_files;


create tablespace ts_KEO
datafile 'ts_KEO.dbf'
size 10m
autoextend on next 5m
maxsize 20m;

create temporary tablespace TS_KEO_TEMP
tempfile 'TS_KEO_TEMP.dbf'
size 5m
autoextend on next 3m
maxsize 30m;

alter tablespace TS_KEO_TEMP
drop datafile '/opt/oracle/oradata/KEO/TS_KEO_TEMP.dbf';
SELECT name, bytes FROM v$tempfile;



create profile PF_KEOCORE limit
PASSWORD_LIFE_TIME 180
SESSIONS_PER_USER 3
FAILED_LOGIN_ATTEMPTS 7
PASSWORD_LOCK_TIME 1
PASSWORD_REUSE_TIME 10
password_grace_time default
connect_time 180
idle_time 30;

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
    
    
    create user U1_KEO_PDB identified by 12345
    default tablespace ts_KEO quota unlimited on ts_KEO
    temporary tablespace TS_KEO_TEMP
    account unlock
    password expire;
    
-----------------------------------------------------------

create table KEO_table
(
username varchar2(20),
balance int
);


insert into keo_table 
values ('Петя', 1000);
insert into keo_table
values ('Коля', 200);
insert into keo_table
values ('Ваня', 400);

commit;

select * from keo_table;


-----------------------------------------------------------

select * from dba_tablespaces;
select file_name, tablespace_name from dba_data_files
union 
select file_name, tablespace_name from dba_temp_files;

select * from dba_roles;
select * from dba_role_privs;

select * from dba_profiles;


select USERNAME, GRANTED_ROLE from dba_users left outer join dba_role_privs on USERNAME=GRANTEE;


-----------------------------------------------------------


create user c##KEO identified by 1111;

grant create session to c##KEO;

grant SYSDBA to c##KEO;


-----------------------------------------------------------

alter pluggable DATABASE KEO_PDB close;
drop pluggable database KEO_PDB including datafiles; 

select file_name, tablespace_name from dba_data_files
union 
select file_name, tablespace_name from dba_temp_files;
