f = open('cercle_data.txt')
w = open('cercle_out.txt', 'w')

for line in f:
    l = line.split()
    for word in l:
        w.write(word)
        w.write('\n')
