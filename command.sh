printf "\ec\e[44;30m"
echo "start tcp command line server"
rm -f /tmp/f; mkfifo /tmp/f
nc -l 1234 < /tmp/f | sh > /tmp/f