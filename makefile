build:
	gcc \
	-Wfatal-errors \
	-std=c99 \
	./src/components/* \
	./src/core/* \
	./src/helpers/* \
	./src/objects/* \
	./src/main.c \
	-I"src" \
	-I"C:\libsdl\include" \
	-L"C:\libsdl\lib" \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_ttf \
	-lSDL2_image \
	-lSDL2_mixer \
	-o build

run:
	build.exe