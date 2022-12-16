#include <iostream>
#include <cassert>
#include <fstream>

#include <CL/opencl.hpp>

int main(int argc, char** argv)
{
	std::cout << "Hello OpenCL!" << std::endl;

	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	assert(platforms.size() > 0);

	auto platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
	assert(devices.size() > 0);

	auto device = devices.front();
	auto vendor = device.getInfo<CL_DEVICE_VENDOR>();
	auto version = device.getInfo<CL_DEVICE_VERSION>();

	cl::Context context(device);

	std::ifstream file("HelloWorld.cl");
	cl::Program::Sources sources(1, std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()));
	cl::Program program(context, sources);
	auto error = program.build("-cl-std=CL1.2");

	char result[16];
	cl::Buffer buffer(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(result));
	cl::Kernel kernel(program, "HelloWorld", &error);
	kernel.setArg(0, buffer);

	cl::CommandQueue queue(context, device);
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(16), cl::NullRange);
	queue.enqueueReadBuffer(buffer, true, 0, sizeof(result), result);

	std::cout << result;
	std::cin.get();

	return 0;
}