#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <signal.h> 
#include <netinet/in.h> 
#include <net/if.h> 
#include <netdb.h> 
#include <sys/ioctl.h> 
#include <sys/stat.h> 
#include <fcntl.h> 

int set_promisc(char *interface, int sock ) 
{      /* 杂乱模式函数 */ 
	struct ifreq ifr;                    /* ifreg结构 */ 
	strncpy(ifr.ifr_name, interface,strlen(interface)+1);  /* 输入网卡名 */ 
	if((ioctl(sock, SIOCGIFFLAGS, &ifr) == -1)) 
	{      /* 接收网卡信号 */ 
		printf("Could not retrive flags for the interface\n"); 
		exit(0); 
	} 
	printf("The interface is ::: %s\n", interface); 
	ifr.ifr_flags |= IFF_PROMISC;              /* 设置网卡信号 = IFF_PROMISC */ 
	if(ioctl(sock, SIOCSIFFLAGS, &ifr) == -1 ) 
	{ 
		printf("Could not set the PROMISC flag.\n"); 
		exit(0); 
	} 
	printf("Setting interface ::: %s ::: to promisc mode\n", interface); 
} 

char INTERFACE[]="ens33";          /* 默认网卡 */ 
main(int argc,char *argv[]) 
{ 
	int sock; 
	char *inter;     
	if(argc == 1)     
		inter = INTERFACE; 
	if(argc ==2) 
		inter = argv[1]; 
	if(argc >2) 
	{ 
		printf("usage: %s <interface> \n",argv[0]); 
		exit(0); 
	} 
	if((sock = socket(AF_INET,SOCK_RAW,IPPROTO_TCP)) <0) 
	{ /* 定义套接字为SOCK_RAW */ 
		printf("The raw socket was not created\n"); 
		exit(0); 
	} 
	set_promisc(inter,sock); 
} 


