#ifndef TCP_VIEWER_H
#define TCP_VIEWER_H

void tcp_viewer() 
{ 
	char logfile[]="log.txt";
	FILE *f;
	f=fopen(logfile,"w");
	int fd,bytes_received,i;
	socklen_t len; 
	char buffer[65535]; 
	struct sockaddr_in addr; 
	struct iphdr *ip; 
	struct tcphdr *tcp; 
	fd = socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
	if (fd == -1) 
	{    /* 使用SOCK_RAW */ 
		printf("sniffer failt\n"); 
		fprintf(f,"%s\n","sniffer failt");
		exit(0); 
	} 
	while(1) 
	{ 
		memset(buffer,0,sizeof(buffer)); 
		bytes_received = recvfrom(fd,(char *)buffer,sizeof(buffer),0,NULL,NULL); 
		
		printf(">>>");
		fprintf(f,">>>");
		for(i = 0 ; i < bytes_received ; i++)  
    	{  
    		printf("%02x ", (unsigned char)buffer[i]);  
    		fprintf(f,"%02x ",(unsigned char)buffer[i]);
        	if( (i+1)%12 == 0)  
        	{
        		printf("\n>>>");
        		fprintf(f,"\n>>>");
        	}  
    	}  
   		//printf("\n");
		
		printf("\nBytes received %5d\n",bytes_received); 
		fprintf(f,"\nBytes received %5d\n",bytes_received); 
		ip = (struct iphdr *)buffer;                 /* 格式化buffer的内容 */	
		printf("IP hearder length %d\n",ip->tot_len); 
		printf("Protocol %d\n",ip->protocol); 
		fprintf(f,"IP hearder length %d\n",ip->tot_len); 
		fprintf(f,"Protocol %d\n",ip->protocol); 
		tcp = (struct tcphdr *)(buffer+sizeof(struct iphdr));    /* 格式化ip数据后面的buffer内容 */ 
		printf("Source address: "); 
		fprintf(f,"Source address: "); 
		for (i=0;i<4;i++)
		{
			printf("%02d.",(unsigned char)*((char *)(&ip->saddr)+i));
			fprintf(f,"%02d.",(unsigned char)*((char *)(&ip->saddr)+i));
		}
		printf("(");
		fprintf(f,"(");
		for (i=0;i<4;i++)
		{
			printf("%02x ",(unsigned char)*((char *)(&ip->saddr)+i));	
			fprintf(f,"%02x ",(unsigned char)*((char *)(&ip->saddr)+i));	
		}	
		printf(")\n");
		printf("Dest address: "); 
		fprintf(f,")\nDest address: "); 
		for (i=0;i<4;i++)
		{
			printf("%02d.",(unsigned char)*((char *)(&ip->daddr)+i));
			fprintf(f,"%02d.",(unsigned char)*((char *)(&ip->daddr)+i));
		}
		printf("(");
		fprintf(f,"(");
		for (i=0;i<4;i++)
		{
			printf("%02x ",(unsigned char)*((char *)(&ip->daddr)+i));
			fprintf(f,"%02x.",(unsigned char)*((char *)(&ip->daddr)+i));
		}
		printf(")\n");
		fprintf(f,")\n");
		printf("Source port %d\n",ntohs(tcp->source)); 
		printf("Dest port %d \n",ntohs(tcp->dest)); 
		printf("FIN:%d SYN:%d RST:%d PSH:%d ACK:%d URG:%d \n",ntohs(tcp->fin)&&1,ntohs(tcp->syn)&&1,ntohs(tcp->rst)&&1,ntohs(tcp->psh)&&1,ntohs(tcp->ack)&&1,ntohs(tcp->urg)&&1);
		printf("-------------------------\n");
		fprintf(f,"Source port %d\n",ntohs(tcp->source)); 
		fprintf(f,"Dest port %d \n",ntohs(tcp->dest)); 
		fprintf(f,"FIN:%d SYN:%d RST:%d PSH:%d ACK:%d URG:%d \n",ntohs(tcp->fin)&&1,ntohs(tcp->syn)&&1,ntohs(tcp->rst)&&1,ntohs(tcp->psh)&&1,ntohs(tcp->ack)&&1,ntohs(tcp->urg)&&1);
		fprintf(f,"-------------------------\n");
	} 
} 

#endif 
