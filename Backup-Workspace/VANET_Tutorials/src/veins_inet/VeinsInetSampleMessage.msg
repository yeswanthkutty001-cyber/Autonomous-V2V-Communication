import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;

class VeinsInetSampleMessage extends inet::FieldsChunk
{
    string senderId;
    double posX;
    double posY;
    bool requestJunction = false;
}