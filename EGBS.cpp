#include <opencv2/opencv.hpp>
#include "EGBS.h"

EGBS::EGBS() {

}

void EGBS::applySegmentation(cv::Mat &image, int c, int min_size) {
    int height = image.rows;
    int width = image.cols;

    cv::Mat smoothed(image);
    smoothed.convertTo(smoothed, CV_32FC3);
    GaussianBlur(smoothed, smoothed, cv::Size(5, 5), 0.5);

    std::vector <Edge> edges = build_graph(smoothed);
    DisjointSet forest = segment_graph(height * width, edges, c);

    // process small components
    for (Edge &edge: edges) {
        int a = forest.find(edge.a);
        int b = forest.find(edge.b);

        if ((a != b) && ((forest.size(a) < min_size) || (forest.size(b) < min_size))) {
            forest.merge(a, b);
        }
    }

    recolor(image, forest);
}

void EGBS::recolor(cv::Mat &image, DisjointSet &forest) {
    int height = image.rows;
    int width = image.cols;

    // calculate average colors for components
    std::map<int, cv::Vec3f> colors;
    std::map<int, int> counts;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int comp = forest.find(y * width + x);
            colors[comp] += image.at<cv::Vec3b>(y, x);
            counts[comp]++;
        }
    }

    for (auto itr : colors)
        colors[itr.first] /= counts[itr.first];

    // apply average colors
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int comp = forest.find(y * width + x);
            image.at<cv::Vec3b>(y, x) = colors[comp];
        }
    }
}
