build:
	gcc \
	-Wfatal-errors \
	-Wl,--stack,20485760 \
	-std=c99 \
	./src/components/* \
	./src/core/* \
	./src/helpers/*.h \
	./src/helpers/*.c \
	./src/helpers/scene/* \
	./src/objects/* \
	./src/rat.h \
	./src/rat.c \
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
	-o build.exe

run:
	build.exe