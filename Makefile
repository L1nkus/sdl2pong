OBJS = game.cpp
OBJS_NAMES = game
FLAGS = -w -lSDL2 -lSDL2_image
MINGW_FLAGS = -lmingw32 -lSDL2main -static-libstdc++ -static-libgcc

all : $(OBJS)
	g++ $(OBJS) $(FLAGS) -o $(OBJS_NAMES)

mingw : $(OBJS)
	x86_64-w64-mingw32-c++ $(OBJS) $(MINGW_FLAGS) $(FLAGS) -o $(OBJS_NAMES).exe
