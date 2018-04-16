/*
 * mkdir build
 * cd build
 * env CC=clang-6.0 CXX=clang++-6.0 CFLAGS=-fsanitize=fuzzer-no-link,address cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/graphviz -DBUILD_SHARED_LIBS=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
 * make install
 * cd ..
 * clang-6.0 -ggdb3 -rpath /tmp/graphviz/lib/ -L /tmp/graphviz/lib/ -I /tmp/graphviz/include/graphviz/ -fsanitize=fuzzer,address -lgvc -lcgraph -lcdt fuzzmain.c
 */
#include <gvc.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    static GVC_t *gvc = NULL;
    if (gvc == NULL) {
        gvc = gvContext();
        agseterr(AGMAX);
    }
    FILE *fp = fmemopen((void*)Data, Size, "r");
    if (fp == NULL) {
        return 0;
    }
    Agraph_t* G = agread(fp, 0);
    fclose(fp);
    if (G != NULL) {
        agclose(G);
    }
    return 0;
}
