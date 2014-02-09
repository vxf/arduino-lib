#include <Fletcher16.h>

Fletcher16::Fletcher16()
{
  sum1 = 0xff, sum2 = 0xff;
}

void
Fletcher16::sum( uint8_t const *data, size_t bytes )
{
  while (bytes--)
  {
    sum2 += sum1 += *data++;

    if ((++count) == 20)
    {	
      sum1 = (sum1 & 0xff) + (sum1 >> 8);
      sum2 = (sum2 & 0xff) + (sum2 >> 8);
    }
  }
}

void
Fletcher16::sum(uint8_t const b)
{
  sum2 += sum1 += b;

  if ((++count) == 20)
  {	
    sum1 = (sum1 & 0xff) + (sum1 >> 8);
    sum2 = (sum2 & 0xff) + (sum2 >> 8);
  }
}

uint16_t
Fletcher16::reduce()
{
  sum1 = (sum1 & 0xff) + (sum1 >> 8);
  sum2 = (sum2 & 0xff) + (sum2 >> 8);
  return sum2 << 8 | sum1;
}

// from Wikipedia
uint16_t
Fletcher16::reduceVector( uint8_t const *data, size_t bytes )
{
	uint16_t sum1 = 0xff, sum2 = 0xff;

	while (bytes) {
		size_t tlen = bytes > 20 ? 20 : bytes;
		bytes -= tlen;
		do {
				sum2 += sum1 += *data++;
		} while (--tlen);
		sum1 = (sum1 & 0xff) + (sum1 >> 8);
		sum2 = (sum2 & 0xff) + (sum2 >> 8);
	}
	/* Second reduction step to reduce sums to 8 bits */
	sum1 = (sum1 & 0xff) + (sum1 >> 8);
	sum2 = (sum2 & 0xff) + (sum2 >> 8);
	return sum2 << 8 | sum1;
}
