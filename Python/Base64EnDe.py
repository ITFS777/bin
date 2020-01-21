import base64
newTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
oldTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
while True:
    flag = input('encode[e]/decode[d]/changeTable[c]\n>')
    if flag == 'e':
        string = input("string:")
        print(base64.b64encode(string.encode('utf-8')).decode())
        print()
    elif flag == 'd':
        string = input("Base64:")
        result = base64.b64decode(string.translate(
            str.maketrans(newTable, oldTable))).decode()
        print("String:", result, "Hex:", sep='\n')
        i = 0
        for x in result:
            i += 1
            print("{:02X}".format(ord(x)), end=' ')
            if(i % 16 == 0):
                print()
        print("\nOct:")
        i = 0
        for x in result:
            i += 1
            print("{:03d}".format(ord(x)), end=' ')
            if(i % 16 == 0):
                print()
        print()
    elif flag == 'c':
        print("oldTable:", oldTable, sep='')
        newTable = input("newTable:")
        print("Table Changed")
    else:
        print("Illegal Input!")
