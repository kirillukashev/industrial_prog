#include <chrono>
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#include "lut_data.h"

#ifndef DEFAULT_MAP_PATH
#define DEFAULT_MAP_PATH "map.png"
#endif

static const int N = 100;

cv::Mat buildLut(const uint8_t* b, const uint8_t* g, const uint8_t* r) {
    cv::Mat lut(1, 256, CV_8UC3);
    for (int i = 0; i < 256; ++i)
        lut.at<cv::Vec3b>(0, i) = cv::Vec3b(b[i], g[i], r[i]);
    return lut;
}

double applyLut(const cv::Mat& src, const cv::Mat& lut, cv::Mat& dst) {
    cv::LUT(src, lut, dst);
    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i)
        cv::LUT(src, lut, dst);
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count() / N;
}

int main(int argc, char* argv[]) {
    std::string map_path = DEFAULT_MAP_PATH;
    if (argc >= 2) map_path = argv[1];

    cv::Mat input;
    if (argc >= 3) input = cv::imread(argv[2]);
    if (input.empty()) {
        input = cv::Mat(1080, 1920, CV_8UC3);
        cv::randu(input, 0, 256);
        std::cout << "Using random 1920x1080 image\n";
    }

    cv::Mat map = cv::imread(map_path);
    if (map.empty()) {
        std::cerr << "Cannot load map: " << map_path << "\n";
        return 1;
    }
    uint8_t r1[256], g1[256], b1[256];
    for (int i = 0; i < 256; ++i) {
        r1[i] = map.at<cv::Vec3b>(0, i)[2];
        g1[i] = map.at<cv::Vec3b>(1, i)[1];
        b1[i] = map.at<cv::Vec3b>(2, i)[0];
    }
    cv::Mat lut1 = buildLut(b1, g1, r1);
    cv::Mat out1;
    double t1 = applyLut(input, lut1, out1);

    cv::Mat lut2 = buildLut(LUT_B, LUT_G, LUT_R);
    cv::Mat out2;
    double t2 = applyLut(input, lut2, out2);

    std::cout << "Approach 1 (from file):  " << t1 << " ms/iter\n";
    std::cout << "Approach 2 (hardcoded):  " << t2 << " ms/iter\n";
    std::cout << "Max pixel diff: " << cv::norm(out1, out2, cv::NORM_INF) << "\n";

    cv::imwrite("output.png", out2);
    return 0;
}
