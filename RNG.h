#pragma once

#include<memory>
#include<thread>
#include<mutex>



using std::shared_ptr;
namespace ee {
	class RNG final
	{
	private:
		std::mutex randMutex;
		RNG();
	public:
		~RNG();
		int nextRandomInt();
		static shared_ptr<RNG> singleton;
		static shared_ptr<RNG> getInstance();
	};
}

