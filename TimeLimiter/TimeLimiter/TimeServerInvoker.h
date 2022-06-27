#pragma once
#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <ctime>

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>


namespace orangelie
{

	class TimeServerInvoker
	{
	public:
		TimeServerInvoker();
		TimeServerInvoker& operator=(const TimeServerInvoker&) = delete;
		TimeServerInvoker(const TimeServerInvoker&) = delete;
		~TimeServerInvoker();

		void AddTimeServer(std::string _timeServerIp);
		std::vector<std::string> GetTimeServer() const;
		std::time_t QueryTimeFromServer();

	private:
		bool ConnectTimeServer(std::string _timeServerIp);

	private:
		std::vector<std::string> m_TimeServers;
		SOCKET m_Socket;
		sockaddr_in m_ServAddr;

	};
}