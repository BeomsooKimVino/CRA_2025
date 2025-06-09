#pragma once

class IEngine
{
public:
	virtual std::string name() = 0;
};

class GMEngine: public IEngine
{
public:
	std::string name() override { return "GM"; };
};

class ToyotaEngine : public IEngine
{
public:
	std::string name() override { return "TOYOTA"; };
};

class WiaEngine : public IEngine
{
public:
	std::string name() override { return "WIA"; };
};

class BrokenEngine : public IEngine
{
public:
	std::string name() override { return "Broken"; };
};
