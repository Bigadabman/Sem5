--1-----------------------------------------------------------------------
select file_name, tablespace_name from dba_data_files
union
select file_name, tablespace_name from dba_temp_files;


--2------------------------------------------------------------------------

create pluggable database KEO_PDB
ADMIN USER root identified by 1111
roles=(connect)
CREATE_FILE_DEST='/opt/oracle/oradata/KEO';


alter pluggable database KEO_PDB open;

create tablespace KEO_QDATA
datafile 'KEO_QDATA.dbf'
size 10m
autoextend on next 1m
maxsize 20m
offline;


alter tablespace KEO_QDATA online;


drop user KEO;

create user KEO identified by 1234
default tablespace KEO_QDATA quota 2m on KEO_QDATA
account unlock;


grant create session,
        create table,
        drop any table
        to KEO;
        
        
create table KEO_T1 
( name varchar2(20) primary key,
balance int check(balance >=0) not null
) tablespace KEO_QDATA;        

        
insert into KEO_T1 values ('Петя', 100);
insert into KEO_T1 values ('Коля', 200);
insert into KEO_T1 values ('Валодя', 1);

select * from KEO_T1;
        
        
--3--------------------------------------------------------------------------

select * from dba_segments where TABLESPACE_NAME='KEO_QDATA';
select * from dba_segments;
        
        
--4--------------------------------------------------------------------------

drop table KEO_T1;

select * from dba_segments where TABLESPACE_NAME='KEO_QDATA';

Select * from user_recyclebin;

        
--5--------------------------------------------------------------------------

flashback table KEO_T1 to before drop;
select * from dba_segments where TABLESPACE_NAME='KEO_QDATA';

--6--------------------------------------------------------------------------

declare i number := 1;

begin 
    while i<10001 loop
        
        insert into KEO_T1 values (concat('user',TO_CHAR(i)),i);
    i:=i+1;
    end loop;
end;

select * from KEO_T1;

--7--------------------------------------------------------------------------


select segment_name, extents, blocks, bytes from dba_segments
where SEGMENT_NAME like '%KEO%';
select * from dba_extents;

--8--------------------------------------------------------------------------


alter tablespace KEO_QDATA offline; 
drop tablespace KEO_QDATA including contents and datafiles;

--9--------------------------------------------------------------------------

select * from v$log;

--10-------------------------------------------------------------------------
select * from  v$logfile;

--11-------------------------------------------------------------------------


alter system switch LOGFILE;

select * from v$log;

--12-------------------------------------------------------------------------

alter database add logfile group 3 'REDO03.LOG'
size 50m blocksize 512;

alter database add logfile member 'REDO031.LOG' to group 3;
alter database add logfile member 'REDO032.LOG' to group 3;


select * from v$log;


alter system switch logfile;

--13---------------------------------------------------------------------------

alter database drop logfile member 'REDO031.LOG';
alter database drop logfile member 'REDO032.LOG';

alter database drop logfile group 3;


select * from v$logfile;
select * from v$log;


--14---------------------------------------------------------------------------

select NAME, log_mode from v$database;
select instance_name, archiver, active_state from v$instance;

--15---------------------------------------------------------------------------


select * from v$archived_log 
where sequence# = (select max(sequence#) from v$archived_log);

--16--------------------------------------------------------------------------

--Включение архивации

-- connect /as sysdba;
-- shutdown immediate;
-- startup mount;
-- alter database archivelog;
-- alter database open;


select NAME, log_mode from v$database;
select instance_name, archiver, active_state from v$instance;

--17------------------------------------------------------------------------

select * from v$log;

alter system switch logfile;

select * from v$archived_log;

--18-----------------------------------------------------------------------

-- connect /as sysdba;
-- shutdown immediate;
-- startup mount;
-- alter database noarchivelog;
-- alter database open;


select NAME, log_mode from v$database;
select instance_name, archiver, active_state from v$instance;


--19------------------------------------------------------------------------

select * from v$controlfile;

--ALTER DATABASE BACKUP CONTROLFILE TO TRACE;
--
--SELECT value FROM v$diag_info WHERE name = 'Default Trace File';

------cat diag/rdbms/free/FREE/trace/FREE_ora_1286.trc

--20--------------------------------------------------------------------------

ALTER DATABASE BACKUP CONTROLFILE TO TRACE;

SELECT value FROM v$diag_info WHERE name = 'Default Trace File';

--21--------------------------------------------------------------------------

show parameter pfile;
select * from v$parameter where name = 'spfile';
 
--22-------------------------------------------------------------------------


create pfile = 'KEO_PFILE.ora' from spfile;
----- cat product/23ai/dbhomeFree/dbs/KEO_PFILE.ora


--23-------------------------------------------------------------------------

select * from v$pwfile_users;
SHOW PARAMETER remote_login_passwordfile;
-----  product/23ai/dbhomeFree/dbs/orapwFREE

--24-------------------------------------------------------------------------

select * from v$diag_info;

-----------------------------------------------------------------------------

------ cat diag/rdbms/free/FREE/alert/log.xml
------ cd product/23ai/dbhomeFree/dbs 


-- rm product/23ai/dbhomeFree/dbs/REDO031.LOG
-- rm product/23ai/dbhomeFree/dbs/REDO032.LOG
-- rm product/23ai/dbhomeFree/dbs/REDO03.LOG
-- rm product/23ai/dbhomeFree/dbs/archx


