def decToS(num):
    ret = list()
    faster = 0
    lenght = 0
    while num != 0:
        rest = num%5
        if rest == 3:
            if faster ==0:
                ret.append('=')
                ret.append('1')
                faster = 1
                lenght +=2
            else:
                if ret[lenght-1] == '2':
                    ret[lenght-1] = '0'
                elif  ret[lenght-1] == '1':
                    ret[lenght-1] = '-'
                elif ret[lenght-1] == '0':
                    ret[lenght-1] = '='
                ret.append('1')
                lenght+=1
        elif rest == 4:
            if faster ==0:
                ret.append('-')
                ret.append('1')
                faster = 1
                lenght +=2
            else:
                if ret[lenght-1] == '2':
                    ret[lenght-1] = '1'
                elif  ret[lenght-1] == '1':
                    ret[lenght-1] = '0'
                elif ret[lenght-1] == '0':
                    ret[lenght-1] = '-'
                ret.append('1')
                lenght+=1
        else:
            if faster == 1:
                if rest == 0:
                    faster = 0
                if rest == 1:
                        ret[lenght-1] = '2'
                        faster = 0
                if rest == 2:
                        ret[lenght-1] = '='
                        lenght+=1
                        ret.append('1')
                        faster = 1
            else:
                if rest == 0:
                    ret.append('0')
                if rest == 1:
                    ret.append('1')
                if rest == 2:
                    ret.append('2')
                lenght+=1
        
        num-=rest
        num/=5
    return ''.join(ret)[::-1]
            



def main():
    sum = 0
    with open("in.txt") as f:
        for line in f:
            half = 0
            for a in line:
                if a == '\n':
                    break
                half*=5
                if a == '0':
                    half+=0
                if a == '1':
                    half+=1
                if a == '2':
                    half+=2
                if a == '-':
                    half-=1
                if a == '=':
                    half-=2
            sum+=half
    print(sum)
    numstr = decToS(sum)
    print(numstr)
    

main()
