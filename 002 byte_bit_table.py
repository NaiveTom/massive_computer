num = 1

for i in range(16):
    print(num<<i, end=', ')

print(); print()

for i in range(16):
    print('0x%x'%(num<<i), end=',')
