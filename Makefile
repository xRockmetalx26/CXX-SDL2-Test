CPP_FILES       := $(wildcard src/*.cpp)
O_FILES         := $(subst .cpp,.o,$(CPP_FILES))
COMPILED_FLAGS  := -std=c++17 -Wall -Wextra -O3

# -I"your-directory" add include directory (files .h) (HEADERS)
INCLUDE_DIRECTORIES  := -Iinclude 

# -L"your-directory" add lib directory (files .a .dll) (LIBRARIES)
LIB_DIRECTORIES      := -Llib

# -l"filename without lib prefix and .a extension" add libraries to use (libfile.a / libfile.dll)
LIB_FILES            := -lSDL2main -lSDL2 -lSDL2.dll -lSDL2_image -lSDL2_image.dll 

# .exe File
app: $(O_FILES)
	g++ $^ -o $@ $(LIB_DIRECTORIES) $(LIB_FILES)

# .o Files
%.o: %.cpp
	g++ -c $^ -o $@ $(INCLUDE_DIRECTORIES) $(COMPILED_FLAGS)