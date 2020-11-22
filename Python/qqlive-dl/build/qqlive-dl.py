# you-get script for QQ Live Series
# Sun Nov 22 20:16:12 CST 2020 
# @Version 1.0
# @Auther ITFS777
# @Email Aryan.ITFS@iCloud.com
# @License MIT License
# @Copyright © 2020, ITFS777


# Pip requirements below:
import requests
from os import system


# Put the url of the first episode of each collection you want to download
# And then it will download 1-120 to the target directory.
# For example (1 of 1-120)
# url = "https://v.qq.com/x/cover/l4z4mjtn43rvlvt/s0012ecy8v9.html"
url=input("请输入要下载的剧集部分的其中一集的链接\n比如1-120里的1，会下载1-120集\n")
dir_input = input("请输入要保存的位置(回车则为桌面):")
if dir_input == "":
    directory = "%USERPROFILE%\\Desktop\\Download\\"
else:
    directory = dir_input


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