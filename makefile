CC := gcc
CFLAGS := -O2
SRC := src/
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

clean:
	rm -rf $(BUILD)
	rm $(wildcard $(SRC)/*.o)

.PHONY: all clean
