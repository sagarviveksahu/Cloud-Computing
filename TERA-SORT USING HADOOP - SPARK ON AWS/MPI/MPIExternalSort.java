

import java.io.*;
import java.util.*;
import java.util.logging.Logger;

import mpi.Intracomm;
import mpi.MPI;
import mpi.MPIException;

/*=========================================================*/
/*       					         					   */
/*	         1TB External Sort Implementaion			   */
/*						       							   */
/*=========================================================*/

//ExternalSort on 1TB Implementation
/**
 * @author Suraj Didwania
 * External Sorting on 1TB using i3.4xlarge instance on EC2 Implementation
 * task: Provide the input file and implement the external sort using in-place merge sort
 */

public class MPIExternalSort extends Thread {


    //In-Place merge sort
    public void mergesort(List<String> array, int start, int end)
    {
        if(start<=end) return;
        int mid = (end+start)/2;
        mergesort(array,0,mid);
        mergesort(array,mid+1,end);
        merge(array,start,mid,end);
    }
    public void merge(List<String> array, int start,int mid, int end)
    {
        if(mid<=start || mid>end) return;
        int left = mid-1;
        int right = mid;
        while(left>=start && right<=end && (array.get(left).compareTo(array.get(right))>1)) left--; right++;
        rotate(array, left+1, mid, right-1);
        merge(array, start, left+1, mid);
        merge(array, mid+1, right, end);
    }
    void rotate(List<String> array, int start, int newStart, int end)
    {
        reverse(array, start, newStart-1);
        reverse(array, newStart, end);
        reverse(array, start, end);
    }

    void reverse(List<String> array, int start, int end)
    {
        while (start<end)
        {
            String tmp = array.get(start);
            array.set(start++,array.get(end));
            array.set(end--,tmp);
        }
    }

}
class DataChunk {

    public static int filenum=0;
    public synchronized static void setFilenum() {
        filenum++;
    }
    public static void runningThread(int noThread,List<String> lt,String dir) throws InterruptedException {
        int val = (int) (Math.ceil(lt.size() / noThread));
        List<String> ltr = new ArrayList<>();
            int start = 0;
            for (int j = start; j < val + start; j++) {
                if (j >= lt.size()) break;
                ltr.add(lt.get(j));
                start = start + val;
            }
            /********** Initialize MPI **********/
            int world_rank;
            int world_size;
            MPI.Init(args);

            int rank = MPI.COMM_WORLD.getRank();
            int size = MPI.COMM_WORLD.getSize();
            MPI.COMM_WORLD.reduce(ltr, ltr.size(), MPI_INT, MPI.INT, 0, MPI.COMM_WORLD);

            MPI.Finalize();
        setFilenum();
    }
    public static int dividingdata(String inputFile, String dir, int noThread) throws IOException, InterruptedException {
        FileReader fr = new FileReader(inputFile);
        private static Logger LOG = Logger.getLogger(DataChunk.class.getName());
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
        Comm comm = MPI.COMM_WORLD;
        int me = comm.getRank();

        if (me == 0) {
            comm.send(data, 5, MPI.DOUBLE, 1, 1);
        } else if (me == 1) {
            Status status = comm.recv(data, 5, MPI.DOUBLE, MPI.ANY_SOURCE, 1);
            int count = status.getCount(MPI.DOUBLE);
            int src = status.getSource();
            System.out.println("Received "+ count +" values from "+ src);
        }
        return filenum;
    }

    public static void mergeFiles(int noOfFiles,String outputFile, String dir) throws IOException {
        BufferedReader[] br = new BufferedReader[noOfFiles];
        Map<String,String> mp = new TreeMap<>();
        for(int i=0;i<noOfFiles;i++) {
            FileReader fr = new FileReader(dir + "/temp-" + i + ".txt");
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
                new File(dir+"/temp-" +i+".txt").delete();
            }catch(FileNotFoundException ffe){}
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        String inputfile = "input";
        String outputfile = "output";
        String tempDir = "tempfile";
        int thread = 2;
        long startTime = System.currentTimeMillis();
        int noOfFiles= dividingdata(inputfile,tempDir,Integer.valueOf(thread));
        mergeFiles(noOfFiles,outputfile,tempDir);
        long endTime = System.currentTimeMillis();
        System.out.println(thread +"Threads Time taken = " +(double)(endTime-startTime)/1000 + " seconds");
    }

}
