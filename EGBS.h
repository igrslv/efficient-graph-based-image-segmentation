#ifndef EGBS_H
#define EGBS_H

#include <opencv2/opencv.hpp>
#include "graph.h"
#include "DisjointSet.h"

using namespace std;
using namespace cv;

class EGBS {
public:
    EGBS();

    void applySegmentation(Mat &image, int c, int min_size);

private:
    void recolor(Mat &image, DisjointSet &forest);
};

#endif // EGBS_H
