#ifndef ETH_ARP_UTILS_H
#define ETH_ARP_UTILS_H
#if !defined(LITE_VERSION)
#include "Arduino.h"
#include "FS.h"

// Shared by ARPSpoofer and ARPoisoner: builds and sends a spoofed ARP reply, optionally
// capturing it to pcapFile. sentLogMsg is the caller-specific line printed once the packet
// is on the wire, so each module keeps its own log wording.
void sendARPPacket(
    uint8_t *targetIP,
    uint8_t *targetMAC,
    uint8_t *spoofedIP,
    uint8_t *spoofedMAC,
    File pcapFile,
    const char *sentLogMsg
);

// Shared by MACFlooding and DHCPStarvation: fills a 6-byte MAC address with random octets.
void randomizeMac(uint8_t *mac);

#endif
#endif
