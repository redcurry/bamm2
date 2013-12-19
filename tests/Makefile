CC = clang++
CCFLAGS = -std=c++11 -stdlib=libc++

src_dir = ~/projects/bamm2/source/
gtest_include_dir = ~/gtest-1.7.0/include/
gtest_src_dir = ~/gtest-1.7.0/src/

test_files = \
	UniformProposerTest.cc

src_files = \
	$(src_dir)/UniformProposer.cc \
	$(src_dir)/Random.cc

test-all: $(test_files) $(src_files)
	$(CC) $(CCFLAGS) -I $(src_dir) -I $(gtest_include_dir) \
		-o test-all $(test_files) $(src_files) \
		$(gtest_src_dir)/gtest-all.o $(gtest_src_dir)/gtest_main.o

clean:
	rm test-all
