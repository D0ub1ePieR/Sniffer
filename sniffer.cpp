#include"header.h"
#include"set_promisc.h"

struct etherpacket
{
	struct ethhdr eth;
	struct iphdr ip;
	struct tcphdr tcp;
	char buff[8192];
}ep;

int main(int argc,char *argv[])
{
	set_promisc(argc,argv);
}
