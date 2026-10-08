CXX      = g++
CXXFLAGS = -std=c++17 -O2
SRC      = $(wildcard src/*.cpp)

app: $(SRC) src/*.h
	$(CXX) $(CXXFLAGS) -o app $(SRC)

test: app
	./app < tests/input.txt > tests/actual_output.txt
	diff tests/expected_output.txt tests/actual_output.txt && echo "Тест пройден"

clean:
	rm -f app tests/actual_output.txt
