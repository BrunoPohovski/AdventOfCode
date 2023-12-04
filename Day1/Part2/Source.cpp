#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include <cctype>
#include <unordered_map>

using namespace std;

int main() {
	static const unordered_map<string, int> wordMap = {
		{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
		{"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
	};

	std::fstream input("Measurements.txt");
	std::string line;
	int sum = 0;
	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

	if (input.is_open()) {
		while (getline(input, line)) {
			// Map of indices to numbers found
			std::map<int, int> map;

			// Parse literal digits
			int idx = 0;
			while (idx < line.size()) {
				if (isdigit(line[idx])) {
					map.insert(std::make_pair(idx, line[idx] - '0'));
				}
				idx++;
			}

			// Parse spelled out digits
			for (auto pair : wordMap) {
				int pos = line.find(pair.first);
				while (pos != std::string::npos) {
					map.insert(std::make_pair(pos, pair.second));
					// pos becomes our index offset for further finds
					pos = line.find(pair.first, pos + pair.first.size());
				}
			}

			sum += map.begin()->second * 10 + map.rbegin()->second;
		}
	}
	else {
		std::cout << "Couldn't open the file." << std::endl;
		return 1;
	}

	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
	auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();
	std::cout << "Time: " << time << " microseconds" << std::endl;
	std::cout << "Sum: " << sum << std::endl;

	return 0;
}



