#include <bits/stdc++.h>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

std::vector<std::string> splitString(const std::string &str, std::string delimiter) {
	std::vector<std::string> ret;
	std::string word;
	size_t pos = 0, dlen = delimiter.length();
	std::string s = str;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		word = s.substr(0, pos);
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

	std::vector<std::pair<ll, ll>> idRanges;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		auto splitLine = (splitString(line, ","));
		for (auto &r : splitLine) {
			auto parts = splitString(r, "-");
			if (parts.size() != 2) {
				std::cerr << "Error: invalid instruction format\n";
				return 1;
			}
			idRanges.push_back({std::stoll(parts[0]), std::stoll(parts[1])});
		}
	}

	auto invalidIds = [](const std::string &s) {
		ll size = s.size();
		for (ll bSz = 1; bSz <= size / 2; ++bSz) {
			if (size % bSz != 0)
				continue;
			auto strBlock = s.substr(0, bSz);
			auto repeat = true;
			for (ll k = bSz; k < size; k += bSz) {
				if (s.substr(k, bSz) != strBlock) {
					repeat = false;
					break;
				}
			}
			if (repeat)
				return true;
		}
		return false;
	};

	std::sort(itN(idRanges));
	ll sum = 0;
	for (auto &[start, end] : idRanges) {
		for (ll i = start; i <= end; ++i) {
			if (invalidIds(std::to_string(i)))
				sum += i;
		}
	}

	std::cout << "Answer: " << sum << std::endl;

	auto chronoEnd = std::chrono::high_resolution_clock::now();
	auto chronoMS =
	    std::chrono::duration_cast<std::chrono::milliseconds>(chronoEnd - chronoSt).count();
	auto sec =
	    std::chrono::duration_cast<std::chrono::duration<double>>(chronoEnd - chronoSt).count();

	std::cout << "Elapsed time: " << chronoMS << " ms (" << sec << " seconds)\n";
	return 0;
}
