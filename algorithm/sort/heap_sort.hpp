#pragma once

#include <algorithm>

namespace ganler
{

template <typename Iter>
void heapify(const Iter beg, const Iter end, const Iter parent)
{
    Iter left = beg + std::distance(beg, parent) * 2 + 1;
    Iter right = left + 1;
    if(right < end)
    {
        auto max_it = (*left > *right) ? left : right;
        if(*max_it > *parent)
        {
            std::swap(*max_it, *parent);
            heapify(beg, end, max_it);
        }
    }
    else if(right == end && *parent < *left)
        std::swap(*left, *parent);
}

template <typename Iter>
void make_heap(const Iter beg, const Iter end)
{
    auto len = std::distance(beg, end);
    if(len <= 1) return;
    for(int i = (len - 2)/2; i >= 0; --i)
        ganler::heapify(beg, end, beg + i);
}

template <typename Iter>
void heap_sort(const Iter beg, Iter end)
{
    auto len = std::distance(beg, end);
    if(len <= 1) return;
    while(beg < end)
    {
        std::swap(*beg, *--end);
        ganler::heapify(beg, end, beg);
    }
}

}
