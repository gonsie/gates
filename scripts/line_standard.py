import sys

def check_standard(file_name):
    f = open(file_name, 'r')
    l1 = f.readline()
    m = len(l1)
    for line in f:
        if len(line) is not m:
            f.close()
            return False
    f.close()
    return True

def get_longest(file_name):
    f = open(file_name, 'r')
    m = 0
    for line in f:
        content = line[:-1].strip(' ')
        m = max(len(content), m)
    f.close()
    # add one for \n
    return m+1

def standardize(file_name, length):
    f = open(file_name, 'r')
    o = open(file_name+".std", 'w')
    for line in f:
        if len(line) < length:
            d = length - len(line)
            line = line[:-1]
            line += ' ' * d
            line += '\n'
        elif len(line) > length:
            if line[-2] is not " ":
                print "Chopping line:"
                print "\"" + line + "\""
                print "\"" + line[:-(d+1)] + "\""
            d = len(line) - length
            line = line[:-(d+1)]
            line += '\n'
        o.write(line)
    o.close()
    f.close()

if __name__ == "__main__":
    if len(sys.argv) is 1:
        print >> sys.stderr, "Usage:", sys.argv[0], "file_name"
    else:
        if not check_standard(sys.argv[1]):
            print "Line lengths are not standard"
            l = get_longest(sys.argv[1])
            print "Standardizing line lengths to", l
            standardize(sys.argv[1], l)
        else:
            print "Line lengths are standard"

