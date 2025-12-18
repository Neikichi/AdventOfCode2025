#include <bits/stdc++.h>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

std::vector<std::string> splitString(const std::string &str, std::string delimiter) {
	std::vector<std::string> ret;
	size_t pos = 0, dlen = delimiter.length();
	std::string s = str;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		std::string word = s.substr(0, pos);
		if (!word.empty()) // skip empty tokens
			ret.push_back(word);
		s.erase(0, pos + dlen);
	}
	if (!s.empty())
		ret.push_back(s);
	return ret;
}

int main() {
	auto chronoSt = std::chrono::high_resolution_clock::now();

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::vector<std::pair<char, std::vector<ll>>> nList(1024);
	ll maxY = 0, maxX = 0;

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty())
			continue;
		auto parts = splitString(line, " ");
		char c = parts[0][0];
		if (!std::isdigit(c)) {
			for (int i = 0; i < parts.size(); i++) {
				nList[i].first = parts[i][0];
			}

		} else {
			for (int i = 0; i < parts.size(); i++) {
				nList[i].second.push_back(std::stoll(parts[i]));
			}
		}
		if (parts.size() > maxX)
			maxX = parts.size();
		maxY++;
	}

	nList.resize(maxX);

	ll sum = 0;

	for (const auto &[ch, vec] : nList) {
		if (ch == '*') {
			sum += std::accumulate(itN(vec), 1LL, std::multiplies<ll>());
		} else if (ch == '+') {
			sum += std::accumulate(itN(vec), 0LL, std::plus<ll>());
		}
	}

	std::cout << "Answer: " << sum << std::endl;

	{
		// End computation time
		auto chronoEnd = std::chrono::high_resolution_clock::now();
		auto chronoMS =
		    std::chrono::duration_cast<std::chrono::milliseconds>(chronoEnd - chronoSt).count();
		auto sec =
		    std::chrono::duration_cast<std::chrono::duration<double>>(chronoEnd - chronoSt).count();

		std::cout << "Elapsed time: " << chronoMS << " ms (" << sec << " seconds)\n";
	}
	return 0;
}
