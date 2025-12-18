#include <bits/stdc++.h>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

int main() {
	auto chronoSt = std::chrono::high_resolution_clock::now();

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::vector<std::string> lines;

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty())
			continue;
		lines.push_back(line);
	}

	ll maxY = lines.size();
	ll maxX = lines[0].size();

	std::vector<std::vector<std::string>> rtlines;
	std::vector<std::string> digitStrs;
	for (ll x = maxX; x >= 0; --x) {
		std::string digitStr;
		std::string opStr;
		for (ll y = 0; y < maxY; ++y) {
			char c = lines[y][x];
			if (std::isdigit(c))
				digitStr.push_back(c);
			if (c == '+' || c == '*') {
				opStr.push_back(c);
				break;
			}
		}
		if (!digitStr.empty())
			digitStrs.push_back(digitStr);
		if (!opStr.empty()) {
			digitStrs.push_back(opStr);
			rtlines.push_back(digitStrs);
			digitStrs.clear();
		}
	}

	std::vector<std::pair<char, std::vector<ll>>> nList;

	for (const auto &line : rtlines) {
		char op = line.back()[0];
		std::vector<ll> nums;
		for (ll i = 0; i < line.size() - 1; ++i) {
			nums.push_back(std::stoll(line[i]));
		}
		nList.push_back({op, nums});
	}

	ll sum = 0;
	for (const auto &[ch, vec] : nList) {
		if (ch == '*') {
			sum += std::accumulate(itN(vec), 1LL, std::multiplies<ll>());
		} else if (ch == '+') {
			sum += std::accumulate(itN(vec), 0LL, std::plus<ll>());
		} else {
			std::cerr << "Unknown operation: " << ch << "\n";
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
