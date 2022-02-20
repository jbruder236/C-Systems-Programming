all: strupr

strupr : strupr.o upper.o
	cc -g -o $@ $^

%.o : %.c
	cc -c $<

clean:
	rm -rf *.o *~ strupr
