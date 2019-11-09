all:
	g++ -g `pkg-config --cflags opencv4` projet_base.cpp `pkg-config --libs opencv4` -pthread

opti:
	g++ -g `pkg-config --cflags opencv4` projet_base.cpp `pkg-config --libs opencv4` -pthread -Ofast

proto:
	g++ -g test_median.cpp -o test_median.out

finite_sobel_opt:
	g++ -g `pkg-config --cflags opencv4` sobel_finite.cpp `pkg-config --libs opencv4` -Ofast -pthread
valgrind: finite_sobel_opt
	./script_prof.sh a.out vg_logs
