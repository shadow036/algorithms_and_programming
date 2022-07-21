CC     = gcc
RM     = rm -f
OBJS   = main.o

LIBS   =
CFLAGS =

.PHONY: bin/Release/arrayVisit.exe clean clean-after

all: bin/Release/arrayVisit.exe

clean:
	$(RM) $(OBJS) bin/Release/arrayVisit.exe

clean-after:
	$(RM) $(OBJS)

bin/Release/arrayVisit.exe: $(OBJS)
	$(CC) -O2 -s -Wall -o $@ $(OBJS) $(LIBS)

main.o: main.c
	$(CC) -O2 -s -Wall -c $< -o $@ $(CFLAGS)

