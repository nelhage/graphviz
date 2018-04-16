/*
 * clang-6.0 -ggdb3 -rpath /tmp/graphviz/lib/ -L /tmp/graphviz/lib/ -I /tmp/graphviz/include/graphviz/ -fsanitize=fuzzer,address -lgvc -lcgraph -lcdt fuzzmain.c
 */
#include <gvc.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    FILE *fp = fmemopen((void*)Data, Size, "r");
    if (fp == NULL) {
        return 0;
    }
    GVC_t *gvc = gvContext();
    Agraph_t* G = agread(fp, 0);
    fclose(fp);
    if (G != NULL) {
        agclose(G);
    }
    gvFreeContext(gvc);
    return 0;
}
