CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -fsanitize=address
TARGET = main
SRCS = DoubleLinkedListMain.cpp	DoubleLinkedList.cpp
OBJS = $(SRCS:.cpp=.o)
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: 
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) 