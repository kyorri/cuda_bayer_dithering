# cuda_bayer_dithering
Parallel and Distributed Algorithms project that implements the Bayer Ordered dithering algorithm in a secvential and also a parallel way using NVIDIA CUDA.

The purpose of the project is to process images using Bayer Dithering algorithm, and to benchmark the difference between a secvential algorithm and a parallel one. <br/>
The project is written using C++ and uses Python scripts for some tasks, like converting images to PNM format. <br/>
For the parallel implementation, NVIDIA CUDA will be used. <br/>

The results of the benchmark will be stored in a csv file for easy integration into Microsoft Excel or Google Sheets. <br/>
Results can be found in results/result#.csv. The time elapsed for the algorithm to run will be represented in milliseconds. <br/>

The machine used for running the tests:
* OS  - Windows 10
* CPU - Ryzen 5 4600H 3.0GHz, 6 cores, 12 logical processors
* RAM - 16 GB