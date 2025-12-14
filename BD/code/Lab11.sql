alter pluggable database KEO_PDB open;

grant create procedure to keo;

--1------------------------------------------------------------------
select * from teacher;

create or replace procedure GET_TEACHERS(pcode teacher.pulpit%TYPE)
is
begin
    for teacher in (select * from teacher where pulpit = pcode)
    loop
        dbms_output.put_line(teacher.teacher_name);
        
    end loop;
    
end;

begin
    GET_TEACHERS('ИСиТ');   
end;

--2-----------------------------------------------------------------

declare 

function COUNT_PULPIT_TEACHERS(pcode teacher.pulpit%TYPE)
return number is
counter number;
cCur SYS_REFCURSOR;
begin
    open cCur for 
    select count(*) from teacher where pulpit = pcode;
    
    fetch cCur into counter;
    
    return counter;   
end COUNT_PULPIT_TEACHERS;
begin 
    dbms_output.put_line('Преподавателей на кафедре ИСиТ: ' || count_pulpit_teachers('ИСиТ'));

end;

--3-------------------------------------------------------------------

create or replace function get_num_teachers(pcode teacher.pulpit%TYPE)
return number is
counter number;
cCur SYS_REFCURSOR;
begin
    open cCur for 
    select count(*) from teacher where pulpit = pcode;
    
    fetch cCur into counter;
    
    return counter;   
end;



begin
     dbms_output.put_line('Преподавателей на кафедре ИСиТ: ' || get_num_teachers('ИСиТ'));
end;

--4---------------------------------------------------------------

create or replace procedure GET_TEACHERS(FCODE FACULTY.FACULTY%TYPE)
is
begin
    for teacher in 
    (select * from teacher where pulpit in (select pulpit from faculty where faculty = FCODE))
    loop
        dbms_output.put_line(teacher.teacher_name);
    
    end loop;

end;


create or replace procedure GET_SUBJECTS(PCODE SUBJECT.PULPIT%TYPE)
is
begin
    for subject in (select * from subject where pulpit = pcode)
    loop
        dbms_output.put_line(subject.subject);
    end loop;

end;



begin 
    GET_TEACHERS('ИДиП');
    dbms_output.put_line('---------------------------------------');
    GET_SUBJECTS('ИСиТ');
end;


--5-------------------------------------------------------------------
declare
function GET_NUM_TEACHERS(FCODE FACULTY.FACULTY%TYPE)
return number
is
counter number;
cCur SYS_REFCURSOR;
begin
    open cCur for 
    Select count(*) from teacher where pulpit in
    (select pulpit from faculty where faculty = FCODE);
    
    fetch cCur into counter;
    
    return counter;
end GET_NUM_TEACHERS;
    
begin
    dbms_output.put_line('Преподавателей на факультете ИДиП: ' || get_num_teachers('ИДиП'));
end;


declare
function GET_NUM_SUBJECTS(PCODE SUBJECT.PULPIT%TYPE)
return number
is
counter number;
cCur SYS_REFCURSOR;
begin
    open cCur for 
    Select count(*) from subject where pulpit = PCODE;
    
    fetch cCur into counter;
    
    return counter;
end GET_NUM_SUBJECTS;
    
begin
    dbms_output.put_line('Дисциплин на факультете: ' || get_num_subjects('ИСиТ'));
end;


--6-------------------------------------------------------------

create or replace package TEACHERS 
is
procedure GET_TEACHERS(FCODE FACULTY.FACULTY%TYPE);
procedure GET_SUBJECTS (PCODE SUBJECT.PULPIT%TYPE);
function GET_NUM_TEACHERS(FCODE FACULTY.FACULTY%TYPE) return number;
function GET_NUM_SUBJECTS(PCODE SUBJECT.PULPIT%TYPE) return number;

end TEACHERS;

--7-------------------------------------------------------------

create or replace package body TEACHERS is
  procedure GET_TEACHERS(FCODE FACULTY.FACULTY%TYPE) is
  begin
    for teacher in (select * from TEACHER where PULPIT in (select PULPIT from PULPIT where FACULTY = FCODE))
      loop
        dbms_output.put_line(teacher.TEACHER_NAME);
      end loop;
  end;

  procedure GET_SUBJECTS(PCODE SUBJECT.PULPIT%TYPE) is
  begin
    for subject in (select * from SUBJECT where PULPIT = PCODE)
      loop
        dbms_output.put_line(subject.SUBJECT_NAME);
      end loop;
  end;

  function GET_NUM_TEACHERS(FCODE FACULTY.FACULTY%TYPE) return number
    is
    num number;
  begin
    select count(*) into num from TEACHER where PULPIT in (select PULPIT from PULPIT where FACULTY = FCODE);
    return num;
  end;

  function GET_NUM_SUBJECTS(PCODE SUBJECT.PULPIT%TYPE) return number
    is
    num number;
  begin
    select count(*) into num from SUBJECT where PULPIT = PCODE;
    return num;
  end;
end TEACHERS;


begin
    TEACHERS.get_teachers('ИДиП');
    dbms_output.put_line('-------------------------------------------');
    TEACHERS.get_subjects('ИСиТ');
    dbms_output.put_line('-------------------------------------------');
    dbms_output.put_line('Преподавателей на факультете ИДиП: ' || get_num_teachers('ИДиП'));
    dbms_output.put_line('-------------------------------------------');
    dbms_output.put_line('Дисциплин на факультете: ' || get_num_subjects('ИСиТ'));
    
end;




