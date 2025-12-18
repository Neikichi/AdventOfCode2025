#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

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

	std::vector<std::pair<ll, ll>> inventory;
	std::vector<ll> toCheck;

	for (auto line : std::views::istream<std::string>(file)) {
		if (line.find('-') != std::string::npos) {
			size_t dashPos = line.find('-');
			ll x1 = std::stoll(line.substr(0, dashPos));
			ll x2 = std::stoll(line.substr(dashPos + 1));
			inventory.emplace_back(x1, x2);
		} else {
			toCheck.push_back(std::stoll(line));
		}
	}
	// Sort by start
	std::sort(inventory.begin(), inventory.end());
	std::vector<std::pair<ll, ll>> merged;
	for (const auto &[start, end] : inventory) {
		if (merged.empty() || merged.back().second < start) {
			merged.push_back({start, end});
		} else {
			merged.back().second = std::max(merged.back().second, end);
		}
	}

	ll sum = 0;
	for (const auto &[start, end] : merged) {
		sum += std::abs(end - start + 1);
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
