#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <opencv2/opencv.hpp>
#include "DisjointSet.h"

using namespace std;
using namespace cv;

struct Edge {
    int a, b;
    float weight;

    bool operator<(const Edge &other) {
        return weight < other.weight;
    }
};

float diff(const Mat &image, int x1, int y1, int x2, int y2);

vector <Edge> build_graph(const Mat &image);

DisjointSet segment_graph(int num_vertices, vector <Edge> &edges, float c);

#endif // GRAPH_H_INCLUDED
