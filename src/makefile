#the makefile file of Auto_aim

object:main.o Control_Motor.o Color_Capture.o parameter.o\ 		Initialzation.o

Auto_aim:$(object)
	g++ `pkg-config opencv --libs --cflags opencv` -o Auto_aim \ $(object)

main.o:include.h
	#g++ -c main.cpp

parameter.o:parameter.h

Control_Motor.o:Control_Motor.h

Color_Capture.o:Color_Capture.h parameter.h

Initialization.o:Initialization.h

.PHONY:clean
clean:
	-rm Auto_aim $(object)
		
