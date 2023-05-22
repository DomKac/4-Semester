#include "CRC.h" // Only need to include this header file!
                 // No libraries need to be included. No project settings need to be messed with.
				 
#include <iomanip>  // Includes ::std::hex
#include <iostream> // Includes ::std::cout
#include <cstdint>  // Includes ::std::uint32_t

int main(int argc, char ** argv)
{
	const unsigned char data[] = { 0x98, 0x76, 0x54, 0x32, 0x10 };
	
	// Second argument is the number of bits. The input data must
	// be a whole number of bytes. Pad any used bits with zeros.
	std::uint32_t crc = CRC::CalculateBits(data, 37, CRC::CRC_32());
	
	std::cout << std::hex << crc;
	
	return 0;
}