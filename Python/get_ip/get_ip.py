import socket
import struct
hostname = socket.gethostname()
ip = socket.gethostbyname(hostname)
Client_Path = 'D:\\Minecraft\\Minecraft1.7.10'
Port = '23333'
Server_Path = 'D:\\Minecraft\\Minecraft_Server 1.7.10'
Client_Path += '\\.minecraft\\servers.dat'
Server_Path += '\\server.properties'

# Get IP address
server_properties = open(Server_Path,'r+')
server_dat = open(Client_Path,'rb+')
text = open('C:\\Users\\13749\\Desktop\\IP.txt','w')
for i in range(14):
    server_properties.readline()
server_properties.seek(server_properties.tell()+10,0)
server_properties.write(ip)
ip += ':' + Port
server_dat.seek(25,0)
for i in ip:
    server_dat.write(struct.pack('b',ord(i)))
text.write(ip)