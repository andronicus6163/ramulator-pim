# C compiler
CC = g++
ICC = gcc #icc
CC_FLAGS = -g -fopenmp -O2

all: tc tc_offload

tc: tc.cpp 
	$(CC) $(CC_FLAGS) tc.cpp -o tc 

tc_offload: tc.cpp
	$(CC) $(CC_FLAGS) -DOMP_OFFLOAD tc.cpp -o tc_offload

clean:
	rm -f tc tc_offload result.txt
