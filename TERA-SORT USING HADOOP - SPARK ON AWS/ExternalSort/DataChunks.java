import java.io.*;
import java.util.*;

/*=========================================================*/
/*       					         					   */
/*	         External Sort Implementaion			       */
/*						       							   */
/*=========================================================*/

//ExternalSort Implementation
/**
 * @author Suraj Didwania
 * External Sorting on 128 GB using i3.large instance Implementation
 * task: Provide the input file and implement the external sort using in-place merge sort
 */

class DataChunks {

    public static int filenum=0;
    public synchronized static void setFilenum() {
        filenum++;
    }
    public static void runningThread(int noThread,List<String> lt,String dir) throws InterruptedException {
        Thread[] thr = new Thread[noThread];
        int val = (int) (Math.ceil(lt.size() / noThread));
        int k=0;
        while(k<noThread){
            List<String> ltr = new ArrayList<>();
            int start = 0;
            for (int j = start; j < val + start; j++) {
                if (j >= lt.size()) break;
                ltr.add(lt.get(j));
                start+= val;
            }
            thr[k] = new ExternalSort(ltr, dir,filenum,ltr.size());
            thr[k++].start();
        }
            setFilenum();
            for (int i = 0; i < noThread; i++) thr[i].join();
    }
    public static int dividingdata(String inputFile, String dir, int noThread) throws IOException, InterruptedException {
        FileReader fr = new FileReader(inputFile);
        BufferedReader br = new BufferedReader(fr);
        String str;
        List<String> lt = new ArrayList<>();
        while ((str = br.readLine()) != null) {
            lt.add(str);
            if (lt.size() == 20000) {
                runningThread(noThread,lt,dir);
                lt = new ArrayList<>();
            }
        }
        br.close();
        if (lt.size() != 0 && lt.size() < 20000) {
            runningThread(noThread,lt,dir);
        }
        return filenum;
    }

    public static void mergeFiles(int noOfFiles,String outputFile, String dir) throws IOException {
        BufferedReader[] br = new BufferedReader[noOfFiles];
        Map<String,String> mp = new TreeMap<>();
        for(int i=0;i<noOfFiles;i++) {
            FileReader fr = new FileReader(dir + "/temp" + i + ".txt");
            br[i] = new BufferedReader(fr);
            String str;
            if ((str = br[i].readLine()) != null) {
                String key = str.substring(0, 10);
                String value = i + "##" + str.substring(10);
                mp.put(key, value);
            }
        }
        FileWriter fw = new FileWriter(outputFile);
        BufferedWriter br1 = new BufferedWriter(fw);
        while(!mp.isEmpty()) {
            String str = mp.keySet().iterator().next();
            String val = mp.get(str);
            StringTokenizer st =new StringTokenizer(mp.get(str), "##");
            int filenum = Integer.parseInt(st.nextToken());
            mp.remove(str);
            br1.write(str+st.nextToken());
            br1.write("\n");
            br1.flush();
            str = br[filenum].readLine();
            if(str != null ) {
                String key = str.substring(0,10);
                val = filenum+"##"+str.substring(10);
                mp.put(key, val);
            }
        }
        br1.close();
        //Deleting all the temporary files and closing all the buffer readers.
        for(int i=0; i<br.length; i++) {
            try{
                if(br[i] != null)
                    br[i].close();
                new File(dir+"/temp" +i+".txt").delete();
            }catch(FileNotFoundException ffe){}
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        String inputfile = "input";
        String outputfile = "output";
        String tempDir = "tempfile";
        int thread = 2;
        long startTime = System.currentTimeMillis();
        int noOfFiles= dividingdata(inputfile,tempDir,Integer.valueOf(thread)); //Function to divide the files into chunks
        mergeFiles(noOfFiles,outputfile,tempDir); // Merge the temp files into output file from temp dir
        long endTime = System.currentTimeMillis();
        int time = (double)(endTime-startTime)/1000;
        System.out.println(thread +" threads Time taken = " +time+ " seconds");
    }

}
