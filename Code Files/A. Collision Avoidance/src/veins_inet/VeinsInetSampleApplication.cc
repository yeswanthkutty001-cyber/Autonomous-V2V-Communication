//
// Copyright (C) 2018 Christoph Sommer <sommer@ccs-labs.org>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "veins_inet/VeinsInetSampleApplication.h"

#include "inet/common/packet/Packet.h"
#include "inet/common/TimeTag_m.h"
#include "veins_inet/VeinsInetSampleMessage_m.h"

using namespace inet;

Define_Module(VeinsInetSampleApplication);

static const double MIN_SAFE_DISTANCE = 15.0;

VeinsInetSampleApplication::VeinsInetSampleApplication() {}

bool VeinsInetSampleApplication::startApplication()
{
    if (getParentModule()->getIndex() == 0) {

        auto emergencyBrake = [this]() {

            if (!traciVehicle) {
                EV_WARN << "TraCI not ready yet, skipping brake\n";
                return;
            }

            EV_WARN << "FRONT VEHICLE: EMERGENCY BRAKE\n";

            traciVehicle->setSpeed(0);

            auto msg = makeShared<VeinsInetSampleMessage>();
            msg->setChunkLength(B(100));
            msg->setEmergencyBrake(true);
            msg->setPosition(traciVehicle->getLanePosition());

            timestampPayload(msg);

            auto pkt = createPacket("brakeAlert");
            pkt->insertAtBack(msg);
            sendPacket(std::move(pkt));

            getParentModule()->getDisplayString().setTagArg("i", 1, "red");
        };

        timerManager.create(
            veins::TimerSpecification(emergencyBrake)
                .oneshotAt(simTime() + 20)
        );
    }

    return true;
}

bool VeinsInetSampleApplication::stopApplication()
{
    return true;
}

VeinsInetSampleApplication::~VeinsInetSampleApplication() {}

void VeinsInetSampleApplication::processPacket(std::shared_ptr<Packet> pk)
{
    if (getParentModule()->getIndex() != 1)
        return;

    if (!traciVehicle)
        return;

    auto msg = pk->peekAtFront<VeinsInetSampleMessage>();

    if (!msg->getEmergencyBrake())
        return;

    double myPos = traciVehicle->getLanePosition();
    double gap = msg->getPosition() - myPos;

    if (gap > 0 && gap < MIN_SAFE_DISTANCE) {
        traciVehicle->setSpeed(0);
        getParentModule()->getDisplayString().setTagArg("i", 1, "red");
    }
}
