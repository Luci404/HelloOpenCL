#include <iostream>
#include <cassert>

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



	return 0;
}