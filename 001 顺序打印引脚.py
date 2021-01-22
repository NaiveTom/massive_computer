num = 7
step = 2
begin = 41

num *= step

for i in range(begin, begin+num, step):
    print(i, end=',')
