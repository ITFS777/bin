import base64
newTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
oldTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
while True:
    flag = input('encode[e]/decode[d]/changeTable[c]\n>')
    if flag == 'e':
        string = input("string:")
        print(str(base64.b64encode(string.encode('utf-8'))))
        print()
    elif flag == 'd':
        string = input("Base64code:")
        print(base64.b64decode(string.translate(str.maketrans(newTable,oldTable))))
        print()
    elif flag == 'c':
        print("oldTable:",oldTable,sep='')
        newTable = input("newTable:")
        print("Table Changed")
    else:
        print("Illegal Input!")



