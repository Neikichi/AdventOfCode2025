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
	auto start = std::chrono::high_resolution_clock::now();

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

	auto getDigitLen = [](ll n) {
		ll len = 0;
		while (n) {
			n /= 10;
			++len;
		}
		return len;
	};

	std::sort(idRanges.begin(), idRanges.end());
	ll sum = 0;
	for (auto &[start, end] : idRanges) {
		for (ll i = start; i <= end; ++i) {
			ll nLen = getDigitLen(i);
			if (nLen % 2 == 0) {
				ll halfLen = nLen / 2;
				ll div = static_cast<ll>(std::pow(10, halfLen));
				ll firstHalf = i / div;
				ll secondHalf = i % div;
				if (firstHalf == secondHalf) {
					sum += i;
				}
			}
		}
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
