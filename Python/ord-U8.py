while True:
    Unicode = int(input("int>"))
    if ((Unicode<0)or(Unicode>1114111)):
        print("Illegal Input!")
        continue
    print("utf-8[",chr(Unicode),"]",sep='')