#include <poco-wrapper/NTPClient.h>

int main()
{
	poco_wrapper::NTPClient client{"time.windows.com"};
	Poco::Timestamp accurate_time = client.Request();
	std::string format = "%Y-%m-%d %H:%M:%S";
	std::string formatted_time = Poco::DateTimeFormatter::format(accurate_time, format);
	std::cout << "从 NTP 服务器得到的时间: " << formatted_time << std::endl;
	return 0;
}
