CC=g++
CFLAGS=-Wall -g -c
CPPFLAGS=
RM=rm
TARGET=versioninfo
LIBS=

objects = versioninfo.o

all: versioninfo

versioninfo: $(objects)
	$(CC) -o $(TARGET) $(objects) $(LIBS) $(DEBUGLIBS)

clean:
	$(RM) $(objects)
