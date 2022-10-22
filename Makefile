CC = gcc
SRC_FILES =  $(filter-out src/main.c, $(wildcard  src/*.c))
OBJ_FILES =  $(SRC_FILES:.c=.o)
CCFLAGS = 
DEBUG_OUT = ex1-debug
RELEASE_OUT = ex1

all: build 
build: clean release
clean: clean-objects clean-binaries

debug: CCFLAGS+=-DDEBUG -g
release: CCFLAGS+=-O2

release: $(OBJ_FILES)
	$(info ========= moving-threads (release) =========)	
	$(CC) src/main.c $(OBJ_FILES) -o ex1 $(CCFLAGS)

debug:  $(OBJ_FILES)
	$(info ========= moving-threads (debug) =========)
	$(CC) src/main.c $(OBJ_FILES) -o ex1-debug $(CCFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CCFLAGS)


clean-objects:
	rm -f src/*.o

clean-binaries:
	rm -f $(DEBUG_OUT) $(RELEASE_OUT)
