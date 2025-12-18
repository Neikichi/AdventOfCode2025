#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/algorithms/detail/covered_by/interface.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

typedef long long ll;
using C = std::complex<ll>;

namespace bg = boost::geometry;
using Point = bg::model::d2::point_xy<ll>;
using Polygon = bg::model::polygon<Point>;

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

	std::vector<Point> redTiles;

	ll idx = 0;
	for (auto [yy, line] : std::views::enumerate(std::views::istream<std::string>(file))) {
		redTiles.emplace_back(std::stoll(line), std::stoll(line.substr(line.find(',') + 1)));
	}

	ll sum = 0;

	Polygon poly;
	for (auto &p : redTiles)
		poly.outer().push_back(p);
	bg::correct(poly);

	auto inside = [&](ll x, ll y) -> bool { return bg::covered_by(Point(x, y), poly); };

	auto getMinMax = [&](const Point &a, const Point &b) {
		auto [minX, maxX] = std::ranges::minmax({a.x(), b.x()});
		auto [minY, maxY] = std::ranges::minmax({a.y(), b.y()});
		return std::make_pair(Point(minX, minY), Point(maxX, maxY));
	};

	std::vector<std::pair<Point, Point>> pairTiles;
	for (size_t i = 0; i < redTiles.size(); ++i) {
		for (size_t j = i + 1; j < redTiles.size(); ++j) {
			auto [minP, maxP] = getMinMax(redTiles[i], redTiles[j]);

			if (!inside(minP.x(), minP.y()))
				continue;
			if (!inside(maxP.x(), minP.y()))
				continue;
			if (!inside(maxP.x(), maxP.y()))
				continue;
			if (!inside(minP.x(), maxP.y()))
				continue;

			ll midX = (minP.x() + maxP.x()) / 2;
			ll midY = (minP.y() + maxP.y()) / 2;
			if (!inside(midX, midY))
				continue;

			Polygon rectPoly;
			rectPoly.outer().push_back(Point(minP.x(), minP.y()));
			rectPoly.outer().push_back(Point(maxP.x(), minP.y()));
			rectPoly.outer().push_back(Point(maxP.x(), maxP.y()));
			rectPoly.outer().push_back(Point(minP.x(), maxP.y()));
			bg::correct(rectPoly);

			if (bg::covered_by(rectPoly, poly)) {
				ll area = (maxP.x() - minP.x() + 1) * (maxP.y() - minP.y() + 1);
				sum = std::max(sum, area);
			}
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
