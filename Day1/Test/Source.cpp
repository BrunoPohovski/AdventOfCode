#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <ctime>
#include <regex>
#include <unordered_map>
#include <map>
#include <chrono>
using namespace std;



int processLineWithRegex(const std::string& line) {

	static const unordered_map<string, int> wordMap = {
		{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
		{"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
	};

	std::map<int, int> indexValueMap; // First number is the index and the second is the value
	std::regex Pattern("one|two|three|four|five|six|seven|eight|nine|\\d"); // Matches one of the words or a single digit

	

	std::sregex_iterator it(line.begin(), line.end(), Pattern); // Iterator to iterate through the matches
	std::sregex_iterator end; // End iterator

	while (it != end)
	{
		// Get the match
		std::smatch match = *it;
		std::string word = match.str();

		// Get the index of the match
		int index = match.position();

		// Save the index and value in the map

		if (isdigit(word[0])) {
			indexValueMap.insert(std::make_pair(index, word[0] - '0')); // Convert the char to an int
		}
		else {
			indexValueMap.insert(std::make_pair(index, wordMap.at(word))); // Get the value from the word map
		}

		// Increment the iterator
		it++;
		
	}


	return indexValueMap.begin()->second * 10 + indexValueMap.rbegin()->second;
}




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

	while (std::getline(fin, line))
	{
		sum += processLineWithRegex(line);
	}

	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
	auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();
	std::cout << "Time: " << time << " microseconds" << std::endl;
	std::cout << "Sum: " << sum << std::endl;





	return 0;
}