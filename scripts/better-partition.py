
# reorder the lines into their better partitions
# based on chaco generated partition file

def main (partition_filename, gate_filename, partition_count):
    f = open(partition_filename, 'r')
    part_assign = []
    for line in f:
        line = int(line.strip('\n'))
        part_assign.append(line)
    f.close()
    f = open(gate_filename, 'r')
    new_order = [[] for i in range(partition_count)]
    current = 0
    for line in f:
        new_order[part_assign[current]].append(line)
        current += 1
    f.close()
    max_part = max([len(p) for p in new_order])
    f = open("better_partition_"+str(partition_count)+"_"+gate_filename, 'w')
    for p in new_order:
        for line in p:
            f.write(line)
        diff = max_part - len(p)
        gap = "\n" * diff
        f.write(gap)
    f.close()


import sys

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print "Usage: python", sys.argv[0], "chaco_partion.txt gate_init_file.gate_parser_generated.txt partition_count"
    else:
        main(sys.argv[1], sys.argv[2], int(sys.argv[3]))
