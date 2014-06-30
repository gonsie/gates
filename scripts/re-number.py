import sys

def main(filename, lib_filename):
    f = open(filename, 'r')
    lines = [[x for x in line.strip(' \n').split(' ') if len(x) > 0] for line in f]
    f.close()
    print "Found", len(lines), "lines"
    # 1st pass: re-number gids
    gid_map = {}
    current = 0
    for l in lines:
        if len(l) < 1:
            continue
        gid_map[l[0]] = str(current)
        l[0] = gid_map[l[0]]
        current += 1
    print "Found", current, "valid lines"
    # 2nd pass: re-number inputs and outputs
    # input/output count based on library file
    f = open(lib_filename, 'r')
    all_lines = [x.strip('\t\n').split(' ') for x in f]
    types = [(all_lines[i][0], len(all_lines[i+1]), len(all_lines[i+2])) for i in range(0, len(all_lines), 3)]
    # special case for input_gate output_gate
    types[-2] = (types[-2][0], 0, 1)
    types[-1] = (types[-1][0], 1, 0)
    f.close()
    for l in lines:
        if len(l) < 1:
            continue
        elif l[1] == '163': # fannout
            l[2] = gid_map[l[2]]
        else:
            # single input gid
            i = 2
            in_count = types[int(l[1])][1]
            for j in range(in_count):
                if l[i] != '-1':
                    l[i] = gid_map[l[i]]
                i += 1
            # output gid/pin pairs
            out_count = types[int(l[1])][2]
            for j in range(out_count):
                if l[i] != '-1':
                    l[i] = gid_map[l[i]]
                i += 2
    f = open(filename+".renumbered", 'w')
    for l in lines:
        f.write(' '.join(l))
        f.write("\n")
    f.close()

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print "Usage: python", sys.argv[0], "ordered-filename lib_filename"
    else:
        main(sys.argv[1], sys.argv[2])
