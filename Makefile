#################################
#	   VARIABLES		#
#################################

INCLUDE_DIR = ./includes/

CPP_FLAGS = -std=c++11 -I$(INCLUDE_DIR)

EXEC_NAME = vvm

OBJS = parser.o		\
main.o				\
runtime/executer.o	\
runtime/typecheck.o	\

ifeq ($(OS), Windows_NT)
	EXEC_SUFFIX = .exe
endif

#################################
#	COMPILATION RULES	#
#################################

all: $(OBJS)
	g++ $(OBJS) -o $(EXEC_NAME) $(CPP_FLAGS)

%.o: %.cpp
	g++ -c -o $@ $< $(CPP_FLAGS)

#Cleaning rules
clean: clean_tmp
		rm -f vvm$(EXEC_SUFFIX)

clean_tmp:
	rm -rf *~ *.o