#include <poco-wrapper/NTPClient.h>
#include <time.h>

void set_system_time(int64_t utc_time_microseconds)
{
	struct timespec ts;

	// 将微秒转换为秒和纳秒
	// 由于1秒 = 1,000,000个微秒单位
	ts.tv_sec = utc_time_microseconds / 1000000;           // 整秒部分
	ts.tv_nsec = (utc_time_microseconds % 1000000) * 1000; // 纳秒部分

	// 设置系统时间
	int result = clock_settime(CLOCK_REALTIME, &ts);
	if (result != 0)
	{
		throw std::runtime_error("设置系统时间失败，请检查是否是管理员权限。");
	}
}

int main()
{
	poco_wrapper::NTPClient client{"time.windows.com"};
	Poco::Timestamp accurate_time = client.Request();
	std::string format = "%Y-%m-%d %H:%M:%S";
	std::string formatted_time = Poco::DateTimeFormatter::format(accurate_time, format);
	std::cout << "从 NTP 服务器得到的时间: " << formatted_time << std::endl;
	set_system_time(accurate_time.epochMicroseconds());
	return 0;
}
