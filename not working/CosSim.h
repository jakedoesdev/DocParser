#include <string>
#include <vector>
#include <iostream>

using namespace std;

class CosSim
{
	public:
	CosSim();
	void Sum(vector<float>& vect, float& Temp, float& Total);
	void Dot(vector<float>& vect1, vector<float>& vect2, float& nominator);
	void Dom(float& denominator, float& TempVec1, float& TempVec2);
	void Reset(float& Vec1Total, float& Vec2Total, float& TempVec1, float& TempVec2, float& nominator, float& denominator, float& final);
};
