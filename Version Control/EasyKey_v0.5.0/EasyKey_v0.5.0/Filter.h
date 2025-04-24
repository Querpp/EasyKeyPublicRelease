#ifndef FILTER_H
#define FILTER_H

#include "GlobalVariables.h"

void LowpassFilter(int fc, int order);
double lowPassXdbPerOctave(double freq, double fc, double order);
double butterworthLowPass(double f, double fc, int order);

#endif // FILTER_H
