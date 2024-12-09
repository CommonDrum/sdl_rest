build:
	gcc ./src/*.c `sdl2-config --libs` `sdl2-config --cflags` -lm -o rasterizer

run: 
	./rasterizer

clean:
	rm rasterizer
