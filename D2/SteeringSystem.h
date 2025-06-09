#pragma once

class ISteeringSystem
{
public:
	virtual std::string name() = 0;
};

class BoschSteeringSystem: public ISteeringSystem
{
public:
	std::string name() override { return "Bosch"; };
};

class MobisSteeringSystem: public ISteeringSystem
{
public:
	std::string name() override { return "Mobis"; };
};
