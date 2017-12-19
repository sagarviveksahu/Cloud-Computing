from pyspark import SparkContext
from pyspark import SparkConf
import sys

if __name__ == "__main__":

	sortedFile = sc.textFile("hdfs://PUBLIC DNS :9000/user/hadooo/input/spark_tera_10gb.txt")

	sortedObj = sortFile.flatMap(lambda line:ine.split("\n")).map(lambda dicto:(str(dicto[:10]),str(dicto[10:]))).sortByKey().map(lambda (a,b) : a+b)

	sortedObj.saveAsTextFile("hdfs://Public DNS :9000/user/hadoop/output_filnal")
