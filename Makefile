# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Source files
SRCS = main.cpp Load.cpp Save.cpp Library.cpp Book.cpp User.cpp Account.cpp utils.cpp Librarian.cpp Student.cpp Faculty.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output binary name
TARGET = LibraryApp

# Build rule
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove object files and binary
clean:
	rm -f *.o $(TARGET)

