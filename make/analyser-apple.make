CXX = clang++

OMP_PATH = /opt/homebrew/opt/libomp
JSON_PATH = /opt/homebrew/opt/nlohmann-json


CXXFLAGS = -std=c++17 -Xpreprocessor -fopenmp
LDFLAGS = -L$(OMP_PATH)/lib -lomp -lfmt
INCLUDE = -I$(OMP_PATH)/include -I$(JSON_PATH)/include -I$(CPP_LIBS)/argparse/include -I$(CPP_LIBS)/fmt/include

BUILDDIR = build/build-analyser
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

TARGET = analyser

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)

