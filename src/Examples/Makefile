SRC_DIR=../
include $(SRC_DIR)Makefile.common

#gcc -Wall -c main.cpp
#g++ -L/usr/lib main.o -lgsl -lgslcblas -lm -o prova

%.o:%.cpp
	$(CC) -c $(CPPFLAGS) -o  $@  $^

clean:
	rm -f */*.o 
	rm -f *.o 
	rm -f $(TARGET) 
	rm -f *.a
	rm -f */*~
	rm -f *~