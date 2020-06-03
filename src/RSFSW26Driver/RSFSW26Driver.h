#pragma once

#include "rsfsw26driver_global.h"
#include<string>
#include<memory>

class RSFSW26DriverPrivate;
class RSFSW26DRIVER_EXPORT RSFSW26Driver
{
public:
	RSFSW26Driver(const std::string&srcName);
	~RSFSW26Driver();
	bool setOrder(const std::string&s);
	std::string readString();

private:
	std::shared_ptr<RSFSW26DriverPrivate> p_;//所有的复制都是针对一个设备
};
