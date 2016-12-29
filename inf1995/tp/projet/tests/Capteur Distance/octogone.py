f = open('octogone_data.txt')
w = open('octogone_out.txt', 'w')

for line in f:
    l = line.split()
    for word in l:
        w.write(word)
        w.write('\n')
