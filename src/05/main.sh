ssh ci@192.168.56.7 "mkdir -p /home/ci/src"
scp -r /home/test/DO6_CICD-2/src/* ci@192.168.56.7:/home/ci/src
echo "312" | sshpass -p "312" ssh ci@192.168.56.7 "sudo -S rsync -a /home/ci/src /usr/local/bin"
ssh ci@192.168.56.7 "rm -rf /home/ci/src"

