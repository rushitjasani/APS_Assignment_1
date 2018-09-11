f = open("output","r")

f1 = f.readlines()
p=-1
print "Read Done"
for x in f1:
	if x<p:
		print x, y,"NO",
		j=input()
		break
print "OK"
f.close()
