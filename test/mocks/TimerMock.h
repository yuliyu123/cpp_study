#include "CommonDef.h"
#include "Timer.h"

class TimerMock : public Timer
{
public:
	TimerMock();
	~TimerMock() {}

	MOCK_METHOD2(start, bool(uint64_t, TimerCallback));
    MOCK_METHOD1(defer, void(uint64_t));
    MOCK_METHOD0(stop, void());
	MOCK_METHOD1(timeoutCallback, void(const boost::system::error_code&));
};
