if [ $# -eq 0 ];
	then 
		gcc -no-pie -ggdb -I/usr/include -I/usr/include/freetype2 -I./include -o exe kiss_sdl/kiss_general.c kiss_sdl/kiss_posix.c kiss_sdl/kiss_widgets.c kiss_sdl/kiss_draw.c game.c -L/usr/lib -L/usr/lib/x86_64-linux-gnu -lGLEW -lglfw -ldl -lm -lGL -lGLU -lX11 -lpthread -lfreetype -lstb -lSDL2 -lSDL2_image -lSDL2_ttf -DRESDIR=\"kiss_sdl/\";
fi
if [ $# -eq 1 ];
	then 
		gcc -no-pie -ggdb -I/usr/include -I/usr/include/freetype2 -I./include -D$1 -o exe kiss_sdl/kiss_general.c kiss_sdl/kiss_posix.c kiss_sdl/kiss_widgets.c kiss_sdl/kiss_draw.c game.c -L/usr/lib -L/usr/lib/x86_64-linux-gnu -lGLEW -lglfw -ldl -lm -lGL -lGLU -lX11 -lpthread -lfreetype -lstb -lSDL2 -lSDL2_image -lSDL2_ttf -DRESDIR=\"kiss_sdl/\";
fi
