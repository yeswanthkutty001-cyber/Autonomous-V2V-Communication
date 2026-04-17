package vanet_tutorials.simulations.Intersection;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.AdhocHost;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import org.car2x.veins.base.connectionManager.ConnectionManager;
import org.car2x.veins.base.modules.BaseWorldUtility;
import org.car2x.veins.modules.obstacle.ObstacleControl;
import org.car2x.veins.modules.world.annotations.AnnotationManager;
import vanet_tutorials.veins_inet.VeinsInetManager;

network V2VIntersectionScenario
{
    parameters:
        double playgroundSizeX @unit(m) = default(2500m);
        double playgroundSizeY @unit(m) = default(2500m);
        double playgroundSizeZ @unit(m) = default(50m);
        @display("bgb=$playgroundSizeX,$playgroundSizeY");

    submodules:
        obstacles: ObstacleControl {
            @display("p=100,50");
        }

        annotations: AnnotationManager {
            @display("p=100,150");
        }

        connectionManager: ConnectionManager {
            @display("p=100,250");
        }

        world: BaseWorldUtility {
            parameters:
                playgroundSizeX = playgroundSizeX;
                playgroundSizeY = playgroundSizeY;
                playgroundSizeZ = playgroundSizeZ;
                @display("p=100,350");
        }

        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=100,450");
        }

        configurator: Ipv4NetworkConfigurator {
            config = default(xml("<config><interface hosts='*' address='10.x.x.x' netmask='255.x.x.x'/></config>"));
            @display("p=100,550");
        }

        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer if hasVisualizer() {
            @display("p=100,650");
        }

        manager: VeinsInetManager {
            @display("p=100,750");
        }

    connections allowunconnected:
}