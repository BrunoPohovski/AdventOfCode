#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <ctime>
#include <chrono>
using namespace std;


int main()
{
	std::ifstream fin("Measurements.txt");

	if (!fin.is_open()) {
		std::cout << "Error opening Measurements.txt" << std::endl;
		return 1;
	}

	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

	int sum = 0;
	std::string line;

	//Start time
	 
	while (getline(fin, line))
	{
		int firstDigit = -1; // Initialize to an invalid value
		int lastDigit = -1;  // Initialize to an invalid value
		int number = 0;

		for (char check : line) 
		{
			if (std::isdigit(check)) 
			{
				if (firstDigit == -1) 
				{
					firstDigit = check - '0';
				}
				lastDigit = check - '0';
			}
		}

		if (firstDigit != -1 && lastDigit != -1) 
		{
			number = firstDigit * 10 + lastDigit;
			sum += number;
		}

	}

	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
	auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();
	std::cout << "Time: " << time << " microseconds" << std::endl;
	std::cout << "Sum: " << sum << std::endl;





	return 0;
}