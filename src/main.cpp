#include "base/time/time.h"
#include "poco-wrapper/NTPClient.h"
#include <iostream>

int main()
{
	poco_wrapper::NTPClient client{"time.windows.com"};
	Poco::Timestamp accurate_time = client.Request();
	std::string format = "%Y-%m-%d %H:%M:%S";

	// 中国的时区为：UTC+8
	std::string formatted_time = Poco::DateTimeFormatter::format(accurate_time + Poco::Timespan{0, 8, 0, 0, 0},
																 format);

	std::cout << "从 NTP 服务器得到的时间: " << formatted_time << std::endl;

	/**
	 * 操作系统自带时区功能，所以设置时间时不要手动处理时区带来的时间偏移，
	 * 否则会造成偏移 2 次，变成 UTC+16.
	 */
	base::TimePointSinceEpoch time_point{std::chrono::microseconds{accurate_time.epochMicroseconds()}};
	base::time::SetRealTime(time_point);
	return 0;
}
