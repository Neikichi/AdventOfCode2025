#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

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
		if (!word.empty())
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

	std::unordered_map<std::string, std::vector<std::string>, boost::hash<std::string>> racks;

	ll idx = 0;
	std::string line;
	while (std::getline(file, line)) {
		line.erase(std::remove(itN(line), ':'), line.end());
		auto parts = splitString(line, " ");
		std::vector<std::string> path;
		for (auto i = 1; i < parts.size(); ++i) {
			path.push_back(parts[i]);
		}
		racks[parts[0]] = path;
	}

	std::unordered_map<std::tuple<std::string, bool, bool>,
	                   ll,
	                   boost::hash<std::tuple<std::string, bool, bool>>>
	    memo;

	std::function<ll(const std::string &, bool, bool)> computeRackValue =
	    [&](const std::string &rackName, bool dac, bool fft) -> ll {
		if (rackName == "out") {
			return (dac && fft) ? 1 : 0;
		}
		if (rackName == "dac") {
			dac = true;
		}
		if (rackName == "fft") {
			fft = true;
		}
		auto key = std::make_tuple(rackName, dac, fft);
		if (auto it = memo.find(key); it != memo.end()) {
			return it->second;
		}
		const auto &path = racks[rackName];
		ll value = 0;
		for (const auto &p : path) {
			value += computeRackValue(p, dac, fft);
		}
		return memo[key] = value;
	};

	ll sum = computeRackValue("svr", false, false);

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
