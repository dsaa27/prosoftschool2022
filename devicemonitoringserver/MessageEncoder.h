#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstdint>
#include <vector>
class BaseEncoderExecutor
{
public:
	virtual ~BaseEncoderExecutor() = default;
	virtual std::string encode(const std::string& message) const = 0;
	virtual std::string decode(const std::string& message) const = 0;
	virtual std::string name() const = 0;
};
class ROT3 : public BaseEncoderExecutor
{
public:
	ROT3() = default;
	~ROT3() = default;
	std::string encode(const std::string& message) const final;
	std::string decode(const std::string& message) const final;
	std::string name() const final;
};

class Mirror : public BaseEncoderExecutor
{
public:
	Mirror() = default;
	~Mirror() = default;
	std::string encode(const std::string& message) const final;
	std::string decode(const std::string& message) const final;
	std::string name() const final;
};
class Multiply41 : public BaseEncoderExecutor
{
public:
	Multiply41() = default;
	~Multiply41() = default;
	std::string encode(const std::string& message) const final;
	std::string decode(const std::string& message) const final;
	std::string name() const final;
};
class MessageEncoder
{
public:
	BaseEncoderExecutor *executor = nullptr;
	std::map <std::string, BaseEncoderExecutor *> exctCont = { {"ROT3", new ROT3()}, {"Mirror" , new Mirror()}, {"Multiply41" , new Multiply41()} };
	MessageEncoder() = default;
	MessageEncoder(std::map <std::string, BaseEncoderExecutor *> exctCnt);
	std::string encode(const std::string& message);
	std::string decode(const std::string& message);
	void algChosser(std::string name);
	void algRegistr(std::string name, BaseEncoderExecutor *executor);
	~MessageEncoder();
};

#endif //MESSAGEENCODER_H