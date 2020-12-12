CC = gcc
CC_FLAGS = -pthread
AR = ar
RM = rm -rf

object_file = thread_pool.o logger.o

test: test.o ctool.a
	$(CC) $(CC_FLAGS) -g -o $@ $^

test.o: test.c
	$(CC) -c -o $@ $<

ctool.a: $(object_file)
	$(AR) -r $@ $^

thread_pool.o: thread_pool.c thread_pool.h
	$(CC) -c -o $@ $<

logger.o: logger.c logger.h
	$(CC) -c -o $@ $<

clean:
	$(RM) *.a *.o test