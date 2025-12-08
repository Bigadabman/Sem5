ALTER PLUGGABLE DATABASE KEO_PDB OPEN;

--1-----------------------------------------------------------

    begin
        null;
    end;
    
    
--2-----------------------------------------------------------


declare
    begin
        dbms_output.put_line('Hello, World!');
    end;

--3-----------------------------------------------------------

declare 
    x number(3) := 3;
    y number(3) := 0;
    z number(10,2);
begin
    dbms_output.put_line('x = ' ||x||
                        ', y = '||y||
                        ', z = '||z);
    z :=x/y;
    dbms_output.put_line('z = '||z); 
        
    exception
        when others
        then dbms_output.put_line('error: code='||sqlcode||' message: '||sqlerrm); 
end;

--4----------------------------------------------------------


declare 
    x number(3) := 3;
    y number(3) := 0;
    z number(10,2);
begin
    dbms_output.put_line('x = ' ||x||
                        ', y = '||y||
                        ', z = '||z);
    begin
    z :=x/y;
    dbms_output.put_line('inner z = '||z); 
        
    exception
        when others
        then dbms_output.put_line('error: code='||sqlcode||' message: '||sqlerrm); 
    end;
    dbms_output.put_line('outer z = '||z); 
end;

--5---------------------------------------------------------------


select * from v$parameter where name = 'plsql_warnings';

--6---------------------------------------------------------------

select keyword from v$reserved_words where length = 1 and keyword != 'A';


--7----------------------------------------------------------------

select keyword from v$reserved_words where length > 1 and keyword != 'A' order by keyword;

--8---------------------------------------------------------

select * from v$parameter where name like '%plsql%';

show parameter plsql;


--9-----------------------------------------------------------------
--10----------------------------------------------------------------

declare 
    x number := 4;
    y number := 10;
    begin
        dbms_output.put_line(x);
        dbms_output.put_line(y);    
    end;

--11----------------------------------------------------------------

declare 
    x number := 4;
    y number := 10;
    begin

        dbms_output.put_line(x+y);
        dbms_output.put_line(x-y);    
        dbms_output.put_line(x*y);
        dbms_output.put_line(x/y);
        dbms_output.put_line(x mod y);
    end;


--12------------------------------------------------------------

declare 
    x number := 123.123;
    y number(10,1) := 123.123;
    begin
        dbms_output.put_line(x);
        dbms_output.put_line(y);
    end;

--13------------------------------------------------------------

declare 
    x number(10,-2) := 1234567.127;
    y number(10,-3) := 123.123;
    begin
        dbms_output.put_line(x);
        dbms_output.put_line(y);
    end;


--14-------------------------------------------------------------


declare 
    x binary_float := 12345.12345;
    begin
        dbms_output.put_line(x);
    
    end;

--15-------------------------------------------------------------


declare 
    x binary_double := 12345.12345;
    begin
        dbms_output.put_line(x);
    
    end;

--16--------------------------------------------------------------

declare
    x number(20, 10) := 12345.123456E+005;
    begin
        dbms_output.put_line(x);
    end;

--17--------------------------------------------------------------

declare
  x boolean := true;
begin
  if x then
   dbms_output.put_line('true');
   ELSE
   dbms_output.put_line('false');
    end if;
end;


--18------------------------------------------------------------

declare
    x constant number := 10;
    begin
    x:= 25;
    exception
        when others
        then dbms_output.put_line('error: code='||sqlcode||' message: '||sqlerrm); 
    end;

--19-------------------------------------------------------------

declare
    x number (10, 3):= 123.123;
    y x%type := 123.123456;
    begin
        dbms_output.put_line(x);
        dbms_output.put_line(y);
    end;

--20------------------------------------------------------------

declare 
    x BANK%rowtype;
    begin
        x.balance := 10;
        x.name := 'Ivan';
        dbms_output.put_line(x.name||' has '||x.balance);
    end;
    
    
--21-------------------------------------------------------------
--22-------------------------------------------------------------

declare
    x number := 1;
    begin
    if x = 1 then
        dbms_output.put_line(x);
    elsif x = 2 then 
        dbms_output.put_line(x);
    else
        dbms_output.put_line(x);
    end if;
    end;
    
--23----------------------------------------------------------

declare
    x number := 1;
    begin
    case x
        when 1 then
          dbms_output.put_line(x);
       when 2 then
            dbms_output.put_line(x);
        else
            dbms_output.put_line(x);
    end case;
    end;

    
--24----------------------------------------------------------

declare 
    x number := 1;
    begin
        loop
            dbms_output.put_line(x);
            x:=x+1;
            exit when x > 10;
        end loop;
    end;
    
--25---------------------------------------------------------

declare 
    x number := 1;
    begin
        while x <=10 loop
            dbms_output.put_line(x);
            x:=x+1;
        end loop;
    end;



