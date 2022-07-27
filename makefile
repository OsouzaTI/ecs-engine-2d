build:
	gcc \
	-Wfatal-errors \
	-std=c99 \
	./src/components/* \
	./src/core/* \
	./src/helpers/*.h \
	./src/helpers/*.c \
	./src/helpers/scene/* \
	./src/objects/* \
	./src/rato.h \
	./src/main.c \
	-I"src" \
	-I"C:\libsdl\include" \
	-L"C:\libsdl\lib" \
	-lm \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_ttf \
	-lSDL2_image \
	-lSDL2_mixer \
	-o build

run:
	./build