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

	std::vector<ll> maxJolts;
	for (auto &bank : powerBanks) {
		auto it1 = std::ranges::max_element(bank);

		auto preit = std::ranges::max_element(bank.begin(), it1);

		auto postit = bank.end();
		if (std::next(it1) != bank.end()) {
			postit = std::ranges::max_element(std::next(it1), bank.end());
		} else {
			postit = it1;
		}

		ll prejolt = -1;
		if (preit != it1) {
			prejolt = *preit * 10 + *(it1);
		}
		ll postjolt = 0;
		if (postit == it1) {
			postjolt = -1;
		} else
			postjolt = *(it1) * 10 + *postit;

		if (prejolt > postjolt) {
			maxJolts.push_back(prejolt);
		} else {
			maxJolts.push_back(postjolt);
		}
	}

	ll sum = std::accumulate(itN(maxJolts), 0LL);
	std::cout << "Answer: " << sum << std::endl;

	auto chronoEnd = std::chrono::high_resolution_clock::now();
	auto chronoMS =
	    std::chrono::duration_cast<std::chrono::milliseconds>(chronoEnd - chronoSt).count();
	auto sec =
	    std::chrono::duration_cast<std::chrono::duration<double>>(chronoEnd - chronoSt).count();

	std::cout << "Elapsed time: " << chronoMS << " ms (" << sec << " seconds)\n";
	return 0;
}
