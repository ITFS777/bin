@echo off
git add .
git commit -m "%date:~3,10% %time:~0,2%:%time:~3,2%:%time:~6,2% by ITFS<Aryan.ITFS@Gmail.com>"
git push bin master