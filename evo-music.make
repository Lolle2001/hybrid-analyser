CXX = g++
CXXFLAGS = -std=c++17 -fopenmp

BUILDDIR = build-evo-music
SRCDIR1 = src/evolution-music
SRCS1 = $(wildcard $(SRCDIR1)/*.cpp)
OBJS1 = $(patsubst $(SRCDIR1)/%.cpp,$(BUILDDIR)/%.o,$(SRCS1))

# SRCS = $(SRCS1) src/HistogramMap2D.cpp

# SRCS = src/Main.cpp
# OBJS = build/Main.o

TARGET = evo-music

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS1) $(OBJS2)
	$(CXX) $(CXXFLAGS) $(OBJS1) $(OBJS2) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR1)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# $(BUILDDIR)/%.o: $(SRCDIR2)/%.cpp
# 	@mkdir -p $(BUILDDIR)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)
