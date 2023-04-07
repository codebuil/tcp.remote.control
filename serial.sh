ip=192.168.1.48
port=8081
usbs=/dev/ttyUSB0
printf "\ec\e[44;30m"
echo "start serial client server"
sudo ifconfig | grep "inet"
sudo socat -d -d  pty,raw,link=$usbs,b9600,echo=0 TCP4:$ip:$port &
while true
do
read a
echo $a > $usbs
done
