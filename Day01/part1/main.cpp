#include <bits/stdc++.h>

typedef long long ll;
using C = std::complex<ll>;

#define itN(x) x.begin(), x.end()
#define itNr(x) x.rbegin(), x.rend()
#define itNc(x) x.cbegin(), x.cend()
#define itNrc(x) x.crbegin(), x.crend()

int main() {
	auto start = std::chrono::high_resolution_clock::now();

	constexpr C UR(1, -1);  // up right
	constexpr C UL(-1, -1); // up left
	constexpr C DR(1, 1);   // down right
	constexpr C DL(-1, 1);  // down left
	constexpr C N(0, -1);   // up
	constexpr C S(0, 1);    // down
	constexpr C E(1, 0);    // right
	constexpr C W(-1, 0);   // left

	constexpr auto dirz = std::array<C, 4>{N, E, S, W};

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::vector<std::pair<char, ll>> instructions;

	ll maxDial = 99;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		instructions.push_back({line[0], std::stoll(line.substr(1))});
	}

	std::vector<ll> dialPos(maxDial + 1);
	std::iota(itN(dialPos), 0);

	std::rotate(dialPos.begin(), dialPos.begin() + 50, dialPos.end());

	ll sum = 0;

	for (const auto &[dir, dist] : instructions) {
		size_t n = dialPos.size();
		size_t actual_dist = dist % n;
		if (dir == 'R') {
			std::rotate(dialPos.begin(), dialPos.begin() + actual_dist, dialPos.end());
		} else if (dir == 'L') {
			std::rotate(dialPos.begin(), dialPos.end() - actual_dist, dialPos.end());
		}
		if (dialPos.front() == 0) {
			sum++;
		}
	}

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
