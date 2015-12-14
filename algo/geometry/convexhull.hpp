#pragma once
#include <algo/geometry/geomvector.hpp>

template<typename T>
std::vector<GeomVector2<T>> convexHull(std::vector<GeomVector2<T>> points)
{
	auto lexicoMinIter = std::min_element(begin(points), end(points));
	if (lexicoMinIter == end(points))
		return{}; // Points are empty

	std::vector<GeomVector2<T>> result;
	auto startPoint = *lexicoMinIter;
	result.push_back(startPoint);

	std::iter_swap(lexicoMinIter, end(points) - 1);
	points.pop_back();

	auto angleThenLengthCompare = [&](const GeomVector2<T>& a, GeomVector2<T>& b)
	{
		auto aDif = a - startPoint;
		auto bDif = b - startPoint;
		auto d = det(aDif, bDif);
		if (d < 0)
			return true;
		else if (d > 0)
			return false;
		else
			return (aDif.lengthSquared() < bDif.lengthSquared());
	};
	
	std::sort(begin(points), end(points), angleThenLengthCompare);
	
	for (const auto& p : points)
	{
		while (result.size() > 1 && det(p - result[result.size() - 1], p - result[result.size() - 2]) <= 0)
			result.pop_back();
		if (!(p == startPoint))
			result.push_back(p);
	}

	return result;
}