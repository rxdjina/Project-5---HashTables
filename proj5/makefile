CC=gcc
CXX=g++
RM=rm -f
CXXFLAGS=-std=c++11 -Wall -pedantic
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

OBJS=$(subst .cc,.o,.x,.cpp,.hpp,$(SRCS))

all: proj5.x sproj5.x

proj5.x: proj5.o passserver.o
	$(CXX) $(CXXFLAGS) -o $@ $^

sproj5.x: sproj5.o passserver.o
	$(CXX) $(CXXFLAGS) -o $@ $^

.SUFFIXES: .x

.PHONY : clean

clean:
	$(RM) $(OBJS)

distclean: clean

%.x : %.c
	$(CC) -o $@ $<
%.x : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<