#pragma once
#include <vector>
#include <algorithm>

template<typename T, typename Predicate>
void sortWithMappings(std::vector<T>& container, Predicate predicate,
                      std::vector<size_t>* forwardMapping, std::vector<size_t>* reverseMapping)
{
    std::vector<std::pair<T, size_t>> containerWithPositionData;
    containerWithPositionData.reserve(container.size());
    for (size_t i = 0; i < container.size(); ++i)
        containerWithPositionData.emplace_back(container[i], i);
    
    auto pairPredicate = [&](const std::pair<T, size_t>& p1, const std::pair<T, size_t>& p2) { return predicate(p1.first, p2.first); };
    std::sort(std::begin(containerWithPositionData), std::end(containerWithPositionData), pairPredicate);

    if (forwardMapping)
        forwardMapping->resize(container.size());
    if (reverseMapping)
        reverseMapping->resize(container.size());

    for (size_t i = 0; i < containerWithPositionData.size(); ++i)
    {
        container[i] = containerWithPositionData[i].first;

        if (forwardMapping)
            (*forwardMapping)[containerWithPositionData[i].second] = i;
        if (reverseMapping)
            (*reverseMapping)[i] = containerWithPositionData[i].second;
    }
}


template<typename T>
void sortWithMappings(std::vector<T>& container, std::vector<size_t>* forwardMapping, std::vector<size_t>* reverseMapping)
{
    sortWithMappings(container, std::less<T>(), forwardMapping, reverseMapping);
}