import sys
import os

def reorder(filename, npcount):
     filename = os.path.realpath(filename)
     if npcount == 1:
          print filename
          return     
     newfile = filename+".reorder."+str(npcount)
     if os.path.exists(newfile):
          print newfile
          return
     f = open(filename, 'r')
     o = open(newfile, 'w')
     buff = [[] for _ in xrange(npcount)]
     c = 0
     for line in f:
         buff[c % npcount].append(line)
         c += 1
     for block in buff:
         for line in block:
             o.write(line)
     f.close()
     o.close()
     print newfile

if __name__ == "__main__":
    if len(sys.argv) is 1:
        print >> sys.stderr, "Usage: python", sys.argv[0], "input_file np_count"
    else:
        reorder(sys.argv[1], int(sys.argv[2]))
