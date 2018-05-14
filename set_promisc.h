#ifndef SET_PROMISC_H
#define SET_PROMISC_H

//设置混杂模式
void procedure(char *interface, int fd) 
{      
	struct ifreq ifr;                    // ifreg结构
	strncpy(ifr.ifr_name, interface, strlen(interface)+1);  //设置网卡名称
	if(ioctl(fd, SIOCGIFFLAGS, &ifr) == -1) 
	{      //接收网卡信号 
		printf("Could not retrive flags for the interface\n"); 
		perror("ioctl");
		exit(0); 
	} 
	printf("The interface is < %s >\n", interface); 
	ifr.ifr_flags |= IFF_PROMISC;              // 设置网卡信号为 IFF_PROMISC 
	if( ioctl(fd, SIOCSIFFLAGS, &ifr) == -1 ) 
	{ 
		printf("Could not set the PROMISC flag.\n"); 
		perror("ioctl");
		exit(0); 
	} 
	printf("Setting interface < %s > to promisc mode\n", interface); 
} 

//用户未指定网卡名，从主机获取网卡名称
void get_interface(char *it)
{
	FILE *shell;
	shell=popen("/sbin/ifconfig | grep ' Link' | grep -v 'Local' | awk -F ' ' '{print $1}'","r");
	//过滤本地网卡名，获取到连接外部网络的网卡名称
	if (shell==NULL)
	{
		perror("popen");
		exit(0);
	}
	fscanf(shell,"%s",it);
	pclose(shell);
}

void set_promisc(int argc, char *argv[]) 
{ 
	int fd; 
	char interface[30];     
	if(argc == 1)     
		get_interface(interface); 
	else if(argc ==2) 
		strcpy(interface, argv[1]); 
	else if(argc >2) 
		{ 
			printf("usage: %s <interface> \n",argv[0]); 
			exit(0); 
		} 
	fd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);	// 定义套接字为SOCK_RAW
	if(fd < 0) 
	{ 
		printf("The raw socket was not created\n"); 
		exit(0); 
	} 
	procedure(interface, fd); 
} 

#endif

