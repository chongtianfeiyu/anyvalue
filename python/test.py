#coding=utf-8
import anyvalue

class Demo:
	def getDemo(self):
		pass;


infile = open('conn_anyvalue.bin')
outfile = open('conn_anyvalue2.bin','w+')

buf = infile.read()
obj = anyvalue.decode(buf);
print obj
obj['names']='蒋有星'
obj['tuple'] = (1,2,3,4,6,'32232323',1.5666)
#obj['names1'] = Demo()

outfile.write(anyvalue.encode(obj));


