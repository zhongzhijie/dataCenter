.PHONE : all

all : liblinklist.so libcfgcenter.so

liblinklist.so : linkList.o
	gcc -Wall -fPIC -shared $^ -o $@

linkList.o : linkList.c
	gcc -c $<

libcfgcenter.so : cfgcenter.o
	gcc -Wall -fPIC -shared -llinklist $^ -o $@

cfgcenter.o : cfgcenter.c
	gcc -c $<

clean:
	rm -f *.so *.o
