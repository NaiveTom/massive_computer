content = \
'''
Welcome to relay computer
If you see this message, the bootloader has been loaded successfully
The instruction set of this computer is as follows:

ADDition, SUBtraction, MULtiplication, DIVision, AND, OR, NOT,
XOR, XNOR, MOVe, PUSH, POP, ShiFt Left, ShiFt Right,
No OPeration, ENerGy saving mode, CoMPare, JuMP.

Please refer to the manual for details!

-> 
'''

print('总字数: ')
print(len(content))
print()

counter = 0
num = 1

print('%03d ->'%num, end = '  ')

for i in content:
    
    print('%#04x'%ord(i), end = '  ')
    counter += 1
    
    if counter == 3:
        num += 1
        print(); print()
        print('%03d ->'%num, end = '  ')
        counter = 0
