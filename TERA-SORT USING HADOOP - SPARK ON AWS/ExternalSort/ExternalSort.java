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
public class ExternalSort extends Thread {

    List<String> data ;
    String dir;
    int fileNum;
    long chunkSize;
    public ExternalSort(List<String> ltr,String dir,int fileNum,long chunkSize) {
        this.data = ltr;
        this.dir = dir;
        this.fileNum = fileNum;
        this.chunkSize = chunkSize;
    }

    public void run() {
        String file = dir + "/temp" + fileNum + ".txt";
        int len = data.size();
        mergesort(data, 0, len - 1);
        FileWriter fw=null;
        try {
            fw = new FileWriter(file);
        int i = 0;
        while (i < len) {
                fw.write(data.get(i++) + "\n");
        }
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

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
