#include"AMI_HDB3_Dec.h"
using namespace std;


AMI_HDB3_Dec::AMI_HDB3_Dec(void):LineDecoder(){
	scramblePattern.push_back(amplitude);
	scramblePattern.push_back(0);
	scramblePattern.push_back(0);
	scramblePattern.push_back(amplitude);
}
AMI_HDB3_Dec::~AMI_HDB3_Dec(void){}

 std::list<bool> AMI_HDB3_Dec::decode(const std::list<float>&in){
	list<bool>result;
	queue<bool>q;
	float lastNonZeroPolarity=0;
	for(float currentSignal : in)
	{
		//get characteristic of signal
		float currentPolarity = currentSignal/abs(currentSignal);
		if(abs(currentSignal)<(amplitude/2)) currentPolarity = 0;

		//add bit to queue
		q.push(currentPolarity!=0);

		if(abs(currentPolarity)>0 )
		{
			//if violation
			if(currentPolarity == lastNonZeroPolarity)
			{
				//last 4 were 0's
				while(q.size())
				{
					result.push_back(false);
					q.pop();
				}
			}

			lastNonZeroPolarity = currentPolarity;
		}


		//max queue size is 4
		if(q.size() >= 4)
		{
			result.push_back(q.front());
			q.pop();
		}

	}

	//empty queue
	while(q.size())
	{
		result.push_back(q.front());
		q.pop();
	}

	 return result;
}