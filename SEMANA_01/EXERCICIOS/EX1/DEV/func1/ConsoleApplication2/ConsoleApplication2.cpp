#include <iostream>
#include <string>
using namespace std;

float percentual(float v, float min, float max) {
	return float((float(v - min) / float(max - min)) * 100);
}



int main() {
	float teste = percentual(20, 0, 100);
	printf("%f", teste);
}