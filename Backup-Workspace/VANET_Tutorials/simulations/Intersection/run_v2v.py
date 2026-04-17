import traci
import math

sumoBinary = "sumo-gui"
sumoCmd = [sumoBinary, "-c", "sim.sumocfg"]

# V2V Parameters
COMM_RANGE = 60.0
# We trigger braking when both cars are within 45m of the center
CRITICAL_DIST = 45.0 

def get_dist(x1, y1, x2, y2):
    return math.sqrt((x1 - x2)**2 + (y1 - y2)**2)

def run():
    traci.start(sumoCmd)
    step = 0
    collision_prevented = False
    
    # 1. GET ACTUAL JUNCTION LOCATION
    # This prevents coordinate errors if netconvert shifted the map
    jx, jy = traci.junction.getPosition("center")
    print(f"DEBUG: Junction 'center' is located at x={jx}, y={jy}")

    while step < 1000:
        traci.simulationStep()
        
        veh_list = traci.vehicle.getIDList()
        
        if "veh_A" in veh_list and "veh_B" in veh_list:
            
            # 2. DISABLE INTERNAL DRIVER (The "Blind" Mode)
            # This forces the car to rely 100% on your code
            traci.vehicle.setSpeedMode("veh_A", 0)
            if not collision_prevented:
                traci.vehicle.setSpeedMode("veh_B", 0)

            # Get positions
            x_a, y_a = traci.vehicle.getPosition("veh_A")
            x_b, y_b = traci.vehicle.getPosition("veh_B")
            
            # Distance to each other
            dist_v2v = get_dist(x_a, y_a, x_b, y_b)
            
            # Distance to Junction Center
            d_a_junc = get_dist(x_a, y_a, jx, jy)
            d_b_junc = get_dist(x_b, y_b, jx, jy)

            # Check V2V Connection
            if dist_v2v < COMM_RANGE and not collision_prevented:
                # print(f"Time {traci.simulation.getTime()}: V2V Active. Dist to Junction: A={d_a_junc:.1f}m, B={d_b_junc:.1f}m")
                
                # 3. SAFETY LOGIC
                # If BOTH cars are rushing toward the center (within 45m)
                if d_a_junc < CRITICAL_DIST and d_b_junc < CRITICAL_DIST:
                    print(f"!!! ALERT Time {traci.simulation.getTime()}: Collision Predicted!")
                    print(f"    -> Distances to center: A={d_a_junc:.1f}m, B={d_b_junc:.1f}m")
                    print("    -> ACTION: Emergency V2V Stop initiated for Vehicle B")
                    
                    # Force stop immediately
                    traci.vehicle.setSpeedMode("veh_B", 0) # Ensure we have control
                    traci.vehicle.slowDown("veh_B", 0.0, 1.0) # Stop in 1 second
                    traci.vehicle.setColor("veh_B", (255, 0, 0, 255)) # Red
                    
                    collision_prevented = True

        step += 1
    
    traci.close()

if __name__ == "__main__":
    run()