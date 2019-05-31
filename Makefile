TARGET=xbeeprom
OBJECTS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

xbeeprom: $(OBJECTS)
	g++ -o $@ $^

%.o: %.cpp
	g++ -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
