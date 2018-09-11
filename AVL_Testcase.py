import random

n = random.randint(1,500001)
m = random.randint(1,100001)
print n;
print m;
for i in range(n):
    l = random.randint(1,n)
    print l,
    print " ",
for i in range(m):
    l = random.randint(1,3)
    p = random.randint(1,n)
    print l,
    print " ",
    print p
