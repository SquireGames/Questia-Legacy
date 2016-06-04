#ifndef PACKET_H
#define PACKET_H

struct pkt
{
    //packet
    enum Header
    {
        //init
        playerLogin = 1, svrResp = 2, playerNewAcc = 3,
        //in game entities
        other = 10, player = 11, playerContainer = 12, entity = 13, entityContainer = 14
    };
};

// used for udp packets
struct Packet
{
public:
    Packet();
    ~Packet();
};

#endif // PACKET_H
