
// 原始套接字
#include "../header.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_arp.h>
int main()
{
    // PF_PACKET, AF_INET=PF_INET
    int sock = socket(AF_PACKET, SOCK_RAW, htons(IPPROTO_IP));

    // sock需要端口么？？
    // 给sock绑定网口
    // sockaddr sockaddr_in sockaddr_ll sockaddr_un
    struct sockaddr_ll addr;
    addr.sll_family = AF_PACKET;
    addr.sll_protocol = htons(ETH_P_ALL); // ETH网，所有协议
    addr.sll_hatype = ARPHRD_ETHER;
    addr.sll_pkttype = PACKET_OTHERHOST;
    addr.sll_halen = ETH_ALEN;
    addr.sll_addr[6]  = 0;
    addr.sll_addr[7]  = 0;

    // fcntl <--> ioctl
    struct ifreq ifstruct;
    strcpy(ifstruct.ifr_name, "eth0"); // 网卡接口名
    if (ioctl(sock, SIOCGIFHWADDR, &ifstruct) == -1)
    {
        printf("\nioctl SIOCGIFHWADDR [%s] Error!!!","eth0" );
        exit(1);
    }
    memcpy(addr.sll_addr, ifstruct.ifr_ifru.ifru_hwaddr.sa_data, ETH_ALEN);

    // 获取flags
    if (ioctl(sock, SIOCGIFFLAGS, &ifstruct) < 0)
    {
        printf("ioctl SIOCGIFFLAGS [%s] Error!!!",  "eth0");
        exit(1);
    }

    // 混杂模式，网卡的调试模式
    ifstruct.ifr_flags |= IFF_PROMISC;//set promisc
    if (ioctl(sock, SIOCSIFFLAGS, &ifstruct) == -1)
    {
        printf("set promisc error\n");
        exit(1);
    }

    if (ioctl(sock, SIOCGIFINDEX, &ifstruct) == -1)//指定socket，把信息存入到ifstruct中
    {
        exit(1);
    }

    addr.sll_ifindex = ifstruct.ifr_ifindex;

    int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    if(ret < 0)
    {
        exit(1);
    }

    printf("bind success\n");

    unsigned char buf[1518];
    while(1)
    {
        ret = read(sock, buf, sizeof(buf));
        if(ret < 0)
        {
            printf("read error");
            return 0;
        }

        if(memcmp(buf, addr.sll_addr, ETH_ALEN) != 0) continue;

        printf("dest mac addr: %02x:%02x:%02x:%02x:%02x:%02x\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

        unsigned short* type = (unsigned short*)(buf+12);
        if(ntohs(*type) == 0x0800)
        {
            // IP报文
            unsigned char* ip = buf+14;
            int header = ip[0] & 0xf;
            printf("header, %02x\n", header);
            printf("version, %02x\n", (ip[0] & 0xf0) >> 4);

            unsigned short total_len = *(unsigned short*)(ip + 2);
            total_len = ntohs(total_len);
            printf("ip total len = %d\n", total_len);

            unsigned int destip = *(unsigned int*)(ip + 16);
            printf("dest ip addr=%08x\n", destip);

            unsigned char protocol = ip[9]; // 6 or 17(0x11)
            printf("protocol = %x\n", protocol);

            // ip数据部分
            unsigned char* data = ip + header * 4; // udp or tcp

            if(protocol == 6)
            {
                unsigned char* tcp = data;
                int header = (tcp[12] & 0xf0) >> 4;
                unsigned char* data = tcp + header * 4;

                printf("tcp data is: %s\n", data);
            }
        }
        printf("packet type is %04x\n", (*type));
    }
}
