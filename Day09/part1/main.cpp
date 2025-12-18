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

	constexpr C UR(1, -1);  // up right
	constexpr C UL(-1, -1); // up left
	constexpr C DR(1, 1);   // down right
	constexpr C DL(-1, 1);  // down left
	constexpr C N(0, -1);   // up
	constexpr C S(0, 1);    // down
	constexpr C E(1, 0);    // right
	constexpr C W(-1, 0);   // left

	constexpr auto dirz = std::array<C, 8>{N, E, S, W, UR, DR, DL, UL};

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::vector<C> redTiles;

	ll idx = 0;
	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		redTiles.emplace_back(std::stoll(line), std::stoll(line.substr(line.find(',') + 1)));
	}

	ll sum = 0;

	std::unordered_map<std::pair<C, C>, ll, boost::hash<std::pair<C, C>>> pairsTiles;

	auto getArea = [&](C a, C b) {
		C diff = b - a;
		ll area = (std::abs(diff.real()) + 1) * (std::abs(diff.imag()) + 1);
		return area;
	};

	for (size_t i = 0; i < redTiles.size(); ++i) {
		for (size_t j = i + 1; j < redTiles.size(); ++j) {
			pairsTiles[{redTiles[i], redTiles[j]}] = getArea(redTiles[i], redTiles[j]);
		}
	}

	sum = std::ranges::max(std::views::values(pairsTiles));

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
