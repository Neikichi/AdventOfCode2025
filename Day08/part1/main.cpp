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

struct vec3 {
	ll x, y, z, idx;

	bool operator==(const vec3 &other) const {
		return x == other.x && y == other.y && z == other.z;
	}
};

struct vec3Hash {
	std::size_t operator()(const vec3 &v) const {
		std::size_t seed = 0;
		boost::hash_combine(seed, v.x);
		boost::hash_combine(seed, v.y);
		boost::hash_combine(seed, v.z);
		return seed;
	}
};

int main() {
	auto chronoSt = std::chrono::high_resolution_clock::now();

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	// std::unordered_set<vec3, boost::hash<p3>> splits, visited;
	std::vector<vec3> jBoxes;

	ll idx = 0;
	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		auto splits = splitString(line, ",");
		if (splits.size() != 3) {
			std::cerr << "Error: invalid line format\n";
			return 1;
		}

		vec3 box{std::stoll(splits[0]), std::stoll(splits[1]), std::stoll(splits[2]), idx++};
		jBoxes.emplace_back(box);
	}

	ll sum = 0;

	auto dist = [](const vec3 &a, const vec3 &b) {
		ll dx = std::abs(a.x - b.x);
		ll dy = std::abs(a.y - b.y);
		ll dz = std::abs(a.z - b.z);
		return dx * dx + dy * dy + dz * dz;
	};

	std::vector<std::tuple<vec3, vec3, double>> pairs;
	for (size_t i = 0; i < jBoxes.size(); ++i) {
		for (size_t j = i + 1; j < jBoxes.size(); ++j) {
			pairs.emplace_back(jBoxes[i], jBoxes[j], dist(jBoxes[i], jBoxes[j]));
		}
	}

	std::ranges::sort(pairs,
	                  [](const auto &a, const auto &b) { return std::get<2>(a) < std::get<2>(b); });

	{
		std::vector<ll> parent(jBoxes.size(), 0), pSize(jBoxes.size(), 1);
		std::ranges::iota(parent, 0);
		ll groups = jBoxes.size();

		std::function<void(ll, ll)> dsu = [&](ll a, ll b) {
			std::function<ll(ll)> find = [&](ll x) {
				if (parent[x] != x)
					parent[x] = find(parent[x]);
				return parent[x];
			};

			ll pa = find(a);
			ll pb = find(b);

			if (pa == pb)
				return;

			groups--;
			if (pSize[pa] > pSize[pb]) {
				parent[pb] = pa;
				pSize[pa] += pSize[pb];
				pSize[pb] = 0;
			} else {
				parent[pa] = pb;
				pSize[pb] += pSize[pa];
				pSize[pa] = 0;
			}
			return;
		};

		for (int i = 0; i < 1000; ++i) {
			auto &[a, b, d] = pairs[i];
			dsu(a.idx, b.idx);
		}

		std::ranges::sort(pSize, std::greater<ll>());

		if (pSize.size() >= 3) {
			sum = std::accumulate(pSize.begin(), pSize.begin() + 3, 1LL, std::multiplies<>());
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
