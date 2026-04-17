#include "veins_inet/VeinsInetSampleApplication.h"
#include "veins_inet/VeinsInetSampleMessage_m.h"

using namespace inet;

Define_Module(VeinsInetSampleApplication);

static const double SAFE_DISTANCE = 20.0;
static const double DRIVE_SPEED  = 13.0;
static const double STOP_SPEED   = 0.0;

VeinsInetSampleApplication::VeinsInetSampleApplication() {}
VeinsInetSampleApplication::~VeinsInetSampleApplication() {}

bool VeinsInetSampleApplication::startApplication()
{
    //traciVehicle->setSpeedMode(0);
    //traciVehicle->setSpeed(DRIVE_SPEED);

    EV_INFO << "START " << mobility->getExternalId()
            << " at t=" << simTime() << endl;

    timerManager.create(
        veins::TimerSpecification([this]() {
            createAndSendBeacon();
        }).oneshotIn(SimTime(1, SIMTIME_S))
    );

    return true;
}

bool VeinsInetSampleApplication::stopApplication()
{
    return true;
}

void VeinsInetSampleApplication::createAndSendBeacon()
{
    Coord myPos = mobility->getCurrentPosition();

    EV_INFO << "[TX] t=" << simTime()
            << " sender=" << mobility->getExternalId()
            << " pos=(" << myPos.x << "," << myPos.y << ")"
            << " speed=" << traciVehicle->getSpeed()
            << endl;

    auto msg = makeShared<VeinsInetSampleMessage>();
    msg->setChunkLength(B(40));
    msg->setSenderId(mobility->getExternalId().c_str());
    msg->setPosX(myPos.x);
    msg->setPosY(myPos.y);
    msg->setRequestJunction(true);

    auto pkt = createPacket("v2vBeacon");
    pkt->insertAtBack(msg);
    sendPacket(std::move(pkt));

    timerManager.create(
        veins::TimerSpecification([this]() {
            createAndSendBeacon();
        }).oneshotIn(SimTime(1, SIMTIME_S))
    );
}

void VeinsInetSampleApplication::processPacket(std::shared_ptr<Packet> pk)
{
    if (!traciVehicle)
        return;

    auto msg = pk->peekAtFront<VeinsInetSampleMessage>();

    std::string otherId = msg->getSenderId();
    std::string myId    = mobility->getExternalId();

    if (otherId == myId)
        return;

    Coord otherPos(msg->getPosX(), msg->getPosY(), 0);
    Coord myPos = mobility->getCurrentPosition();

    double distance = myPos.distance(otherPos);

    EV_WARN << "[RX] t=" << simTime()
            << " me=" << myId
            << " other=" << otherId
            << " myPos=(" << myPos.x << "," << myPos.y << ")"
            << " otherPos=(" << otherPos.x << "," << otherPos.y << ")"
            << " dist=" << distance
            << " speed=" << traciVehicle->getSpeed()
            << " stopped=" << isStopped
            << endl;

    // ---- STOP DECISION ----
    if (distance < SAFE_DISTANCE && !isStopped) {
        EV_ERROR << "[DECISION] STOP issued by " << myId
                 << " at dist=" << distance
                 << " t=" << simTime() << endl;

        traciVehicle->setSpeed(STOP_SPEED);
        isStopped = true;
        getParentModule()->getDisplayString().setTagArg("i", 1, "red");
    }

    // ---- RESUME DECISION ----
    if (distance > SAFE_DISTANCE + 5 && isStopped) {
        EV_INFO << "[DECISION] RESUME issued by " << myId
                << " at dist=" << distance
                << " t=" << simTime() << endl;

        traciVehicle->setSpeed(DRIVE_SPEED);
        isStopped = false;
        getParentModule()->getDisplayString().setTagArg("i", 1, "green");
    }
}
