#pragma once

class IBrakeSystem
{
public:
	virtual std::string name() = 0;
};

class MandoBrakeSystem: public IBrakeSystem
{
public:
	std::string name() override { return "Mando"; };
};

class ContinentalBrakeSystem : public IBrakeSystem
{
public:
	std::string name() override { return "Continental"; };
};


class BoschBrakeSystem : public IBrakeSystem
{
public:
	std::string name() override { return "Bosch"; };
};
