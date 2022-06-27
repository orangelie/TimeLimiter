#include "TimeLimiter.h"

int main(int argc, char** argv)
{
	std::unique_ptr<orangelie::TimeServerInvoker> timeServerInvoker(new orangelie::TimeServerInvoker);
	timeServerInvoker->AddTimeServer("Input.The.Time.Server.Ip.Address");

	std::unique_ptr<orangelie::TimeLimiter> timeLimiter(new orangelie::TimeLimiter);
	timeLimiter->SetTimeMaxLimits(
		std::atoi(argv[1]), std::atoi(argv[2]), std::atoi(argv[3]),
		std::atoi(argv[4]), std::atoi(argv[5]), std::atoi(argv[6]));

	bool result = timeLimiter->Limit(timeServerInvoker.get());

	// Pass
	if (result)
	{
		std::cout << "The time limit has not passed! (Available)" << std::endl;
	}
	// No pass
	else
	{
		std::cout << "The time limit has passed! (Not available)" << std::endl;
	}

	return 0;
}