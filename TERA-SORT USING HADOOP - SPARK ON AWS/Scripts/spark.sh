
yes | apt-get update
yes | apt-get	upgrade
yes | apt-get	install	default-jdk

eval `ssh-agent -s`
chmod 600 hadoop.pem
ssh-add hadoop.pem

cd /home/ec2-user

wget http://mirrors.sonic.net/apache/spark/spark-1.6.1/spark-1.6.1-bin-hadoop2.6.tgz

tar -xvzf spark-1.6.1-bin-hadoop2.6.tgz
sudo rm spark-1.6.1-bin-hadoop2.6.tgz

mv spark-1.6.1 spark

export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64/jre
export SCALA_HOME=/usr/local/src/scala/scala-2.10.4
export PATH=$SCALA_HOME/bin:$PATH


cd /root/

echo "export JAVA_HOME=/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.95.x86_64/jre" >> .bashrc
echo "export SCALA_HOME=/usr/local/src/scala/scala-2.10.4" >> .bashrc
echo "export PATH=$SCALA_HOME/bin:$PATH" >> .bashrc
echo "export  PYSPARK_PYTHON=/usr/bin/python3.5" >> .bashrc
echo "export  PYTHONPATH=$SPARK_HOME/python/:$PYTHONPATH" >> .bashrc
echo "export  PYTHONPATH=$SPARK_HOME/python/lib/py4j-0.10.4-src.zip:$PYTHONPATH" >> .bashrc
