#include "TimeServerInvoker.h"


namespace orangelie
{

	TimeServerInvoker::TimeServerInvoker()
	{

		// Referenced by
		// https://tf.nist.gov/tf-cgi/servers.cgi
		m_TimeServers =
		{
			"ntp-b.nist.gov",
			"time-b-g.nist.gov",
			"time-c-g.nist.gov",
			"time-d-g.nist.gov",
			"time-e-g.nist.gov",
			"time-a-wwv.nist.gov",
			"time-b-wwv.nist.gov",
			"time-c-wwv.nist.gov",
			"time-d-wwv.nist.gov",
			"time-e-wwv.nist.gov",
			"time-a-b.nist.gov",
			"time-b-b.nist.gov",
			"time-c-b.nist.gov",
			"time-d-b.nist.gov",
			"time-e-b.nist.gov",
			"time.nist.gov",
			"utcnist.colorado.edu",
			"utcnist2.colorado.edu",
			"ntp-b.nist.gov",
			"ntp-wwv.nist.gov",
			"ntp-c.colorado.edu",
			"ntp-d.nist.gov",
			"ut1-time.colorado.edu",
			"ut1-wwv.nist.gov",
		};
	}

	TimeServerInvoker::~TimeServerInvoker()
	{
	}

	void TimeServerInvoker::AddTimeServer(std::string _timeServerIp)
	{
		m_TimeServers.push_back(_timeServerIp);
	}

	std::vector<std::string> TimeServerInvoker::GetTimeServer() const
	{
		return m_TimeServers;
	}

	std::time_t TimeServerInvoker::QueryTimeFromServer()
	{
		WSADATA wsaData;
		std::time_t sBuffer;
		int strLen;

		if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
		{
			return -1;
		}

		m_Socket = socket(PF_INET, SOCK_STREAM, 0);

		if (m_Socket == INVALID_SOCKET)
		{
			return -1;
		}

		memset(&m_ServAddr, 0, sizeof(m_ServAddr));
		m_ServAddr.sin_family = AF_INET;
		m_ServAddr.sin_port = htons(37);

		bool getSignFlag = false;
		for (size_t i = 0; i < m_TimeServers.size(); ++i)
		{
			if (ConnectTimeServer(m_TimeServers[i]))
			{
				getSignFlag = true;
				break;
			}

			std::cout << i;
		}

		if (!getSignFlag)
		{
			return -1;
		}

		strLen = recv(m_Socket, (char*)&sBuffer, sizeof(sBuffer), 0);


		if (strLen == -1)
		{
			return -1;
		}

		sBuffer = ntohl(sBuffer) - 2208988800l;

		closesocket(m_Socket);
		WSACleanup();

		return sBuffer;
	}

	bool TimeServerInvoker::ConnectTimeServer(std::string _timeServerIp) 
	{
		hostent* s_HostEntry = gethostbyname(_timeServerIp.c_str());
		if (s_HostEntry == nullptr)
		{
			return false;
		}

		memcpy((void*)(&m_ServAddr.sin_addr), (void*)(s_HostEntry->h_addr), sizeof(m_ServAddr.sin_addr));
		if (connect(m_Socket, (sockaddr*)&m_ServAddr, sizeof(m_ServAddr)) == SOCKET_ERROR)
		{
			return false;
		}

		return true;
	}
}