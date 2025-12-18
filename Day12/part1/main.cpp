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

struct Shape {
	ll id, bboxX, bboxY;
	std::vector<std::string> grid;
	std::vector<C> cell;
};

struct Instruction {
	ll y;
	ll x;
	std::vector<ll> seq;
};

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

	std::string data(std::istreambuf_iterator<char>(file), {});
	file.close();

	auto blocks = splitString(data, "\n\n");

	std::vector<Shape> shapes;
	std::vector<Instruction> instructions;

	for (auto i = 0; i < blocks.size(); ++i) {
		auto lines = splitString(blocks[i], "\n");
		if (i == blocks.size() - 1) {
			for (auto i = 0; i < lines.size(); ++i) {
				auto splits = splitString(lines[i], " ");

				Instruction instr;
				auto xPos = splits[0].find('x');
				instr.y = std::stoll(splits[0].substr(xPos + 1));
				instr.x = std::stoll(splits[0]);

				for (auto ix = 1; ix < splits.size(); ++ix) {
					instr.seq.push_back(std::stoll(splits[ix]));
				}
				instructions.push_back(instr);
			}

		} else {
			Shape shape;

			shape.id = std::stoll(lines[0]);

			for (auto i = 1; i < lines.size(); ++i) {
				shape.grid.push_back(lines[i]);
			}
			shapes.push_back(shape);
		}
	}

	for (auto &shape : shapes) {
		for (auto y = 0; y < shape.grid.size(); ++y) {
			std::cout << shape.grid[y] << "\n";
			for (auto x = 0; x < shape.grid[y].size(); ++x) {
				if (shape.grid[y][x] == '#') {
					shape.cell.push_back(C(x, y));
				}
			}
		}
		auto minmaxX = std::ranges::minmax(
		    shape.cell, [](const C &a, const C &b) { return a.real() < b.real(); });

		auto minmaxY = std::ranges::minmax(
		    shape.cell, [](const C &a, const C &b) { return a.imag() < b.imag(); });

		shape.bboxX = static_cast<ll>(minmaxX.max.real() - minmaxX.min.real() + 1);
		shape.bboxY = static_cast<ll>(minmaxY.max.imag() - minmaxY.min.imag() + 1);
	}

	ll sum = 0;
	for (auto &instr : instructions) {
		ll instrArea = instr.x * instr.y;

		ll totalShapeArea = 0, totalInstrArea = 0;

		for (auto i = 0; i < shapes.size(); ++i) {
			ll instrCount = (i < instr.seq.size()) ? instr.seq[i] : 0;
			totalShapeArea += instrCount * shapes[i].cell.size();
			totalInstrArea += instrCount * (shapes[i].bboxX * shapes[i].bboxY);
		}

		if (totalInstrArea <= instrArea && totalShapeArea <= instrArea) {
			sum++;
		}
	}

	std::cout << "Answer: " << sum << "\n";

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
