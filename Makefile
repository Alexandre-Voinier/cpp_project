OBJS = src/animal.cpp src/sheep.cpp src/wolf.cpp src/clean.cpp src/init.cpp src/application.cpp src/main.cpp 

OBJ_NAME = project_sdl

all: $(OBJS)
	g++ $(OBJS) -w -lSDL2 -lSDL2_image -o $(OBJ_NAME)

clean: 
	$(RM) $(OBJ_NAME)
