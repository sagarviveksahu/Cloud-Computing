————————————————SharedMemory————————————

To run the java program 

javac DataChunks.Java

javac ExternalSort.java

Java DataChunks


Instruction to run shared memory sort:
$gensort –a 1280000000 input
$sudo apt-get install default-jdk
$mkdir tempfile
$Javac DataChunk.java
$Javac ExternalSort.java
$java DataChunk.java

Shared Memory 128 GB External Sorting:

//ExternalSort Implementation
/**
 * @author Suraj Didwania
 * External Sorting on 128 GB using i3.large instance Implementation
 * task: Provide the input file and implement the external sort using in-place merge sort
 */
Function to divide the files into chunks
Merge the temp files into output file from temp dir

Shared memory performed on Virtual Cluster (1-node i3.large) and Virtual Cluster (1-node i3.4xlarge)
Sorting techniques used:
In-place merge sort.
2 Threads have been used



---------------------------------Hadoop Steps---------------------------------------

1. Upload your pem file on AWS instance.
	eval `ssh-agent -s`
	chmod 600 Hadoop.pem
	ssh-add Hadoop.pem


2. Mount additional drives

	bash disk.sh

3.Format Hadoop namenode.
 	hadoop namenode -format


4.Start all the services from the hadoop/sbin:
	./hadoop/sbin/start-dfs.sh
	./hadoop/sbin/start-yarn.sh


->  Check on master and slave both for the active running services:
	jps


5. Write your Java File and make jar file, add class file to jar.

	hadoop com.sun.tools.javac.Main javafile.java
	jar cf JAR_NAME.jar javafile*.class


6. Generate data file with gensort.
	./gensort -a numoflines path/name


7. Put generated data on hadoop file system.
	hadoop fs -mkdir /input
	hadoop fs -mkdir /output
	Hadoop fs -put file_path/file_name /input/in


8. Run the Program:
	hadoop jar ts.jar Terasort input_path output_path


9. Store output from hadoop fs to local fs and validate it:
	hadoop fs -get output/* /path
	mv generated_outputname output_file_name


11. validate it with valsort:
	./valsort output_file_name




----------------------------------------Spark Steps------------------------------------------




1. Mount extra disk space:

	bash disk.sh


2. Put Python Program in same folder as Pyspark-shell.


3. Slave nodes are come with drive mounted, to run program go to following path:
	cd spark/
------Open Spark Shell:
	./pyspark

3. •	Copy and paste following command into shell

  sortedFile = sc.textFile("hdfs://PUBLIC DNS :9000/user/hadooo/input/in")

  sortedObj = sortFile.flatMap(lambda line:ine.split("\n")).map(lambda dicto:(str(dicto[:10]),str(dicto[10:]))).sortByKey().map(lambda (a,b) : a+b)

  sortedObj.saveAsTextFile("hdfs://Public DNS :9000/user/hadoop/output/out")


4. To checck the output data:

	./hadoop fs -ls /output/

5. To fetch data from output folder, run following commands:

	./hadoop fs -get /output/File_number /mnt/raid/

-> It will fetch data from hadoop file system and store it into drive

MPI:
Message Passing interface uses the same program as the external sort by not implemeneting thread but scattering the program into chunks. I have used Java Bindings for Open MPI
Our approach is based on the Java Native Interface (JNI), a mechanism that allows the application programmer to call native subroutines and libraries from Java and vice versa.
JNI communication usually takes place in the Java-C direction.
It picks up the respective file based on ranks and performing sorting bybusing inplace merge sort.
All the process ranks other than zero has been finished the proram, it finishes the giving the executuion output to rank 0 process.
Each chunk is divided by number of processors and root node passes(scatters) the data.
4. Each processor gets a rank and sorts the piece of chunk
5. Root node gathers data and writes the sorted chunk to temporary sort 
