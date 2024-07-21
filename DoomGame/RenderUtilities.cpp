#include "RenderUtilities.h"

namespace RenderUtilities
{
	uint32_t RenderUtilities::renderPointToAngle(int x, int y, Player* player)
	{
		x -= player->getXPosition();
		y -= player->getYPosition();

		if ((!x) && (!y))
			return 0;

		if (x >= 0)
		{
			if (y >= 0)
			{
				if (x > y)
				{
					// Octant 0
					return tantoangle[slopeDiv(y, x)];
				}
				else
				{
					// Octant 1
					return ANG90 - 1 - tantoangle[slopeDiv(x, y)];
				}
			}
			else
			{
				y = -y;
				if (x > y)
				{
					// Octant 8
					return -tantoangle[slopeDiv(y, x)];
					//return ~tantoangle[slopeDiv(y, x)] + 1;
				}
				else
				{
					// Octant 7
					return ANG270 + tantoangle[slopeDiv(x, y)];
				}
			}
		}
		else
		{
			x = -x;
			if (y >= 0)
			{
				if (x > y)
				{
					// Octant 3
					return ANG180 - 1 - tantoangle[slopeDiv(y, x)];
				}
				else
				{
					// Octant 2
					return ANG90 + tantoangle[slopeDiv(x, y)];
				}
			}
			else
			{
				y = -y;
				if (x > y)
				{
					// Octant 4
					return ANG180 + tantoangle[slopeDiv(y, x)];
				}
				else
				{
					// Octant 5
					return ANG270 - 1 - tantoangle[slopeDiv(x, y)];
				}
			}
		}
	}

	int RenderUtilities::slopeDiv(unsigned int num, unsigned int den)
	{
		unsigned ans;

		if (den < 512)
		{
			return SLOPERANGE;
		}
		else
		{
			ans = (num << 3) / (den >> 8);

			if (ans <= SLOPERANGE)
			{
				return ans;
			}
			else
			{
				return SLOPERANGE;
			}
		}
	}


}



