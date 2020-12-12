main: main.o queue.a
# 	cc -o $@ $<

main.o: main.c
# 	cc -c -o $@ $<

queue.a: queue.o
	ar    -r $@ $<

queue.o: queue.c queue.h ../types.h
# 	cc -c -o $@ $<

clean:
	rm -rf *.a *.o main && echo 'clear success'