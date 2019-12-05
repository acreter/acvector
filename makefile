CC := cc
CFLAGS := -O2 -Wall -Wextra
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
	rm -f $(wildcard $(SRC)/*.o)

.PHONY: all clean
