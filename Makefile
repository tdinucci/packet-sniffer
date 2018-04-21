src = $(wildcard *.cpp) \
	$(wildcard link/*.cpp) \
	$(wildcard linux/*.cpp) \
	$(wildcard network/*.cpp) \
	$(wildcard transport/*.cpp) \
	$(wildcard windows/*.cpp)

obj = $(src:.cpp=.o)

CXXFLAGS = -Wall -std=c++14
CXXFLAGS_DEBUG = $(CXXFLAGS) -g

sniff: 
	$(CXX) $(CXXFLAGS) $(src) -o $@

sniff_debug: 
	$(CXX) $(CXXFLAGS_DEBUG) $(src) -o $@

.PHONY: clean
clean:
	rm -f $(obj) sniff sniff_debug