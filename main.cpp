#include <vector>
#include <boost/thread.hpp>
#include "visualize_evidence.h"

/**
    main
*/
int main(int argc, char **argv) {
    // Set the coarsness of the evidence grid
    int GRANULARITY = 40;
    // Create an evidence grid object
    EvidenceGrid grid = EvidenceGrid(GRANULARITY);
    // Initialize the Robots local evidence grid
    std::vector< std::vector<float> > v;
    v.resize(GRANULARITY);
    for (int i=0; i < v.size(); i++) {
        v[i].resize(GRANULARITY);
        for (int j=0; j < v.size(); j++) {
            v[i][j] = 0.5f;
        }
    }
    // Package arguments for UI
    ARG_STRUCT GFX_ARGS;
    GFX_ARGS.argc = argc; 
    GFX_ARGS.argv = argv; 
    GFX_ARGS.GRANULARITY = GRANULARITY; 
    GFX_ARGS.grid = &grid;
    // Dispatch a thread to run the GUI
    boost::thread spin_thread(&dispatch_gfx);
}
