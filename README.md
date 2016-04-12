# ROS Visualization System

A GUI written in C++ for use in dense evidence grid mapping in Robotics. 
I specifically developed this with ROS in mind though it should be fairly universal.

This visualization system depends on OpenGL and GLUT.


## Examples

![Kinect Map](http://i.imgur.com/sxctDoA.png)
![Sonar Map](http://i.imgur.com/6x04bOK.png)
![Kinect+Sonar Map](http://i.imgur.com/kLLjfSb.png)
![Sonar Real Map](http://i.imgur.com/7FfwHgf.png)

## Installation & Usage

Depends what framework you are working with.

For ROS specifically, the following is known to work.

```c++
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
    GFX_ARGS.argc = argc; 
    GFX_ARGS.argv = argv; 
    GFX_ARGS.GRANULARITY = GRANULARITY; 
    GFX_ARGS.grid = &grid;
    // Dispatch a thread to run the GUI
    boost::thread spin_thread(&dispatch_gfx);
}
```
Using the visualization system is as simple as including visualize_evidence.h,
initializing GFX_ARGS, and running dispatch_gfx in a thread via your preferred means
of thread creation.

## Contributing

If you would like to contribute follow these steps and i'll review the
request at the earliest convenience.

1. Fork it
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request

## License

This project is under the MIT License, more info can be found on this under the file LICENSE
