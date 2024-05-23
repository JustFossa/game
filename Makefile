#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp src/map.cpp src/player.cpp src/utils.cpp src/map.h src/player.h src/utils.h src/item.h src/item.cpp src/animation.h src/animation.cpp src/json.h src/json.cpp src/healthbar.cpp src/healthbar.h src/hud.cpp src/hud.h src/inventory.h src/inventory.cpp src/slot.h src/slot.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -IC:\MinGW\include\SDL2 -LC:\MinGW\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2_ttf  -lSDL2_image -lSDL2 -o $(OBJ_NAME)
