#pragma once


struct edge_2d {
public:
    int x = 0;
    int y = 0;
    int weight = 0;

public:
    bool operator<(const edge_2d& p_other) const {
        return weight < p_other.weight;
    }

    bool operator>(const edge_2d& p_other) const {
        return weight > p_other.weight;
    }
};
