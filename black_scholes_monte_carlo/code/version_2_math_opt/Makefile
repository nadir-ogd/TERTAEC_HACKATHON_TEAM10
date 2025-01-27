CXX = g++

CXXFLAGS += -O3 -g -I/tools/openblas/gnu/14.2.0/include
LDFLAGS  += -L/tools/acfl/24.10/gcc-14.2.0_AmazonLinux-2/lib64 \
            -Wl,-rpath=/tools/acfl/24.10/gcc-14.2.0_AmazonLinux-2/lib64 \
            -L/tools/forge/lib -lmap-golem -Wl,-rpath=/tools/forge/lib \
            /tools/openblas/gnu/14.2.0/lib/libopenblas.so \
            -Wl,-rpath=/tools/openblas/gnu/14.2.0/lib


SRC = BSM_v2.cxx
OUT = BSM

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)
	

run: $(OUT)
	./$(OUT) $(ARGS)

clean:
	rm -f $(OUT)

.PHONY: all clean run
