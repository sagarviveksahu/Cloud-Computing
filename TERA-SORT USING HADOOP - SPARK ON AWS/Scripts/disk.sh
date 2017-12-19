#!/bin/bash

eval `ssh-agent -s`

ssh-add hadoop.pem

mdadm

mdadm --create --verbose /dev/md0 --level=0 --name=MY_RAID --raid-devices=2 /dev/xvdb /dev/xvdc

mkfs.ext4 -L MY_RAID /dev/md0

mkdir -p /mnt/raid

mount LABEL=MY_RAID /mnt/raid

chmod 777 /mnt/raid/

rm -Rf /mnt/raid/hdfs/*
rm -Rf /mnt/raid/tmp/*

cd /mnt/raid/

mkdir -p tmp
mkdir -p tmp/hadoop-ec2-user
mkdir -p tmp/namenode
mkdir -p tmp/datanode
