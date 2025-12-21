alter pluggable database KEO_PDB open;

GRANT CREATE TABLESPACE TO KEO;
GRANT ALTER TABLESPACE TO KEO;

create tablespace t1
    datafile 't1_keo.dbf'
    size 7 m
    autoextend on
    maxsize unlimited
    extent management local;

create tablespace t2
    datafile 't2_keo.dbf'
    size 7 m
    autoextend on
    maxsize unlimited
    extent management local;

create tablespace t3
    datafile 't3_keo.dbf'
    size 7 m
    autoextend on
    maxsize unlimited
    extent management local;

create tablespace t4
    datafile 't4_keo.dbf'
    size 7 m
    autoextend on
    maxsize unlimited
    extent management local;

    
alter user KEO quota unlimited on t1;
alter user KEO quota unlimited on t2;
alter user KEO quota unlimited on t3;
alter user KEO quota unlimited on t4;

drop tablespace t1 including contents and datafiles;
drop tablespace t2 including contents and datafiles;
drop tablespace t3 including contents and datafiles;
drop tablespace t4 including contents and datafiles;


--1------------------------------------------------------------

create table T_RANGE
(
    id      number,
    TIME_ID date
)
partition by range (id) 
(
    partition p0 values less than (100) tablespace t1,
    partition p1 values less than (200) tablespace t2,
    partition PMAX values less than (maxvalue) tablespace t4
);

drop table T_RANGE purge;


--2------------------------------------------------------------

create table T_INTERVAL
(
    id      number,
    TIME_ID date
)
tablespace t1
partition by range (TIME_ID)
interval (numtoyminterval(1,'MONTH'))
(
    partition p1 values less than (date '2024-01-01')
);

drop table T_INTERVAL purge;

--3------------------------------------------------------------

create table T_HASH
(
    code varchar2(10),
    data varchar2(20)
)
tablespace t2
partition by hash (code)
partitions 4;

drop table T_HASH purge;

--4------------------------------------------------------------

create table T_LIST
(
    status char(1),
    descr  varchar2(20)
)
partition by list (status)
(
    partition p_a values ('A') tablespace t1,
    partition p_b values ('B') tablespace t2,
    partition p_other values (default) tablespace t4
);

drop table T_LIST purge;

--5--------------------------------------------------------

insert into T_RANGE values (1, sysdate);
insert into T_RANGE values (101, sysdate);
insert into T_RANGE values (201, sysdate);




insert into T_INTERVAL values (1, '01-12-2023');
insert into T_INTERVAL values (2, '01-02-2024');
insert into T_INTERVAL values (3, '01-03-2025');



insert into T_HASH values ('A1', 'one');
insert into T_HASH values ('B2', 'two');
insert into T_HASH values ('C3', 'three');


insert into T_LIST values ('A', 'alpha');
insert into T_LIST values ('B', 'beta');
insert into T_LIST values ('C', 'other');

commit;


select table_name, partition_name, num_rows, high_value
from user_tab_partitions
where table_name like 'T_%'
order by table_name;


select * from T_RANGE partition(p1);
--6---------------------------------------------------------------

alter table T_RANGE enable row movement;
alter table T_INTERVAL enable row movement;
alter table T_HASH enable row movement;
alter table T_LIST enable row movement;

update T_RANGE set id = 250 where id = 1;
update T_INTERVAL set TIME_ID = '02-06-2024' where TIME_ID = '01-12-2023';
update T_HASH set code = 'Z9' where code = 'A1';
update T_LIST set status = 'A' where descr ='other';
commit;

--можно посмотреть перенесенные строки в разделе
select *
from T_RANGE partition (p0);

-- либо посмотреть статистикку пов всем разделам
-- Если стата не обновляется - запустить exec
exec dbms_stats.gather_table_stats(user, 'T_INTERVAL');
exec dbms_stats.gather_table_stats(user, 'T_RANGE');
exec dbms_stats.gather_table_stats(user, 'T_HASH');
exec dbms_stats.gather_table_stats(user, 'T_LIST');

select table_name, partition_name, num_rows, high_value
from user_tab_partitions
where table_name like 'T_%'
order by table_name;


--7---------------------------------------------------------------


alter table T_RANGE
merge partitions p0, p1 into partition p1
tablespace t1;

select partition_name, num_rows, high_value
from user_tab_partitions
where table_name = 'T_RANGE'
order by partition_position;


--8---------------------------------------------------------------

alter table T_RANGE
split partition p1
at (150)
into
(
    partition p0,
    partition p1
);

select partition_name, num_rows, high_value
from user_tab_partitions
where table_name = 'T_RANGE'
order by partition_position;

--9---------------------------------------------------------------

create table T_EXCHANGE
(
    id number,
    TIME_ID date
);


alter table T_RANGE
exchange partition p0
with table T_EXCHANGE
without validation;

select * from T_EXCHANGE;
delete T_EXCHANGE;


select * from T_RANGE partition (p0);
