#!/bin/bash
scp -r ~/DO6_CICD-1/* ci@192.168.56.7:/tmp/
ssh ci@192.168.56.7  "sudo -S mv /tmp/* /usr/local/bin/" <<< "312"
