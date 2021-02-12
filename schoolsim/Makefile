SRC = $(wildcard *.cpp)

OBJS = $(SRC:.cpp=.o)

OUT = schoolsim

CC	= g++

$(OUT): $(OBJS)
	$(CC) $^ -o $@
	
clean:
	rm -f $(OBJS) $(OUT)

run:	
	./$(OUT) 15 50 50 50