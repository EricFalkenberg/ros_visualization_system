#include <vector>

class EvidenceGrid {
    float * robot_info;
    float ** grid;
    int size;
    public:
        EvidenceGrid(int g);
        void update_grid(std::vector< std::vector<float> > external_grid, std::vector<float> robot_info);
        void retrieve_grid(std::vector< std::vector<float> > *external_grid, std::vector<float> *robot_info);
};
