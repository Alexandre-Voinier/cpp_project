OBJS = src/InteractionObject.cpp src/RenderedObject.cpp src/MovingObject.cpp src/PlayableCharacter.cpp src/Shepherd.cpp src/checkPos.cpp src/Sheep.cpp src/Wolf.cpp src/ShepherdDog.cpp src/clean.cpp src/init.cpp src/Ground.cpp src/Application.cpp src/main.cpp 

OBJ_NAME = project_sdl

all: $(OBJS)
	g++ $(OBJS) -w -lSDL2 -lSDL2_image -o $(OBJ_NAME)

clean: 
	$(RM) $(OBJ_NAME)
