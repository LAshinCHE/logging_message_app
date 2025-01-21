CC = g++
CFLAGS = -Wall -Wextra -fPIC
LDFLAGS = -shared

LIBRARY_NAME = liblog_library.so

SRC_FILES = log_library.cpp record.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)

INCLUDE_DIRS = -I.

all: $(LIBRARY_NAME)

$(LIBRARY_NAME): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(LIBRARY_NAME)

.PHONY: all clean
