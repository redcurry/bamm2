CC = clang++
CCFLAGS = -std=c++11 -stdlib=libc++

src_dir = ~/projects/mcmc-test/
gtest_include_dir = ~/gtest-1.7.0/include/
gtest_src_dir = ~/gtest-1.7.0/src/

test_files = \
	EventTest.cc \
	EventMoverTest.cc \
	TreeModelTest.cc \
	TreeModelProposalTest.cc

src_files = \
	$(src_dir)/Event.cc \
	$(src_dir)/Node.cc \
	$(src_dir)/EventMover.cc \
	$(src_dir)/Random.cc \
	$(src_dir)/Tree.cc \
	$(src_dir)/TreeModel.cc \
	$(src_dir)/ModelProposal.cc \
	$(src_dir)/TreeModelProposal.cc

test-all: $(test_files) $(src_files)
	$(CC) $(CCFLAGS) -I $(src_dir) -I $(gtest_include_dir) \
		-o test-all $(test_files) $(src_files) \
		$(gtest_src_dir)/gtest-all.o $(gtest_src_dir)/gtest_main.o

clean:
	rm test-all
