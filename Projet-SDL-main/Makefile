CC = g++
CFLAGS = -Wall #-Wextra -Werror
LIBS = -lSDL2main -lSDL2_image -lSDL2

OBJS = main.o Project_SDL1.o application.o ground.o interacting_object.o rendered_object.o sheep.o wolf.o playable_character.o shepherd_dog.o

TESTS_OBJS = tests/ground_test.o

game: ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBS}

debug: ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBS} -g

tests: ${TESTS_OBJS} ground.o
	${CC} ${CFLAGS} -o debug $^ ${LIBS} -g

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) -g

clean:
	${RM} ${OBJS} ${TESTS_OBJS} game debug

.PHONY: clean
