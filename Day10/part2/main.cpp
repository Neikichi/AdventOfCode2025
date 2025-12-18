#include <bits/stdc++.h>
#include <z3++.h>

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

	size_t size() const {
		return lights.size() + buttons.size() + jolts.size();
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

ll tryZ3(const auto &jolts, const auto &buttons) {
	z3::context c;
	z3::optimize opt(c);

	int jSize = jolts.size();
	int bSize = buttons.size();

	std::vector<z3::expr> pressCounts;
	pressCounts.reserve(bSize);

	for (int i = 0; i < bSize; ++i) {
		auto x = c.int_const(("x_" + std::to_string(i)).c_str());
		pressCounts.push_back(x);

		opt.add(x >= 0);
	}

	std::vector<std::vector<int>> tileToButtons(jSize);
	for (int b = 0; b < bSize; ++b) {
		for (int idx : buttons[b]) {
			tileToButtons[idx].push_back(b);
		}
	}

	for (int j = 0; j < jSize; ++j) {
		z3::expr sum = c.int_val(0);

		for (int b : tileToButtons[j]) {
			sum = sum + pressCounts[b];
		}

		z3::expr rhs = c.int_val((int)jolts[j]);
		opt.add(sum == rhs);
	}

	z3::expr total = c.int_val(0);
	for (auto &pc : pressCounts)
		total = total + pc;

	opt.minimize(total);

	if (opt.check() != z3::sat) {
		return -1;
	}

	z3::model m = opt.get_model();
	ll result = 0;

	for (auto &pc : pressCounts)
		result += m.eval(pc).get_numeral_int();

	return result;
}

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

	for (const auto &machine : machines) {
		ll res = tryZ3(machine.jolts, machine.buttons);
		if (res != -1) {
			sum += res;
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
