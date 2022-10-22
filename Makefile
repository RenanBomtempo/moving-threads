CC = gcc
SRC_FILES =  $(filter-out src/main.c, $(wildcard  src/*.c))
OBJ_FILES =  $(SRC_FILES:.c=.o)

DEBUG_OUT = ex1-debug
RELEASE_OUT = ex1

all: build 
build: release
clean: clean-objects clean-binaries

release: $(OBJ_FILES)
	$(info ========= moving-threads (release) =========)	
	$(CC) src/main.c $(OBJ_FILES) -o ex1 

debug: $(OBJ_FILES)
	$(info ========= moving-threads (debug) =========)
	$(CC) src/main.c $(OBJ_FILES) -D DEBUG -o ex1-debug

%.o: %.c
	$(CC) -c $< -o $@


clean-objects:
	rm src/*.o

clean-binaries:
	rm $(DEBUG_OUT) $(RELEASE_OUT)
