import gmpy2


def isPrime(num):
    if ((num % 6 != 1) and (num % 6 != 5)):
        if((num == 2) or (num == 3)):
            return True
        else:
            return False
    else:
        return gmpy2.is_prime(num)


while True:
    target = gmpy2.mpz(input("Number to break>"))
    with open("result.txt", 'a') as result:
        result.write(str(target)+' = ')
    print(str(target)+"\n └",end='')
    decom = []
    i = 1
    while i <= target:
        if isPrime(target):
            decom.append(int(target))
            with open("result.txt", 'a') as result:
                result.write(str(target)+'\n')
            print(str(target))
            break
        else:
            while i <= target:
                if isPrime(i):
                    if(target % i == 0):
                        decom.append(i)
                        with open("result.txt", 'a') as result:
                            result.write(str(i)+' * ')
                        target = target // i
                        print(target, i, sep=" × ")
                        print(' '*(len(decom)*2+1)+"└",end='')
                        break
                i += 1
    print(decom)
    del decom
