#include "CosSim.h"
#include<math.h>

CosSim::CosSim()
{

}

void CosSim::Sum(vector<float>& vect, float& Temp, float& Total)
{
	for(int x=0;x<vect.size();x++)
	{
		Temp+= pow(vect[x],2);
		Total+=vect[x];

	}
	Temp= sqrt(Temp);




}
void CosSim::Dot(vector<float>& vect1, vector<float>& vect2, float& nominator)// change to return float
{
	for(int x=0;x<vect2.size();x++)
	{
		nominator+=(vect1[x]*vect2[x]);
	}



}
void CosSim::Dom(float& denominator, float& TempVec1, float& TempVec2)// change to return float
{
	denominator+=TempVec1*TempVec2;
}
void CosSim::Reset(float& Vec1Total, float& Vec2Total, float& TempVec1, float& TempVec2, float& nominator, float& denominator, float& final)
{
			Vec1Total=0;
			Vec2Total=0;

			TempVec1=0;
			TempVec2=0;

			nominator=0;
			denominator=0;
			final=0;
}
