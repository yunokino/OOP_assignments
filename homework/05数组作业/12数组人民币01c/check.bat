@type copyright

@echo 测试即将开始，用时约一分钟。^若长时间无反应，请尝试打开echo检查错误。
@echo 出现任何报错即表示失败

echo >myresult.txt
echo >demoresult.txt

setlocal enabledelayedexpansion

set count=0
for /f "delims=^" %%i in (test-data.txt) do (
echo Data #!count! is %%i^ >>myresult.txt
echo %%i^ | my>>myresult.txt
set /a count+=1
)

set count=0
for /f "delims=^" %%i in (test-data.txt) do (
echo Data #!count! is %%i^ >>demoresult.txt
echo %%i^ | demo >>demoresult.txt
set /a count+=1
)

echo on

fc myresult.txt demoresult.txt

@pause