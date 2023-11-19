#ifndef __Formulas_H
#define __Formulas_H



#define ROUND(x)	((x) > 0 ? (int)(x + .5) : -(int)(.5 - x))


//////////////////////
// OVERLAP FORMULAS //
//////////////////////

#define NOF(x, max)				(x - (((int)((x + 1) / max) - 1) * max))	// Negative Overlap formula
#define POF(x, max)				(x - ((int)(x / max) * max))				// Positive Overlap formula

#define FLOAT_NOF(x, max)		(x - (((float)(int)((x + 1) / max) - 1) * max))
#define FLOAT_POF(x, max)		(x - ((float)(int)(x / max) * max))

#define OVERLAP(x, max)			(x < 0) ? NOF(x, max) : POF(x, max) 
#define FLOAT_OVERLAP(x, max)	(x < 0) ? FLOAT_NOF(x, max) : FLOAT_POF(x, max)



#endif