#include"header.h"
#include"set_promisc.h"
#include"tcp_viewer.h"
#include<iostream>
#include<fstream>
using namespace std;

int main(int argc,char *argv[])
{
	set_promisc(argc,argv);
	tcp_viewer();
}
