#ifndef EGBS_H
#define EGBS_H

#include <opencv2/opencv.hpp>
#include "graph.h"
#include "DisjointSet.h"

class EGBS {
public:
    EGBS();

    void applySegmentation(cv::Mat &image, int c, int min_size);

private:
    void recolor(cv::Mat &image, DisjointSet &forest);
};

#endif // EGBS_H
