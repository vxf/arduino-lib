#include <string.h>
#include <stdint.h>

class Fletcher16
{
private:
  uint16_t sum1, sum2;
  int count;

public:
  Fletcher16();
  void sum(uint8_t const *data, size_t bytes);
  void sum(uint8_t const b);
  uint16_t reduce();
  uint16_t reduceVector(uint8_t const *data, size_t bytes);
};
