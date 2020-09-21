PROJECT_SRC = ./src/main.cpp ./src/fnv.cpp src/hashing.cpp src/bloomfilter.cpp src/helper.cpp src/sdhash.cpp


NAME=mrsh_net

all: debug

debug: ${PROJECT_SRC} ${PROJECT_HDR}
	g++ -w -ggdb  -fpermissive -D_DEFAULT_SOURCE -o ${NAME} ${PROJECT_SRC} -lm -lcrypto -lssl -I./boost_1_73_0/boost -L./boost_1_73_0/stage/lib   -lboost_system -lboost_filesystem

mrsh: ${PROJECT_SRC} ${PROJECT_HDR}
	g++  -w -O3 -fpermissive -D_DEFAULT_SOURCE -o ${NAME} ${PROJECT_SRC} -lm -lcrypto -lssl -I./boost_1_73_0/boost -L./boost_1_73_0/stage/lib -lboost_system -lboost_filesystem


#pg for profiler, gprof. 

clean :  
	rm -f ${NAME} *.o 
	

#for DT_DIR feature to work, need to have the _BSD_SOURCE  feature test macro defined. THese are not standard, and GCC does not define the macro when compiling for C99
# -lm: -l means link a library and -m means a math library. Without this option 


