import os
import sys
import random
from random import randrange
import hashlib
import string

if (len(sys.argv) != 4):
	print "Usage: python randNet.py <# of Nodes> <# of Edges> <output file>"
	exit(-1)

random.seed()

#initialize variables
numNodes = string.atoi(sys.argv[1])
numEdges = string.atoi(sys.argv[2])
outputFile = sys.argv[3]

#create non-repeating random list of weights from 1 to numEdges+1
#This ensures a unique MST
listWeight = random.sample(range(1,numEdges+1), numEdges)
listTime = random.sample(range(1,numEdges+1), numEdges)

#create array of random nodenames
a = []

#fill array with random 5 character strings
for x in xrange(numNodes):
	str = "".join([random.choice(string.ascii_letters + string.digits) for n in xrange(5)])
	# check for collision
	while (str in a):
		str = "".join([random.choice(string.ascii_letters + string.digits) for n in xrange(5)])
		
	a.append(str)

#open file
f = open(outputFile, "w")

for x in xrange(numEdges):
	#default weight and edge range is 1-100.  Change below if desired
	f.write("%s\t%s\t%d\t%d\n" % (a[randrange(numNodes)],a[randrange(numNodes)],
		listWeight[x],listTime[x]))
	
f.close()



