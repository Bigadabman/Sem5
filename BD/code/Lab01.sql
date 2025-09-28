create table KEO_t(x number(3) primary key, s varchar2(50));

--------------------------------------------


insert into KEO_t values (1, 'str1');
insert into KEO_t values (2, 'str2');
insert into KEO_t values (3, 'str3');
insert into KEO_t values (5, 'str5');

commit;

--------------------------------------------


update KEO_t set x=4 where x = 1;
update KEO_t set s = 'string' where x = 4;

commit;

--------------------------------------------


select * from KEO_t where s LIKE '%str%';
select sum(x) from KEO_t;
 
--------------------------------------------


delete KEO_t where s = 'string';

commit;

--------------------------------------------


create table KEO_t1 (z number(3),
x number(3), 
foreign key (x) references KEO_t(x));


insert into keo_t1 values (1, 2);
insert into keo_t1 values (1, 2);
insert into keo_t1 values (2, 3);

-------------------------------------------

select * from keo_t LEFT JOIN keo_t1 on keo_t.x = keo_t1.x;
select * from keo_t right join keo_t1 on keo_t.x = keo_t1.x;
select * from keo_t join keo_t1 on keo_t.x = keo_t1.x;

-------------------------------------------


drop table KEO_t1;
drop table KEO_t;


