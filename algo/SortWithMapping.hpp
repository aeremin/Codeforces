#pragma once

template<typename T>
void sortWithMappings(vector<T>& container, vector<size_t>* forwardMapping, vector<size_t>* reverseMapping)
{
    vector<pair<T, size_t>> containerWithPositionData;
    containerWithPositionData.reserve(container.size());
    for (size_t i = 0; i < container.size(); ++i)
        containerWithPositionData.emplace_back(container[i], i);
    sort(begin(containerWithPositionData), end(containerWithPositionData));

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