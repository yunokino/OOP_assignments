@echo ************************************************
@echo *                     必读                     *
@echo ************************************************
@echo 本次demo无法正常重定向输入
@echo 所以放的是我自己的
@echo 和demo进行过十次comp全过
@echo ************************************************
@echo        重   如果不放心建议用demo手测   重
@echo        要   如果不放心建议用demo手测   要
@echo        的   如果不放心建议用demo手测   的
@echo        事   如果不放心建议用demo手测   事
@echo        说   如果不放心建议用demo手测   说
@echo        七   如果不放心建议用demo手测   七
@echo        遍   如果不放心建议用demo手测   遍
@echo ************************************************
@echo 如果已理解相关风险，请按回车键继续

@pause

@echo 测试即将开始，用时约四十秒。^若长时间无反应，请尝试打开echo检查错误。
@echo 出现任何报错即表示失败

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