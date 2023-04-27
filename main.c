#include <stdio.h>
#include <math.h>
#include "HX711.h"

HX711 scale;

int main() {
  printf("HX711 Demo\n");

  printf("Initializing the scale\n");
  scale.begin(A1, A0); // DOUT = A1, PD_SCK = A0

  printf("Raw ave(20):\t\t%d\n", scale.read_average(20));

  // Scale factor:
  // 1Kg cell: 2020 for reading in gms
  // 50kg cells: 19150 for reading in kg
  scale.set_scale(2020.f); // this value is obtained by calibrating the scale with known weights

  scale.tare(); // reset the scale to 0

  printf("\nAfter setting up the scale:\n");

  printf("Raw:\t\t\t%d\n", scale.read());

  printf("Raw ave(20):\t\t%d\n", scale.read_average(20));

  printf("Raw ave(5) - tare:\t%.2f\n", scale.get_value(5));

  printf("Calibrated ave(5):\t%.1f\n", scale.get_units(5));

  printf("\nReadings:\n");

  int t, i, n;
  double val, sum, sumsq, mean;
  float stddev;

  n = 20;
  t = 0;
  i = sum = sumsq = 0;
  while (i < n) {
    val = ((double) scale.read() - scale.get_offset()) / scale.get_scale();
    sum += val;
    sumsq += val * val;
    i++;
  }
  mean = sum / n;
  stddev = sqrt(sumsq / n - mean * mean);
  printf("Mean, Std Dev of %d readings:\t%.3f\t%.3f\n", i, mean, stddev);

  return 0;
}
