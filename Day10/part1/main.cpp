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

struct shibaInu {
	std::vector<bool> lights;
	std::vector<std::vector<ll>> buttons;
	std::vector<ll> jolts;

	bool empty() const {
		return lights.empty() && buttons.empty() && jolts.empty();
	}

	void clear() {
		lights.clear();
		buttons.clear();
		jolts.clear();
	}

	friend std::ostream &operator<<(std::ostream &os, const shibaInu &si) {
		os << "Lights: [";
		for (auto light : si.lights) {
			os << (light ? '#' : '.');
		}
		os << "]\n";
		os << "Buttons: ";
		for (auto &row : si.buttons) {
			os << "(";
			for (size_t i = 0; i < row.size(); ++i) {
				os << row[i];
				if (i + 1 < row.size()) {
					os << ",";
				}
			}
			os << ")";
		}
		os << "\nJolts: {";
		for (size_t i = 0; i < si.jolts.size(); ++i) {
			os << si.jolts[i];
			if (i + 1 < si.jolts.size()) {
				os << ",";
			}
		}
		os << "}\n";
		return os;
	}
};

int main() {
	auto chronoSt = std::chrono::high_resolution_clock::now();

	std::ifstream file("notes.txt");
	if (!file) {
		std::cerr << "Error: cannot open notes.txt\n";
		return 1;
	}

	std::vector<shibaInu> machines;

	ll idx = 0;
	shibaInu temp;
	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		if (line.front() == '[') {
			if (!temp.empty()) {
				machines.emplace_back(temp);
				temp.clear();
			}
			for (auto ch : line) {
				if (ch == '#') {
					temp.lights.push_back(true);
				} else if (ch == '.') {
					temp.lights.push_back(false);
				}
			}
		} else if (line.front() == '(') {
			std::vector<ll> buttonRow;
			auto parts = splitString(line.substr(1, line.length() - 2), ",");
			for (auto &part : parts) {
				buttonRow.push_back(std::stoll(part));
			}
			temp.buttons.push_back(buttonRow);
		} else if (line.front() == '{') {
			auto parts = splitString(line.substr(1, line.length() - 2), ",");
			for (auto &part : parts) {
				temp.jolts.push_back(std::stoll(part));
			}
		}
	}
	if (!temp.empty()) {
		machines.emplace_back(temp);
		temp.clear();
	}

	ll sum = 0;

	auto minButtonCount = [](const shibaInu &machine) -> ll {
		std::queue<std::pair<std::vector<bool>, ll>> q;
		std::unordered_set<std::vector<bool>, boost::hash<std::vector<bool>>> visited;

		std::vector<bool> stLights(machine.lights.size(), false);
		q.push({stLights, 0});
		visited.insert(stLights);

		while (!q.empty()) {
			auto [currLights, count] = q.front();
			q.pop();

			for (const auto &button : machine.buttons) {
				auto nLights = currLights;
				for (const auto &n : button) {
					nLights[n] = !nLights[n];
				}

				if (!visited.count(nLights)) {
					if (nLights == machine.lights) {
						return count + 1;
					}
					visited.insert(nLights);
					q.push({nLights, count + 1});
				}
			}
		}
		return -1;
	};

	for (const auto &machine : machines) {
		ll mbc = minButtonCount(machine);
		if (mbc != -1) {
			sum += mbc;
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
