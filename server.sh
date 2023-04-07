ip=192.168.1.51
port=8081
usbs=/dev/ttyUSB0
printf "\ec\e[44;30m"
echo "start serial server"
sudo ifconfig | grep "inet"
while true
do
sudo socat -d -d STDOUT TCP4-listen:$port  
done
