CC := clang++ -std=c++11 -stdlib=libc++

CPP_FILES := $(wildcard *.cpp)

bitdoku:
	$(CC) $(CPP_FILES)
