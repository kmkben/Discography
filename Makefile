SOURCES  =  main.cpp disco_utils.cpp
OBJECTS  =  $(SOURCES:.cpp=.o)
TARGET   =  disco
#LIBS     =  $(shell sdl-config --libs) -lGL -lGLU -lglut -lm

all: $(OBJECTS)
	g++ -std=c++17 -o $(TARGET) $(OBJECTS) 


%o: %cpp
	g++ -std=c++17 -o $@ -c $<


x: all
	./$(TARGET)


clean: 
	rm -rf $(OBJECTS)


superclean: clean
	rm -rf $(TARGET)

