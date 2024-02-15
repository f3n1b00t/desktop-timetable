#pragma once
#include <algorithm>
#include <iterator>
#include <vector>
#include "pair.h"

class pair_list
{
public:
    void add(const pair& pair)
    {
        pairs_.push_back(pair);
    }

    const std::vector<pair>& get_pairs() const
    {
        return pairs_;
    }
    
    friend bool operator==(const pair_list& lhs, const pair_list& rhs)
    {
        return lhs.pairs_ == rhs.pairs_;
    }
private:
    std::vector<pair> pairs_;
};
