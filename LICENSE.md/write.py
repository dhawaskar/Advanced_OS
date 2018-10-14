#! /usr/bin/python 
import sys


if len(sys.argv) != 4:
	print "Usage: "+sys.argv[0]+"  pid <String to search for> <String to replace it with>"
	exit(0)
pid = int(sys.argv[1])
str1 = str(sys.argv[2])
str2 = str(sys.argv[3])
print "The pid is",pid,"String to search for is ",str1," String to be replaced is ",str2

filename="/proc/"+sys.argv[1]+"/mem"
filename1="/proc/"+sys.argv[1]+"/maps"
print "File to be inspected to read the virtual memory "+filename

fp = open(filename1, 'r')
for line in fp:
	sline = line.split(' ')
    	if sline[-1][:-1] != "[heap]":
        	continue
    	print("Found heap line")

    	addr = sline[0]
    	perm = sline[1]
    	if perm[0] != 'r' or perm[1] != 'w':
        	print("you don't have permission to acces the pages i.e to write")
        	fp.close()
        	exit(0)

    	addr = addr.split("-")
    	addr_start = int(addr[0], 16)
    	addr_end = int(addr[1], 16)
	print("Heap memory address range",addr_start,"to",addr_end);

fp.close()

fp = open(filename, 'rb+')
fp.seek(addr_start)
buffer_str = fp.read(addr_end - addr_start)
print "Red contents are ",buffer_str
i = buffer_str.index(bytes(str1))
print ("Index of string to search is at ",i)
fp.seek(addr_start + i)
fp.write(bytes(str2))
fp.close()

