PHP_EXT_HOME=/opt/lampp/lib/php/extensions/no-debug-non-zts-20100525/
PHP_SRC=/opt/lampp/include/php/

INCLUDE=-I$(PHP_SRC) -I$(PHP_SRC)/main -I$(PHP_SRC)/TSRM -I$(PHP_SRC)/Zend

CC=g++

all: anyvalue.so

anyvalue.so: anyvalue.o decode.o encode.o
	$(CC) -shared -O2 -rdynamic -o anyvalue.so anyvalue.o decode.o encode.o

anyvalue.o: anyvalue.cpp
	$(CC) -fpic -O2 -DCOMPILE_DL_FIRST_MODULE=1 $(INCLUDE) -c anyvalue.cpp
decode.o: decode.cpp decode.h
	$(CC) -fpic -O2 -DCOMPILE_DL_FIRST_MODULE=1 $(INCLUDE) -c decode.cpp

encode.o: encode.cpp encode.h
	$(CC) -fpic -O2 -DCOMPILE_DL_FIRST_MODULE=1 $(INCLUDE) -c encode.cpp

clean:
	rm -fr *.so *.o

install: anyvalue.so
	cp -fp anyvalue.so $(PHP_EXT_HOME)
