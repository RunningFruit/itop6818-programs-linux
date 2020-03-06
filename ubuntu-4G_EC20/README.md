

编译 ppp 拨号工具
```
tar xvf ppp-2.4.4.tar.gz;cd ppp-2.4.4
./configure
make CC=arm-linux-gnueabihf-gcc
ls pppd/pppd
ls chat/chat
```

拷贝工具
```
cp pppd /usr/sbin/
cp chat /usr/sbin/

cp wcdma /etc/ppp/peers/
cp wcdma-chat-connect /etc/ppp/peers/
cp wcdma-chat-disconnect /etc/ppp/peers/
```

最后在开发板执行以下指令，建立软连接
```
ln /lib/ld-linux-armhf.so.3 /lib/ld-linux.so.3
```

测试
```
首先将天线安装到开发板上，插入手机卡后重启开发板
#在开发板执行
./pppd_conf.sh &

ping www.baidu.com -c 4 -I ppp0
```
