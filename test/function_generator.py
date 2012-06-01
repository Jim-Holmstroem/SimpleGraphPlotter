import itertools as itt
bin="+-*/<>^"
for s in itt.product(" -","2x",bin," -","3x",bin," -","4x"):
    print "".join(s)
