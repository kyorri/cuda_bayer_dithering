# cuda_bayer_dithering
Parallel and Distributed Algorithms project that implements the Bayer Ordered dithering algorithm in a secvential and also a parallel way using NVIDIA CUDA.

The purpose of the project is to process images using Bayer Dithering algorithm, and to benchmark the difference between a secvential algorithm and a parallel one. <br/>
The project is written using C++ and uses images in non-compressed [BMP format](https://en.wikipedia.org/wiki/BMP_file_format). <br/>
For the parallel implementation, NVIDIA CUDA will be used. <br/>

The results of the benchmark will be stored in a csv file for easy integration into Microsoft Excel or Google Sheets. <br/>
Sample results can be found in results/result#.csv. The time elapsed for the algorithm to run will be represented in milliseconds. <br/>


The machine used for running the tests:
* OS  - Windows 10
* CPU - Ryzen 5 4600H 3.0GHz, 6 cores, 12 logical processors
* RAM - 16 GB
* <b>GPU - NVIDIA GeForce GTX 1650</b>

# Documentation
The documentation of this project can be seen [here](https://docs.google.com/document/d/165euXi7qWcO-A3sKLQMDd3MpZ2kD3072c0Z6YdN7V2A/edit?usp=sharing)

# Prerequisites
* NVIDIA GPU with Tesla Arhitecture or newer
* [Visual Studio](https://visualstudio.microsoft.com/) installed with "Desktop development with C++"
* [CMake](https://cmake.org/) installed
* [NVIDIA CUDA Toolkit](https://developer.nvidia.com/cuda-toolkit) installed

# Building
1. Clone the repository using Visual Studio
2. Build using the CMakeLists.txt file
3. Compile and Run

# Usage
* Running the executable first time will generate two directories on the relative path of the executable, "in" and "out"
* The bitmap images in the "in" directory's contents will be read by the executable, to be processed
* The processed images and the csv file will be outputted to the "out" directory

# Results
The speedup comparison of different CUDA block sizes can be seen [here](https://docs.google.com/spreadsheets/d/1PgbXkxlctCBIPYDMSXIqjVRf3VENVrNdid5s4IY9sHA/edit?usp=sharing)