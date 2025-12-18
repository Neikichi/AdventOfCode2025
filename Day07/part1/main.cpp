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

	std::unordered_set<C, boost::hash<C>> splits, visited;
	C stPos;
	ll maxY = 0, maxX = 0;

	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		for (auto [xx, ch] : std::views::enumerate(line)) {
			if (ch == 'S') {
				stPos = C(xx, yy);
			} else if (ch == '^') {
				splits.insert(C(xx, yy));
			}
		}
		if (line.size() > maxX)
			maxX = line.size();
		if (yy > maxY)
			maxY = yy;
	}

	ll sum = 0;
	std::queue<std::pair<C, ll>> q;
	q.push({stPos, 0});

	while (!q.empty()) {
		auto [curr, dist] = q.front();
		q.pop();

		if (!visited.insert(curr).second)
			continue;

		C nPos = curr + S;
		if (nPos.real() < 0 || nPos.real() > maxX || nPos.imag() < 0 || nPos.imag() > maxY)
			continue;
		if (splits.contains(nPos)) {
			C lPos = nPos + W;
			C rPos = nPos + E;

			q.push({lPos, dist + 1});
			q.push({rPos, dist + 1});

			sum++;
		} else {
			q.push({nPos, dist});
		}
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
