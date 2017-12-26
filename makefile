# Lenny Harrrison
# Program4 Makefile

OBJECTS = main.o Tree.o
HEADERS = Tree.h 

myEditor: $(OBJECTS)
	g++ $^ -o CS216PA4

#Define a rule
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

#Clean
clean:
	rm -f *.o CS216PA4
