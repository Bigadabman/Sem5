--1----------------------------------------------------------------------------
select sum(value) from v$sga;

--2----------------------------------------------------------------------------
select component, current_size, max_size from v$sga_dynamic_components
where current_size > 0;

--3----------------------------------------------------------------------------
select component, granule_size from v$sga_dynamic_components 
where current_size > 0;

--4----------------------------------------------------------------------------

select current_size from v$sga_dynamic_free_memory;

--5----------------------------------------------------------------------------
show parameter sga;


--6----------------------------------------------------------------------------
select component, current_size, min_size, max_size 
from v$sga_dynamic_components
where component in ('KEEP buffer cache', 'DEFAULT buffer cache', 'RECYCLE buffer cache');

--7----------------------------------------------------------------------------

alter system set db_keep_cache_size = 100m scope=spfile;


create table bank (
userName varchar2(20) primary key, 
balance int check(balance > 0) not null
 )
 storage (buffer_pool keep);


insert into bank
values ('Ваня', 100);
insert into bank 
values ('Петя', 200);


select segment_name, segment_type, tablespace_name, buffer_pool
from user_segments where segment_name = 'BANK';


drop table bank purge;

--8---------------------------------------------------------------------------

create table bank (
userNme varchar2(20) primary key,
balance int check(balance > 0) not null
)
storage (buffer_pool default);

insert into bank
values ('Ваня', 100);
insert into bank 
values ('Петя', 200);


select segment_name, segment_type, tablespace_name, buffer_pool
from user_segments where segment_name = 'BANK';

--9---------------------------------------------------------------------------
show parameter log_buffer;

--10--------------------------------------------------------------------------

select * from  v$sgastat where pool = 'large pool' and name = 'free memory';


--11--------------------------------------------------------------------------

select username, service_name, server 
from v$session
where username is not null;

--12--------------------------------------------------------------------------

select * from v$bgprocess where paddr != hextoraw('00');


--13-------------------------------------------------------------------------

select * from v$process where background is null;

--14-------------------------------------------------------------------------
select count(*) from v$bgprocess where NAME like '%DBW%';

--15-------------------------------------------------------------------------

select * from v$services;

--16-------------------------------------------------------------------------

select * from v$dispatcher;

--17-------------------------------------------------------------------------

-- На докере не надо

--18-------------------------------------------------------------------------

-- cat /opt/oracle/product/23ai/dbhomeFree/network/admin/listener.ora


--19------------------------------------------------------------------------

--  lsnrctl services