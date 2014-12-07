#include "bitwise.h"

HammingWeightIterator::HammingWeightIterator(int weight) :
	weight_(weight),
	state_(1)
{
	if (0 == weight)
	{
		state_ = MAX + 1;
	}
}

// this is stupidly brute-force, but it's still fast enough for
// the space of 9-bit integers
int HammingWeightIterator::next()
{
	if (state_ > MAX)
	{
		return -1;
	}

	while (num_ones(state_) != weight_)
	{
		++state_;
	}

	// post-increment behavior is important here
	return state_++;
}
