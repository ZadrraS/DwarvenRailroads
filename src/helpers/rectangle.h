#ifndef DWARVENRR_HELPERS_RECTAMGLE_H_
#define DWARVENRR_HELPERS_RECTAMGLE_H_

namespace dwarvenrr 
{

class Rectangle 
{
 public:
  Rectangle(int x, int y, int width, int height)
  {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
  }

  ~Rectangle()
  {

  }

  int x, y;
  int width, height;
};

}  // namespace dwarvenrr

#endif  // DWARVENRR_HELPERS_RECTAMGLE_H_