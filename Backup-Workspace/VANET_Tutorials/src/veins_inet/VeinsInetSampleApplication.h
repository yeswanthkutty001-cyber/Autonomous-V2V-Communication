#pragma once

#include "veins_inet/veins_inet.h"
#include "veins_inet/VeinsInetApplicationBase.h"

class VEINS_INET_API VeinsInetSampleApplication
    : public veins::VeinsInetApplicationBase
{
protected:
    bool isStopped = false;

    void createAndSendBeacon();

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;

public:
    VeinsInetSampleApplication();
    virtual ~VeinsInetSampleApplication();
};
