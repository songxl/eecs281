CC = g++
CFLAGS = -g -O3

HDRS = p3.h
SRCS = mediabrowser.cpp
OBJS = $(patsubst %.cpp, %.o, $(SRCS) $(HDRS))

sort281:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)
$.o: $.cpp $(HDRS)
	g$(CC) $(CFLAGS) -c &<

.PHONY:clean
clean:	
	rm -rf *.o *~ *core* sort281
