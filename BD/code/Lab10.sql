alter pluggable database open;

--1--------------------------------------------------

alter table teacher
add (birthday date, salary number);

update teacher 
set salary = floor(dbms_random.value(2000, 4000)),
birthday = trunc(sysdate) - floor(dbms_random.value(365*23, 365*50));


select * from teacher;

alter table teacher drop column salary;
alter table teacher drop column birthday;


--2-----------------------------------------------------------------

select substr(teacher_name, 0, instr(teacher_name, ' ')+1) || '.' 
|| substr(teacher_name, instr(teacher_name, ' ', 1, 2) + 1, 1) || '.' as ФИО
from teacher;

--3-----------------------------------------------------------------

select * from teacher where to_char(birthday, 'D') = 1; 

--4-----------------------------------------------------------------

create or replace view next_month_birthday
as
select * from teacher
where to_char(birthday, 'MM') = mod(to_char(sysdate, 'MM') + 1, 12);

select * from next_month_birthday;

--5-----------------------------------------------------------------

create or replace view month_amount
as 
select to_char(birthday, 'MONTH') as month, count(*) as amount
from teacher group by to_char(birthday, 'MONTH');

select * from month_amount;

--6----------------------------------------------------------------

declare
    cTeach  SYS_REFCURSOR;
     vTeacher_name teacher.teacher_name%type;
    vBirthday     teacher.birthday%type;
begin
    open cTeach for 
    select teacher_name, birthday  from teacher
    where mod(to_char(sysdate, 'YYYY') + 1 - (to_char(birthday, 'YYYY')), 5) = 0;
    
    loop
        fetch cTeach into vTeacher_name, vBirthday;
        exit when cTeach%notfound;

        dbms_output.put_line(vTeacher_name || ' ' || vBirthday);
    end loop;
    

end;
/

--7-------------------------------------------------------


declare 
cSalary SYS_REFCURSOR;
aFaculty pulpit.pulpit%type;
aSalary teacher.salary%type;
aPulpit pulpit.pulpit%type;

begin
open cSalary for
select faculty.faculty, pulpit.pulpit, floor(avg(salary)) 
from teacher inner join pulpit on pulpit.pulpit = teacher.pulpit
inner join faculty on faculty.faculty = pulpit.faculty
group by rollup( faculty.faculty, pulpit.pulpit);


loop 
    fetch cSalary into aFaculty,aPulpit, aSalary;
    exit when cSalary%notfound;
    if aFaculty is NULL then 
     dbms_output.put_line('Общая: ' || aSalary);
    else
    dbms_output.put_line('Средняя по ' || trim(aFaculty) || ' ' || trim(aPulpit) || ': ' || aSalary);
    end if;
    
end loop;

end;
/

--8-----------------------------------------------------------------

declare
    type tTeacher is record
    (
        full_name       teacher.teacher_name%type,
        birth_date      teacher.birthday%type,
        salary_amount   teacher.salary%type,
        random_number   number
    );

    type tTeacherOuter is record
    (
        teacher_data    tTeacher,
        extra_text      varchar2(50)
    );

    teacher1     tTeacher;
    teacher2     tTeacher;
    teacherOuter tTeacherOuter;

begin
    teacher1.full_name     := 'fullname var1';
    teacher1.birth_date    := sysdate;
    teacher1.salary_amount := 1356;
    teacher1.random_number := 6.2;

    dbms_output.put_line('teacher1: '||
        teacher1.full_name||' '||
        teacher1.salary_amount||' '||
        teacher1.random_number);

    teacher2 := teacher1;

    dbms_output.put_line('teacher2: '||
        teacher2.full_name||' '||
        teacher2.salary_amount||' '||
        teacher2.random_number);

    teacherOuter.teacher_data := teacher2;
    teacherOuter.extra_text   := '13:56';

    dbms_output.put_line('Outer salary: '||
        teacherOuter.teacher_data.salary_amount);

end;
/

