SRC= ${wildcard  src/*.cpp}
HDR= ${wildcard  src/*.hpp}
EXE=jishoRequest

CXX=clang++
CXXFLAGS+=-Wall -Wextra -g -O1 -std=c++17 -march=native
INCLUDE+= -I/usr/include/unicode
LDFLAGS= -lcurl -licuio -licui18n -licuuc -licudata -lpthread

OBJDIR=build
OBJ= $(patsubst %.cpp, $(OBJDIR)/%.o,$(notdir $(SRC)))

all: $(OBJ)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDE)  -o $@ -c $<
check:
	@clang-check $(SRC)
Format:
	@clang-format -i -style=file $(SRC) $(HDR)
clean:
	rm -rf build $(EXE)
