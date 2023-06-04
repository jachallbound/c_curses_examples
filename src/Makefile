CC=gcc
STDFLAGS=-std=c99
WFLAGS=-Wall
CFLAGS=
LDFLAGS=-lm -lcurses
PROGRAM=main
PFLAGS=-pg -g # Profiler flags
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

all: $(OBJ)
	$(CC) $(LDFLAGS) -o $(PROGRAM) $(OBJ)
# $(CC) $(WFLAGS) $(STDFLAGS) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJ) $(PFLAGS)

%.o:%.c
	$(CC) $(WFLAGS) $(STDFLAGS) $(CFLAGS) -c $< $(PFLAGS)

clean:
	rm -fv *.o $(PROGRAM)

# CC=gcc
# LIB_PATH=src
# STDFLAGS=-std=c99
# WFLAGS=-Wall
# CFLAGS=-I$(LIB_PATH)
# LDFLAGS=-lm -lcurses
# PFLAGS=-g -fPIC
# SRC=$(wildcard $(LIB_PATH)/*.c)
# OBJ=$(patsubst %.c, %.o, $(SRC))
# PROGRAM=main
# SO=libcitt.so

# all: $(OBJ)

# $(LIB_PATH)/%.o : $(LIB_PATH)/%.c
# 	$(CC) $(STDFLAGS) $(WFLAGS) $(CFLAGS) -c $< $(LDFLAGS) -o $@ $(PFLAGS)

# shared:
# 	$(info ########## Creating libcitt.so, Then deleting individual .o files.)
# 	$(CC) -shared -o $(SO) $(OBJ)	
# 	rm -fv $(LIB_PATH)/*.o

# game:
# 	$(info ########## Creating `main` executable.)
# 	$(CC) $(LDFLAGS) -o $(PROGRAM) $(SO)

# clean:
#		rm -fv $(LIB_PATH)/*.o *.so


# CC=gcc
# LIB_PATH=./src
# STDFLAGS=-std=c99
# WFLAGS=-Wall
# CFLAGS=-I$(LIB_PATH)
# LDFLAGS=-lm -lcurses
# OBJ=main.o
# PROGRAM=main
# PFLAGS=-g #-pg # Profiler flags
# SRC=$(wildcard $(LIB_PATH)/*.c)
# OBJ=$(patsubst %.c, %.o, $(SRC))

# all: $(OBJ)
# 	$(CC) $(LDFLAGS) -o $(PROGRAM) $(OBJ)
# # $(CC) $(WFLAGS) $(STDFLAGS) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJ) $(PFLAGS)

# %.o:%.c
# 	$(CC) $(WFLAGS) $(STDFLAGS) $(CFLAGS) -c $< $(PFLAGS)

# clean:
# 	rm -fv *.o $(PROGRAM)
