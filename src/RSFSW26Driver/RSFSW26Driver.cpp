#include "RSFSW26Driver.h"
#include<iostream>
#include "visa/visa.h"
using std::cerr;
using std::cout;
using std::ends;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;

class RSFSW26DriverPrivate
{
public:
	RSFSW26DriverPrivate(const string&srcName);
	~RSFSW26DriverPrivate();

	bool setOrder(const string&s);
	string readString();
private:
	void init();

	string srcName_;//NI MAX配置的名字
	ViSession defaultRM_;//resource manager
	ViSession instr_;//instrument
	ViStatus status_;
};

RSFSW26DriverPrivate::RSFSW26DriverPrivate(const string&srcName):
	srcName_(srcName),defaultRM_(0),instr_(0),status_(0)
{
	init();
}

RSFSW26DriverPrivate::~RSFSW26DriverPrivate()
{
	status_ = viClose(instr_);
	if (status_ < VI_SUCCESS) {
		cerr << "close instr_ error" << endl;
	}
	status_ = viClose(defaultRM_);
	if (status_ < VI_SUCCESS) {
		cerr << "close defaultRM error" << endl;
	}
}

bool RSFSW26DriverPrivate::setOrder(const string&s)
{
	if (!s.size()) {
		cerr << "order is empty" << endl;
		return false;
	}
	ViUInt32 writeCount{ 0 };
	status_ = viWrite(instr_, (ViBuf)&s[0], s.size(), &writeCount);
	if (status_ < VI_SUCCESS) {
		cerr << s << ":write error" << endl;
		return false;
	}
	return true;
}

string RSFSW26DriverPrivate::readString()
{
	const ViUInt32 bufSize{ 1024 };
	unsigned char buffer[bufSize];
	ViUInt32 count{ 0 };
	status_ = viRead(instr_, buffer, bufSize, &count);

	string tempBuf;
	if (status_ < VI_SUCCESS) {
		cerr << "read buffer error" << endl;
	}
	else {
		tempBuf = (char*)buffer;
	}
	return tempBuf;
}

void RSFSW26DriverPrivate::init()
{
	status_ = viOpenDefaultRM(&defaultRM_);
	if (status_ < VI_SUCCESS) {
		cerr << "open defaultRM error" << endl;
	}

	status_ = viOpen(defaultRM_, &srcName_[0], VI_NULL, VI_NULL, &instr_);
	if (status_ < VI_SUCCESS) {
		cerr << "open device error" << endl;
	}

	status_ = viSetAttribute(instr_, VI_ATTR_TMO_VALUE, 5000);//5秒钟超时
	if (status_ < VI_SUCCESS) {
		cerr << "set timeout error" << endl;
	}
}

RSFSW26Driver::RSFSW26Driver(const std::string&srcName):
	p_(make_shared<RSFSW26DriverPrivate>(srcName))
{

}

RSFSW26Driver::~RSFSW26Driver()
{

}

bool RSFSW26Driver::setOrder(const std::string&s)
{
	return p_->setOrder(s);
}

string RSFSW26Driver::readString()
{
	return p_->readString();
}
