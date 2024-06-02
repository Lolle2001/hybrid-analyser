CXX = g++ 
CXXFLAGS = -std=c++17 -fopenmp # -Wall -Wextra -Wpedantic -Wno-reorder

BUILDDIR = build/build-hybridp
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# SRCS = src/Main.cpp
# OBJS = build/Main.o

TARGET = hybridp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)
