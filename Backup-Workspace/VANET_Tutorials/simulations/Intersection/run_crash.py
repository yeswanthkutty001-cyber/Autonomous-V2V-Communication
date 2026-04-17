import traci
import os
import sys

# Initialize SUMO GUI
sumoBinary = "sumo-gui" 
sumoCmd = [sumoBinary, "-c", "sim.sumocfg"]

def run():
    traci.start(sumoCmd)
    
    step = 0
    while step < 1000:
        traci.simulationStep()
        
        # Once vehicles enter the simulation, disable their safety checks
        # "0" disables all checks (collision, gap, etc.), forcing them to drive blindly
        if "veh_A" in traci.vehicle.getIDList():
            traci.vehicle.setSpeedMode("veh_A", 0)
            
        if "veh_B" in traci.vehicle.getIDList():
            traci.vehicle.setSpeedMode("veh_B", 0)
            
        step += 1
    
    traci.close()

if __name__ == "__main__":
    run()