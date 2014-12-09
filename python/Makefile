PYTHON_LIB_PATH=/usr/lib/python2.7/
PYTHON_SRC=/usr/include/python2.6

INCLUDE=-I$(PYTHON_SRC)

CC=g++

all: anyvalue.so

anyvalue.so: anyvalue.o decode.o encode.o
	$(CC) -shared -O2 -rdynamic -o anyvalue.so anyvalue.o decode.o encode.o

anyvalue.o: anyvalue.cpp
	$(CC) -fpic -O2 $(INCLUDE) -c anyvalue.cpp
decode.o: decode.cpp decode.h
	$(CC) -fpic -O2 $(INCLUDE) -c decode.cpp

encode.o: encode.cpp encode.h
	$(CC) -fpic -O2 $(INCLUDE) -c encode.cpp

clean:
	rm -fr *.so *.o

install: anyvalue.so
	cp -fp anyvalue.so $(PYTHON_LIB_PATH)
