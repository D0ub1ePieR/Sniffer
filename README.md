# Sniffer
一个简单的linux系统下的sniffer，可以解析tcp报文 <br>
屏幕输出以及在log.txt中记录所有信息 <br>
# 用法
gcc -o sniffer sniffer.cpp <br>
./sniffer <interface> <br>
提供网卡名称则尝试使用对应网卡，否则自动获取主机网卡名称 <br>
# 对于tcp报文
输出报文内容，源ip目标ip，源端口目标端口，六个标志位的具体值
