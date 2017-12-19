import java.io.IOException;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import java.util.StringTokenizer;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.commons.lang.time.StopWatch;

public class teraSort
{

        public static class teraSortMapper extends Mapper<LongWritable, Text, Text, Text>
        {
                  private Text keySet;
                  private Text valueSet;

                public void map(LongWritable key, Text value, Context context) throws IOException,InterruptedException {

                  String token = null;
                  StringTokenizer tokenizer;

                  tokenizer = new StringTokenizer(value.toString(),"\n");
                  keySet = new Text();
                  valueSet = new Text();

                  while (tokenizer.hasMoreTokens()) {

                        token = tokenizer.nextToken();
                        keySet.set(token.substring(0,10));
                        valueSet.set(token.substring(12,98));
                        context.write(keySet,valueSet);
                  }
                }
        }

        public static class teraSortReducer extends Reducer<Text, Text, Text, Text>
        {
                public void reduce(Text key, Iterable<Text> values, Context context) throws IOException,InterruptedException
                {
                  String sort = null;

                  for (Text value : values)
                        {
                                sort = value.toString()+ "\n";
                        }
                  context.write(key , new Text(sort));
                }
        }

        private static class RandomConstant {

          final Unsigned16 aa;
          final Unsigned16 cc;

          public RandomConstant(String left, String right) {

            aa = new Unsigned16(left);
            cc = new Unsigned16(right);
          }
        }

        public static void nextRand(Unsigned16 rand) {
    /* advance the random number forward once using the linear congruential
     * generator, and then return the new random number
     */
        rand.multiply(genArray[0].aa);
        rand.add(genArray[0].cc);
      }

        public static void main(String[] args) throws Exception
       {
                long startTime;
                long stopTime;
                long elapsedTime;
                startTime = System.currentTimeMillis();
                Configuration config;
                config = new Configuration();
                Job schedular = Job.getInstance(config, "Hadoop_Sort");
                schedular.setJarByClass(teraSort.class);
                schedular.setMapperClass(teraSortMapper.class);
                schedular.setCombinerClass(teraSortReducer.class);
                schedular.setReducerClass(teraSortReducer.class);
                schedular.setOutputKeyClass(Text.class);
                schedular.setOutputValueClass(Text.class);
                FileInputFormat.addInputPath(schedular, new Path(args[0]));
                FileOutputFormat.setOutputPath(schedular, new Path(args[1]));
                System.exit(schedular.waitForCompletion(true) ? 0 : 1);
                stopTime = System.currentTimeMillis();
                elapsedTime = stopTime - startTime;
                System.out.println(elapsedTime);
  }
}
