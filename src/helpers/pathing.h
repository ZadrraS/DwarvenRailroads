/* ******************
Most of the code here has been shamelessly stolen from Amit because I'm lazy.
http://www.redblobgames.com/pathfinding/a-star/implementation.html
******************* */

#ifndef DWARVENRR_HELPERS_PATHING_H_
#define DWARVENRR_HELPERS_PATHING_H_

#include "map/hex_coord.h"
#include "map/grid.h"
#include "helpers/hex_utils.h"

#include <cmath>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>

namespace std 
{
    template <> struct hash< dwarvenrr::HexCoord<int> >
    {
        size_t operator()(const dwarvenrr::HexCoord<int> &x) const
        {
            // 420 hash it. Should be good enough for now.
            return 104729 * std::hash<int>()(x.q()) ^ std::hash<int>()(x.r());
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

    std::vector< HexCoord<int> > FindShortestPath(const Grid &grid, const HexCoord<int> &start_hex, const HexCoord<int> &goal_hex)
    {
        if (start_hex == goal_hex)
        {
            std::vector< HexCoord<int> > path;
            path.push_back(start_hex);
            return path;
        }

        std::unordered_map< HexCoord<int>, HexCoord<int> > came_from;
        std::unordered_map< HexCoord<int>, double > cost_so_far;
        PriorityQueue< HexCoord<int>, double > frontier;

        frontier.put(start_hex, 0.0);
        came_from[start_hex] = start_hex;
        cost_so_far[start_hex] = 0.0;
        
        HexCoord<int> current;
        while (!frontier.empty())
        {
            current = frontier.get();
            if (current == goal_hex)
                break;

            for (auto next: grid.GetNeighbours(current))
            {
                double new_cost = cost_so_far[current] + grid.Distance(current, next);
                if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
                {
                    cost_so_far[next] = new_cost;
                    double priority = new_cost + HexDistance<int>(next, goal_hex);
                    frontier.put(next, priority);
                    came_from[next] = current;
                }
            }
        }

        std::vector< HexCoord<int> > path;
        if (!frontier.empty())
        {            
            current = goal_hex;
            path.push_back(current);
            while (current != start_hex)
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