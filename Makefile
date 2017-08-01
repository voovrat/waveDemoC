CC=g++
FAST= -Ofast -ffast-math -march=native
DEBUG= -O0 -g 
OPTS=$(FAST)

CFLAGS= $(OPTS) -c  --std=c++11
LFLAGS= $(OPTS) -flto -lfltk -lpthread -lX11 --std=c++11

BASIC_HEADERS = view.h  \
		calculator.h    \
		window.h        \
		shared_object.h 

BASIC_OBJ = window.o

GRAPH_HEADERS = graphics.h 	fl_graphics.h

GRAPH_OBJ = graphics.o fl_graphics.o

MY_HEADERS =  mymodel.h \
		mysettings.h    \
		myview.h        \
		mycalculator.h  \
		mywindow.h    

MY_OBJ = myview.o       \
	mycalculator.o \
	mysettings.o   \
	mymodel.o      \
	mywindow.o


OBJ=maxwell.o      \
	pane.o         \
	vector_field.o \
	P3.o           \
	$(BASIC_OBJ)   \
	$(MY_OBJ)      \
	$(GRAPH_OBJ)

HEADERS= $(BASIC_HEADERS) \
		$(GRAPH_HEADERS)  \
		$(MY_HEADERS)     \
		maxwell.h         \
		pane.h            \
		P3.h              \
		vector_field.h  

 

ame: main.o 
	$(CC) -o ame main.o $(OBJ) $(LFLAGS)

clean:
	rm -f *.gch *.o

main.o: main.cpp $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) main.cpp 

myview.o: view.h mymodel.o mysettings.o pane.o fl_graphics.o myview.cpp myview.h 
	$(CC) $(CFLAGS) myview.cpp

mycalculator.o: mycalculator.cpp mycalculator.h maxwell.o 
	$(CC) $(CFLAGS) mycalculator.cpp 

mymodel.o: maxwell.o mymodel.h mymodel.cpp
	$(CC) $(CFLAGS) mymodel.cpp

mysettings.o: mysettings.h mysettings.cpp
	$(CC) $(CFLAGS) mysettings.cpp

pane.o: graphics.o vector_field.o pane.cpp pane.h
	$(CC) $(CFLAGS) pane.cpp

vector_field.o: vectorN.h P3.h vector_field.h vector_field.cpp
	$(CC) $(CFLAGS) vector_field.cpp

fl_graphics.o: graphics.o fl_graphics.cpp fl_graphics.h
	$(CC) $(CFLAGS) fl_graphics.cpp

graphics.o: graphics.cpp graphics.h
	$(CC) $(CFLAGS) graphics.cpp

maxwell.o: vector_field.o maxwell.cpp maxwell.h
	$(CC) $(CFLAGS) maxwell.cpp

P3.o: P3.h P3.cpp
	$(CC) $(CFLAGS) P3.cpp

mywindow.o: mywindow.h mywindow.cpp
	$(CC) $(CFLAGS) mywindow.cpp

window.o: window.h window.cpp
	$(CC) $(CFLAGS) window.cpp
