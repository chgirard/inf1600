CXX = g++
INCLUDES= -I./
CXXFLAGS = -g $(INCLUDES)
SRCM= ../Article.cpp
OBJM = $(SRCM:.cpp=.o)
LINKFLAGS= -lcppunit

ArticleTests: ArticleTest.h main.cpp $(OBJM)
	$(CXX) $(CXXFLAGS) -o $@ main.cpp $(OBJM) $(LINKFLAGS) $(LINKFLAGSLOG4) $(LIBLOG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

