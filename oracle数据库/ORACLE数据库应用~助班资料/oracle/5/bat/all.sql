spool C:\bat\test.log
conn sys/sjzu@sjzu as sysdba
@C:\bat\user.sql
conn test/test@sjzu
@C:\bat\student.sql
spool off