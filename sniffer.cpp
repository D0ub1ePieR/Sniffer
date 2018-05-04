#include"header.h"

struct etherpacket
{
	struct ethhdr eth;
	struct iphdr ip;
	struct tcphdr tcp;
	char buff[8192];
}ep;

int main()
{}
