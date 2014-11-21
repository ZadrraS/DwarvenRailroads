#ifndef DWARVENRR_MAP_CELL_H_
#define DWARVENRR_MAP_CELL_H_

namespace dwarvenrr 
{
    class Cell
    {
    public:
        Cell();
        ~Cell();

        size_t get_ground_type();

    private:
        size_t ground_type_;

    };
}  // namespace dwarvenrr

#endif  // DWARVENRR_MAP_CELL_H_