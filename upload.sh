#!/bin/bash

read -s -p "Password: " password

echo "Start uploading"
sshpass -p $password scp -r src stage@131.211.54.64:~/Documents/HybridProcessor/
sshpass -p $password scp -r make stage@131.211.54.64:~/Documents/HybridProcessor/
sshpass -p $password scp compile.sh stage@131.211.54.64:~/Documents/HybridProcessor/
# sshpass -p $password scp compile-evo.sh stage@131.211.54.64:~/Documents/HybridProcessor/
sshpass -p $password scp server.par stage@131.211.54.64:~/Documents/HybridProcessor/
# sshpass -p $password scp example.sh stage@131.211.54.64:~/Documents/HybridProcessor/
echo "Uploading done"
