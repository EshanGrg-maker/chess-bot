LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDE = -I src/include -I Stuff

# Recursive wildcard function
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,Stuff/,*.cpp)

all:
	g++ $(INCLUDE) $(SRC) main.cpp -L src/lib $(LIBS) -o main

