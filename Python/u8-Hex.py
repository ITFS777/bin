while True:
    string = input('>')
    length = len(string)
    for i in range(length):
        if (i % 16 == 0):  # 行索引
            print("%05X |" % i, end=' ')
        if(i % 16 == 7):  # 判断行中心位置
            print("%04X" % ord(string[i]), end='-')
        else:
            print("%04X" % ord(string[i]), end=' ')
        if (i % 16 == 15):
            print("|", end='')
            for j in range(15, -1, -1):
                print(' '+string[i-j], end='')
            print()

    if(length % 16):
        for i in range((length % 16), 16):  # 补全多余的0
            if(i % 16 == 7):  # 判断行中心位置
                print("%04X" % 0, end='-')
            else:
                print("%04X" % 0, end=' ')

        print("|", end='')
        for i in range(length % 16, 0, -1):
            print(' '+string[length-i], end='')
        for i in range(16-(length % 16)):
            print(" .", end='')
        print()