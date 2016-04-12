#include "evidence_grid.h"

void VisualizeEvidence(int argc, char **argv, int g, EvidenceGrid v);
void dispatch_gfx();
struct ARG_STRUCT {
    int argc;
    char **argv;
    int GRANULARITY;
    EvidenceGrid *grid;
};
extern ARG_STRUCT GFX_ARGS;
