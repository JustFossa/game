#OBJS specifies which files to compile as part of the project
OBJS = main.cpp map.cpp player.cpp utils.cpp map.h player.h utils.h

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -IC:\MinGW\include\SDL2 -LC:\MinGW\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2_ttf  -lSDL2_image -lSDL2 -o $(OBJ_NAME)
