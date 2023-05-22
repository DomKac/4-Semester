import sys;

file = open(sys.argv[1], 'rb+')


while 1:
    sym = file.read(1)
    if not sym:
        break

    print(sym)

file.close()