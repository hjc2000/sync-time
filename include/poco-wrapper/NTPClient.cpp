#include "NTPClient.h"

class poco_wrapper::NTPClient::NTPResponseHandler
{
private:
	Poco::Timestamp _t1 = Poco::Timestamp{};
	Poco::Timestamp _accurate_time;
	bool _completed = false;

public:
	// 定义事件处理器方法
	void OnNTPResponse(void const *sender, Poco::Net::NTPEventArgs &args)
	{
		Poco::Timestamp t2 = args.packet().receiveTime();
		Poco::Timestamp t3 = args.packet().transmitTime();
		Poco::Timestamp t4 = Poco::Timestamp{};
		Poco::Timespan delay = ((t4 - _t1) - (t3 - t2)) / 2;
		Poco::Timespan offset = ((t2 - _t1) + (t3 - t4)) / 2;
		_accurate_time = t4 + offset;
		_completed = true;
	}

	bool Completed() const
	{
		return _completed;
	}

	Poco::Timestamp AccurateTime() const
	{
		return _accurate_time;
	}
};

poco_wrapper::NTPClient::NTPClient(std::string const &ntp_host)
{
	_client = std::shared_ptr<Poco::Net::NTPClient>{
		new Poco::Net::NTPClient{
			Poco::Net::SocketAddress::Family::IPv4,
		},
	};

	_response_handler = std::shared_ptr<NTPResponseHandler>{new NTPResponseHandler{}};

	_client->response += Poco::delegate(_response_handler.get(),
										&NTPResponseHandler::OnNTPResponse);
}

Poco::Timestamp poco_wrapper::NTPClient::Request()
{
	while (true)
	{
		_client->request("time.windows.com");
		if (_response_handler->Completed())
		{
			return _response_handler->AccurateTime();
		}
	}
}
