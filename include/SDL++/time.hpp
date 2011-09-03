#ifndef SDLPP_TIME_INCLUDED
#define SDLPP_TIME_INCLUDED
/* vim:set cindent sw=4 ts=4 sts=4 */

namespace sdlpp
{
	const unsigned MILLIS_PER_SECOND = 1000;
	const unsigned HZ_1    = ((float) MILLIS_PER_SECOND /    1);
	const unsigned HZ_2    = ((float) MILLIS_PER_SECOND /    2);
	const unsigned HZ_5    = ((float) MILLIS_PER_SECOND /    5);
	const unsigned HZ_10   = ((float) MILLIS_PER_SECOND /   10);
	const unsigned HZ_25   = ((float) MILLIS_PER_SECOND /   25);
	const unsigned HZ_30   = ((float) MILLIS_PER_SECOND /   30);
	const unsigned HZ_50   = ((float) MILLIS_PER_SECOND /   50);
	const unsigned HZ_60   = ((float) MILLIS_PER_SECOND /   60);
	const unsigned HZ_100  = ((float) MILLIS_PER_SECOND /  100);
	const unsigned HZ_200  = ((float) MILLIS_PER_SECOND /  200);
	const unsigned HZ_250  = ((float) MILLIS_PER_SECOND /  250);
	const unsigned HZ_500  = ((float) MILLIS_PER_SECOND /  500);
	const unsigned HZ_1000 = ((float) MILLIS_PER_SECOND / 1000);
}

#endif /* SDLPP_TIME_INCLUDED */
