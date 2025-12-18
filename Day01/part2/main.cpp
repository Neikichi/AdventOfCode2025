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

	ll sum = 0;

	auto it = dialPos.begin() + 50;
	for (const auto &[dir, dist] : instructions) {
		if (dir == 'R') {
			for (ll i = 0; i < dist; ++i) {
				++it;
				if (it == dialPos.end())
					it = dialPos.begin();

				if (*it == 0)
					++sum;
			}
		} else {
			for (ll i = 0; i < dist; ++i) {
				if (it == dialPos.begin())
					it = dialPos.end();
				--it;

				if (*it == 0)
					++sum;
			}
		}
	}

	// arithmetic ways
	// ll n = dialPos.size();
	// ll pos = 50;
	//
	// for (const auto &[dir, dist] : instructions) {
	// 	for (ll i = 0; i < dist; ++i) {
	// 		if (dir == 'R') {
	// 			pos = (pos + 1) % n;
	// 		} else {
	// 			pos = (pos + n - 1) % n;
	// 		}
	// 		if (pos == 0)
	// 			++sum;
	// 	}
	// }

	std::cout << "Answer: " << sum << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	std::cout << "Elapsed time: " << ms << " ms (" << sec << " seconds)\n";
	return 0;
}
