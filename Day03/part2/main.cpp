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

	std::vector<std::vector<ll>> powerBanks;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		std::vector<ll> bank;
		for (auto &n : line) {
			bank.push_back(n - '0');
		}
		powerBanks.push_back(bank);
	}

	ll sum = 0;

	for (auto &bank : powerBanks) {
		std::vector<ll> maxJolts;
		auto tempBank = bank;
		for (ll i = 12; i > 0; i--) {
			if (tempBank.size() < i)
				break;
			auto maxSets = std::ranges::max_element(tempBank.begin(),
			                                        tempBank.begin() + (tempBank.size() - i + 1));
			maxJolts.push_back(*maxSets);
			tempBank.erase(tempBank.begin(), tempBank.begin() + (tempBank.size() - i + 1));
		}
		ll acm = 0;
		for (auto &n : maxJolts) {
			acm = acm * 10 + n;
		}
		sum += acm;
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
