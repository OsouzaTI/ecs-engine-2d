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

clear:
	del *.exe && del tempCodeRunnerFile.py