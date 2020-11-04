import java.io.*;
import java.util.Scanner;


public class Lex {
   public static void main(String[] args) throws IOException {
      
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      int lineNumber = 0;

      int outi = 0; //for writing output
      
      if(args.length != 2) {
         System.err.println("Usage error: requires 2 command line arguments");
         System.exit(1);
      }
      
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));
      List L = new List();
      
      //count lines
      BufferedReader counter = new BufferedReader(new FileReader(args[0]));
      int lines = 0;
      while (counter.readLine() != null) lines++;
      counter.close();
      
      String[] S = new String[lines];
      
      while( in.hasNextLine() ){
          
         line = in.nextLine();    // add extra space so split works right
         S[lineNumber] = line;
         lineNumber++; 
      }
      //after making a 1,2,3...n array with n as the length
      
      //insert first element here
      L.append(0);
      L.moveFront();
      
      for(int i = 1; i < lines; i++){
         for(int j = 0; j < L.length(); j++){
            if(S[i].compareTo(S[j]) > 0)
               L.moveNext();
         }
         if(L.index() != -1){
            L.insertBefore(i);
            L.moveFront();
         }
         else{
            L.append(i);
            L.moveFront();
         }
      }
      
      L.moveFront();
      
      while(outi < L.length()) {
         outi++;
         out.println(S[L.get()]);
         L.moveNext();
      
      }

      in.close();
      out.close();
      
   }

}
