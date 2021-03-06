# you-get script for QQ Live Series
# Sun Nov 22 20:16:12 CST 2020 
# @Version 1.0
# @Auther ITFS777
# @Email Aryan.ITFS@iCloud.com
# @License MIT License
# @Copyright © 2020, ITFS777


# Pip requirements below:
# you-get
# requests


# Put the url of the first episode of each collection you want to download
# And then it will download 1-120 to the target directory.
# For example (1 of 1-120)
# url = "https://v.qq.com/x/cover/l4z4mjtn43rvlvt/s0012ecy8v9.html"
url = "https://v.qq.com/x/cover/53q0eh78q97e4d1/x00174aq5no.html"


# The directory you want to save
directory = "%USERPROFILE%\\Desktop\\名侦探柯南"


import requests
from os import system

index = url[0:url.rfind('/')+1]

res = requests.get(url)
assert res.status_code == 200
res.encoding = "utf-8"

html = res.text
html = html[html.find('<div class="mod_episode" data-tpl="episode" _wind="columnname=选集">'):-1]
html = html[0:html.find("</div>")]

lst=[]
while "{current: curVid == " in html:
    html = html[html.find("{current: curVid == "):-1]
    lst.append(html[21:html.find('}')-1])
    html = html[html.find("}"):-1]

command = "you-get -o "+directory+' '
for item in lst:
    system(command+index+item+".html")