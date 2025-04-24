#ifndef DISTORTION_H
#define DISTORTION_H

#include "GlobalVariables.h"

double distortionSelection(int algorithm, int drive, double x, double threshold);
void DistortionEffect(int DistAlg, int DistDrive);

#endif // DISTORTION_H
