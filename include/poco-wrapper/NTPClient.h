#pragma once
#include <format>
#include <iostream>
#include <memory>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Delegate.h>
#include <Poco/Net/Net.h>
#include <Poco/Net/NTPClient.h>
#include <Poco/Timespan.h>

namespace poco_wrapper
{
	class NTPClient
	{
	private:
		std::shared_ptr<Poco::Net::NTPClient> _client;

		class NTPResponseHandler;
		std::shared_ptr<NTPResponseHandler> _response_handler;

	public:
		NTPClient(std::string const &ntp_host);

		/// @brief 发送请求，获取时间后返回。
		/// @return
		Poco::Timestamp Request();
	};
} // namespace poco_wrapper
