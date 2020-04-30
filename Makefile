PROJDIR = .
SRCDIR  = $(PROJDIR)/src

SRC_FILES = $(shell find $(PROJDIR) -type f -name "*.cpp")
OBJ_FILES = $(patsubst %.cpp, %.o, $(SRC_FILES))

.PHONY: all clean run

WARNINGS = -Wall -Wextra

CPPFLAGS = -std=c++17 -O0 -g $(WARNINGS) -I$(SRCDIR)

CC = g++
EXE = scheduler

all: $(EXE)

$(EXE): $(OBJ_FILES)
	$(CC) -o $(EXE) $(OBJ_FILES)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(EXE)

