CC = g++
CFLAGS = -g -O3

HDRS = p4.h crawl.h
SRCS = crawl281.cpp
OBJS = $(patsubst %.cpp, %.o, $(SRCS) $(HDRS))

crawl281:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)
$.o: $.cpp $(HDRS)
	g$(CC) $(CFLAGS) -c &<

.PHONY:clean
clean:	
	rm -rf *.o *~ *core* crawl281
