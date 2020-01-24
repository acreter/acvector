CC := cc
CFLAGS := -O2 -Wall -Wextra -Winline
SRC := src/
TEST := test/
BUILD := build/
ARCHIVE := ar
AFLAGS := rcs

NAME := acvector

all: $(NAME)

$(NAME): $(patsubst $(SRC)%.c,$(SRC)%.o, $(wildcard $(SRC)/*.c))
	mkdir -p $(BUILD)
	$(ARCHIVE) $(AFLAGS) $(BUILD)/lib$@.a $^

$(SRC)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

test: all $(TEST)/test.o
	$(CC) -o $(TEST)/test -L$(BUILD) $(TEST)/test.o -l$(NAME)
	$(TEST)/test

$(TEST)/test.o: $(TEST)/test.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(BUILD)
	rm -f $(wildcard $(SRC)/*.o)
	rm -f $(wildcard $(TEST)/*.o)

.PHONY: all clean test
