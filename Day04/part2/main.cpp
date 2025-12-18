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

	std::unordered_set<C, boost::hash<C>> paperRolls;
	ll maxY = 0, maxX = 0;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		for (auto [xx, ch] : std::views::enumerate(line)) {
			if (ch == '@') {
				paperRolls.insert(C(xx, yy));
			}
		}
		if (line.length() > maxX)
			maxX = line.length();
		if (yy > maxY)
			maxY = yy;
	}
	ll sum = 0;

	while (true) {
		std::unordered_set<C, boost::hash<C>> toRemove;
		for (auto &roll : paperRolls) {
			int neighbCount = 0;
			for (auto &dir : dirz) {
				C checkPos = roll + dir;
				if (paperRolls.contains(checkPos)) {
					neighbCount++;
				}
			}
			if (neighbCount < 4) {
				toRemove.insert(roll);
			}
		}
		if (toRemove.empty())
			break;
		for (auto &rem : toRemove) {
			paperRolls.erase(rem);
		}
		sum += toRemove.size();
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
