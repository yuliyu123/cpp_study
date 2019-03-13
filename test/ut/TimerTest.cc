#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mocks/TimerMock.h"

using namespace asyncServer::base;

class TimerTest : public ::testing::Test, Timer
{
public:
	TimerTest();


private:
	std::unique_ptr<AsioSteadyTimer> timer_;
	std::shared_ptr<Timer> timerPtr_;
	std::unique_ptr<TimerMock> timerMock_;
	TimerCallback cb_;
	uint64_t count_;
	AsioIoService& ioservice_;
};

TEST_F(TimerTest, IfTimeExpired)
{
	timerPtr_ = std::make_shared<Timer>(ioservice_, count_);
	EXPECT_CALL(*timerMock_, timeoutCallback(_)).times(1);
	tick = boost::posix_time::second_clock::local_time();
	timerPtr_->start(100, cb_);
	now = boost::posix_time::second_clock::local_time();
	boost::posix_time::time_duration diff = tick - now;
	diff.total_milliseconds();

	EXPECT_EQ(diff, 100);
}
