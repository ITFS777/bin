import socket
import struct
import os
# ------------------------------------------------------------
hostname = socket.gethostname()
ip = socket.gethostbyname(hostname)
# Get IP address
Port = '23333'
# Get Port
Client_Path = 'D:\\Minecraft\\Minecraft1.7.10'
Server_Path = 'D:\\Minecraft\\Minecraft_Server 1.7.10'
Client_Path += '\\.minecraft\\servers.dat'
Server_Path += '\\server.properties'
abspath = os.getcwd()
# Get Path
# ------------------------------------------------------------
server_properties = open(Server_Path,'r+')
server_dat = open(Client_Path,'rb+')
text = open(abspath+'\\IP.txt','w')
# open file to write
for i in range(14):
    server_properties.readline()
server_properties.seek(server_properties.tell()+10,0)
server_properties.write(ip)
# write IP address to server.properties
ip += ':' + Port
server_dat.seek(25,0)
for i in ip:
    server_dat.write(struct.pack('b',ord(i)))
# write IP and Port to servers.dat
text.write(ip)
# write IP and port to IP.txt