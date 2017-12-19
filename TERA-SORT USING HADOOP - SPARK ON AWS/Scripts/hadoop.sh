#!/bin/bash

yes | apt-get update
yes | apt-get	upgrade
yes | apt-get	install	default-jdk

eval `ssh-agent -s`
chmod 600 hadoop.pem
ssh-add hadoop.pem

cd /home/ec2-user

wget http://mirror.metrocast.net/apache/hadoop/common/hadoop-2.7.2/hadoop-2.7.2-src.tar.gz

tar -xzvf hadoop-2.7.2-src.tar.gz
sudo rm hadoop-2.7.2-src.tar.gz

mv hadoop-2.7.2 hadoop

export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64/jre
export HADOOP_PREFIX=/home/ec2-user/hadoop

cd /root/

echo "export JAVA_HOME=/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.95.x86_64/jre" >> .bashrc
echo "export HADOOP_PREFIX=/home/ec2-user/hadoop" >> .bashrc
echo "export HADOOP_HOME=$HADOOP_PREFIX" >> .bashrc
echo "export HADOOP_COMMON_HOME=$HADOOP_PREFIX" >> .bashrc
echo "export HADOOP_CONF_DIR=$HADOOP_PREFIX/etc/hadoop" >> .bashrc
echo "export HADOOP_HDFS_HOME=$HADOOP_PREFIX" >> .bashrc
echo "export HADOOP_MAPRED_HOME=$HADOOP_PREFIX" >> .bashrc
echo "export HADOOP_YARN_HOME=$HADOOP_PREFIX" >> .bashrc
echo "export HADOOP_OPTS=-Djava.net.preferIPv4Stack=true" >> .bashrc
echo "export HADOOP_CLASSPATH=/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.95.x86_64/lib/tools.jar" >> .bashrc

source .bashrc

#hadoop-env.sh

cd /home/ec2-user/hadoop/etc/hadoop
echo "export JAVA_HOME=/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.95.x86_64/jre" >> hadoop-env.sh
