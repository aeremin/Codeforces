#pragma once

template<typename T>
void relaxMax(T& relaxWhat, const T& relaxBy)
{
    relaxWhat = max(relaxWhat, relaxBy);
}

template<typename T>
void relaxMin(T& relaxWhat, const T& relaxBy)
{
    relaxWhat = min(relaxWhat, relaxBy);
}