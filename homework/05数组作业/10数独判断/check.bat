@echo ���Լ�����ʼ����ʱԼ��ʮ�롣^����ʱ���޷�Ӧ���볢�Դ�echo������
@echo �����κα�����ʾʧ��


echo >myresult.txt
echo >demoresult.txt

setlocal enabledelayedexpansion

set count=0
for %%i in (test-data\*.txt) do (
echo Data #!count! is %%i >>myresult.txt
my <%%i >>myresult.txt
set /a count+=1
)

set count=0
for %%i in (test-data\*.txt) do (
echo Data #!count! is %%i >>demoresult.txt
demo <%%i  >>demoresult.txt
set /a count+=1
)

echo on

fc myresult.txt demoresult.txt

@pause