#define __CL_ENABLE_EXCEPTIONS
#define CL_TARGET_OPENCL_VERSION 300
#include <iostream>
#include <tuple>
#include <cmath>
#include <fstream>
#include <chrono>
#include <vector>
#include <math.h>
#include <omp.h>
#include <CL/opencl.hpp>

using namespace std;

extern "C" double count_s(double, long long);
extern "C" double eval_y(double);

const char* kernel_source = R"(
	"__kernel void calculate(__global double* result, __global int* n_values, double a, double b, double h, double eps) {\n"
    "    int idx = get_global_id(0);\n"
    "    double x = a + idx * h;\n"
    "    double y = eval_y(x);\n"
    "    double sum = 1.0;\n"
    "    int n = 0;\n"
    "    for (long long j = 1; fabs(y - sum) > eps; j++) {\n"
    "        sum += count_s(x, j);\n"
    "        n++;\n"
    "    }\n"
    "    result[idx] = sum;\n"
    "    n_values[idx] = n;\n"
    "}\n";
)";

void iGPUCalculation(double a, double b, double h, double eps, const char* kernel_source) {

    try {
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        if (platforms.empty()) {
            std::cerr << "No OpenCL platforms found!" << std::endl;
            return;
        }

        for (const auto& platform : platforms) {
            std::cout << "Platform Name: " << platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
        }

        // cl::Platform platform = platforms.front();
        // std::vector<cl::Device> devices;
        // platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
        // if (devices.empty()) {
        //     std::cerr << "No GPU devices found!" << std::endl;
        //     return;
        // }

        // cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, nullptr);
        // cout << context << endl;

        // cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, 0, nullptr);
        // cout << queue << endl;

        // cl_program program = clCreateProgramWithSource(context, 1, &kernel_source, nullptr, nullptr);

        // clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);

        // // Create kernel
        // cl_kernel kernel = clCreateKernel(program, "calculate", nullptr);

        // std::vector<std::pair<int, double>> points;

        // int upper_bound = static_cast<int>((b - a) / h);

        // // Allocate memory on iGPU
        // cl_mem resultBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(double) * upper_bound, nullptr, nullptr);
        // cl_mem nBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * upper_bound, nullptr, nullptr);

        // // Kernel args
        // clSetKernelArg(kernel, 0, sizeof(cl_mem), &resultBuffer);
        // clSetKernelArg(kernel, 1, sizeof(cl_mem), &nBuffer);
        // clSetKernelArg(kernel, 2, sizeof(double), &a);
        // clSetKernelArg(kernel, 3, sizeof(double), &b);
        // clSetKernelArg(kernel, 4, sizeof(double), &h);
        // clSetKernelArg(kernel, 5, sizeof(double), &eps);

        // // Execute the kernel
        // size_t globalSize = upper_bound;
        // clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &globalSize, nullptr, 0, nullptr, nullptr);

        // std::vector<double> result(upper_bound);
        // std::vector<int> n_values(upper_bound);

        // // Read the result
        // clEnqueueReadBuffer(queue, resultBuffer, CL_TRUE, 0, sizeof(double) * upper_bound, &result[0], 0, nullptr, nullptr);
        // clEnqueueReadBuffer(queue, nBuffer, CL_TRUE, 0, sizeof(int) * upper_bound, &n_values[0], 0, nullptr, nullptr);

        // // Cleanup
        // clReleaseMemObject(resultBuffer);
        // clReleaseMemObject(nBuffer);
        // clReleaseKernel(kernel);
        // clReleaseProgram(program);
        // clReleaseCommandQueue(queue);
        // clReleaseContext(context);

        // Output the result
        // for (auto val : result) {
        //     std::cout << "result: " << val << std::endl;
        // }

        // for (auto val : n_values) {
        //     std::cout << "n: " << val << std::endl;
        // }
    } catch (std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
}

int main()
{
    // double a,b,h,eps;
    // int n = 0;
	// vector <std::tuple<int,double, int>> points;
    // std::cout << "Введите a, b, h ,eps" << endl;
    // cin >> a >> b >> h >> eps;
   	// auto start_time = chrono::high_resolution_clock::now();

	// double i = 0;
	// int upper_bound = int((b-a)/h);
	// double y = 0, sum = 0;

	// #pragma omp parallel for schedule(dynamic) shared(a, b, h, eps, y, sum, n, points, start_time)
	// for (int k = 0; k < upper_bound; k++) {
	// 	i = a + k * h;
	// 	y = eval_y(i);
	// 	sum = 1;

	// 	for (long long j = 1; std::abs(y - sum) > eps; j++) {
	// 		sum += count_s(i, j);
	// 		n++;
	// 	}

	// 	#pragma omp critical
	// 	{
	// 		auto end_time = std::chrono::high_resolution_clock::now();
	// 		points.push_back(std::make_tuple(n, std::chrono::duration<double, std::milli>(end_time - start_time).count(), omp_get_thread_num()));
	// 		std::cout << "time: " << std::chrono::duration<double, std::milli>(end_time - start_time).count() << std::endl;
	// 		std::cout << "y = " << y << "\nsum = " << sum << "\nn = " << n << std::endl;
	// 	}
	// }

	// std::cout << "End!";
	// std::ofstream fout("without_hyperthreading_all_core.csv");
    // fout << "iters;time;core" << std::endl;
    // if(a > b) std::swap(a, b);
    // double x = a;
    // for(auto val: points)
    // {	
    //     fout << std::get<0>(val) << ';' << std::get<1>(val) << ";" << std::get<2>(val) << std::endl;
    // }
    // fout.close();

    iGPUCalculation(1, 2, 0.001, 0.001, kernel_source);
	return 0;
}