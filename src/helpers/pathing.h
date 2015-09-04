#ifndef DWARVENRR_HELPERS_PATHING_H_
#define DWARVENRR_HELPERS_PATHING_H_

#include "map/grid.h"
#include "helpers/geometry.h"

#include <cmath>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>

namespace std 
{
    template <> struct hash< dwarvenrr::Vector2<int> >
    {
        size_t operator()(const dwarvenrr::Vector2<int> &x) const
        {
            // 420 hash it. Should be good enough for now.
            return 104729 * std::hash<int>()(x.x ^ std::hash<int>()(x.y));
        }
    };
}

namespace dwarvenrr
{
    template < class T1, class T2, class Pred >
    struct sort_pair_first
    {
        bool operator()(const std::pair<T1, T2> &left, const std::pair<T1, T2> &right) 
        {
            Pred p;
            return p(left.first, right.first);
        }
    };

    template<typename T, typename Number>
    struct PriorityQueue 
    {
        typedef std::pair<Number, T> PQElement;
        std::priority_queue< PQElement, std::vector<PQElement>, sort_pair_first<Number, T, std::greater<Number> > > elements;

        inline bool empty() 
        { 
            return elements.empty(); 
        }

        inline void put(T item, Number priority) 
        {
            elements.emplace(priority, item);
        }

        inline T get() 
        {
            T best_item = elements.top().second;
            elements.pop();
            return best_item;
        }
    };

    std::vector< Vector2<int> > FindShortestPath(const Grid &grid, const Vector2<int> &start_pos, const Vector2<int> &goal_pos)
    {
        if (start_pos == goal_pos)
        {
            std::vector< Vector2<int> > path;
            path.push_back(start_pos);
            return path;
        }

        std::unordered_map< Vector2<int>, Vector2<int> > came_from;
        std::unordered_map< Vector2<int>, double > cost_so_far;
        PriorityQueue< Vector2<int>, double > frontier;

        frontier.put(start_pos, 0.0);
        came_from[start_pos] = start_pos;
        cost_so_far[start_pos] = 0.0;
        
        Vector2<int> current;
        while (!frontier.empty())
        {
            current = frontier.get();
            if (current == goal_pos)
                break;

            for (auto next: grid.GetNeighbours(current))
            {
                double new_cost = cost_so_far[current] + grid.Distance(current, next);
                if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
                {
                    cost_so_far[next] = new_cost;
                    double priority = new_cost + EuclideanDistance(next, goal_pos);
                    frontier.put(next, priority);
                    came_from[next] = current;
                }
            }
        }

        std::vector< Vector2<int> > path;
        if (!frontier.empty())
        {            
            current = goal_pos;
            path.push_back(current);
            while (current != start_pos)
            {
                current = came_from[current];
                path.push_back(current);
            }

            std::reverse(path.begin(), path.end());
        }
        return path;
    }

}  // namespace dwarvenrr

#endif  // DWARVENRR_HELPERS_PATHING_H_