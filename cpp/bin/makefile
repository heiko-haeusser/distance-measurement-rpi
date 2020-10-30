PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = ../src/distance-measurement-rpi.o\
../src/Gpio_Manager.o\
../src/UltrasonicSensor.o\
../src/PDC.o\
../src/Custom_Gpi.o\
../src/Custom_Gpo.o\
../src/Custom_Gpio.o\


BUILD_MODE = run

CFLAGS = -std=c++14\
-O2\
-Wall
LDFLAGS = 


all:	distance-measurement-rpi

distance-measurement-rpi:	$(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr gpio_test $(OBJS)
