#pragma once

#include <algorithm>

namespace ganler
{
    template<typename Iter>
    Iter partition(const Iter beg, const Iter end)
    {
        Iter base = beg;
        auto par = *(end - 1);
        for(auto it = beg; it < end - 1; ++it)
            if(*it < par) std::swap(*it, *base++);
        std::swap(*base, *(end - 1));
        return base;
    }
    
    template<typename Iter>
    void quick_sort(const Iter beg, const Iter end)
    {
        if(std::distance(beg, end) <= 1) return;
        auto piv = partition(beg, end);
        quick_sort(beg, piv);
        quick_sort(piv+1, end);
    }
}
