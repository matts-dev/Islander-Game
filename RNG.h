#pragma once

#include<memory>
#include<thread>
#include<mutex>

namespace ee {
	class RNG final
	{
	private:
		std::mutex randMutex;
		RNG();
	public:
		~RNG();
		int nextRandomInt();
		static std::shared_ptr<RNG> singleton;
		static std::shared_ptr<RNG> getInstance();
	};
}

