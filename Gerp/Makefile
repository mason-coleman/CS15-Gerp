###
### Makefile for Gerp Project
###
### Author:  Nick Ferrari & Mason Coleman

## 
## Build up your Makefile in a similar manner as for Zap. Feel free 
## to use that Makefile to guide you! Note, you do NOT need rules for
## FSTree.o and DirNode.o as those (pre-compiled) object files are 
## provided to you.
## 
## At the end, you can delete this comment!
## 

# --- Compiler Variables ---
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 -O2

# --- Final Executable Rule ---
# This rule links all the compiled object files together to create 'gerp'
gerp: main.o Gerp.o HashTable.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -o gerp main.o Gerp.o HashTable.o FSTree.o DirNode.o

# --- Object File Compilation Rules ---
main.o: main.cpp Gerp.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Gerp.o: Gerp.cpp Gerp.h HashTable.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c Gerp.cpp

HashTable.o: HashTable.cpp HashTable.h
	$(CXX) $(CXXFLAGS) -c HashTable.cpp

processing.o: processing.cpp processing.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c processing.cpp

unit_test: unit_test_driver.o processing.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o processing.o FSTree.o DirNode.o

##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out

