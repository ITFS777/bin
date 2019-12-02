import base64
while True:
    flag = input('en/de\n')
    if flag == 'en':
        string = input()
        print(str(base64.b64encode(string.encode('utf-8')), 'utf-8'))
        print()
    else:
        string = input()
        decode = base64.b64decode(string.encode('utf-8'))
        print(decode)
        for x in decode:
            print(chr(x),end='')
        print()
        seq = ''
        for x in decode:
             seq += bin(x).replace('b','')
        print(seq)
        print()
