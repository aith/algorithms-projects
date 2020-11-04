
//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa3: Sparse
// cmps101, spring 2019
// 
// Sparse.java
//-----------------------------------------------------------------------------

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Sparse {
   public static void main(String[] args) throws IOException {
      Scanner in = null;
      PrintWriter out = null;
      
      if(args.length != 2){
         System.err.println("Usage error: requires 2 command line arguments");
         System.exit(1);
      }
      
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));
      
      //read the first line of nums
      if(!in.hasNextInt()) { in.close(); out.close(); throw new RuntimeException("error: incorrect input."); }
      int size = in.nextInt(); 
      if(!in.hasNextInt()) { in.close(); out.close(); throw new RuntimeException("error: incorrect input."); }
      int Annz = in.nextInt();
      if(!in.hasNextInt()) { in.close(); out.close(); throw new RuntimeException("error: incorrect input."); }
      int Bnnz = in.nextInt();
      
      //initialize A & B
      Matrix A = new Matrix(size);
      Matrix B = new Matrix(size);
      
      //create A
      for(int i = 0; i < Annz; i++) {
         A.changeEntry(in.nextInt(), in.nextInt(), in.nextDouble());
      }
      
      //create B
      for(int j = 0; j < Bnnz; j++) {
         B.changeEntry(in.nextInt(), in.nextInt(), in.nextDouble());
      }
      
      //print the output
      out.write("A has " + Annz + " non-zero entries:\n");
      out.println(A);
      
      out.println("B has " + Bnnz + " non-zero entries:");
      out.println(B);
      
      out.println("(1.5)*A =");
      out.println(A.scalarMult(1.5));
      
      out.println("A+B =");
      out.println(A.add(B));
      
      out.println("A+A =");
      out.println(A.add(A));
      
      out.println("B-A =");
      out.println(B.sub(A));
      
      out.println("A-A =");
      out.println(A.sub(A));
      
      out.println("Transpose(A) =");
      out.println(A.transpose());
      
      out.println("A*B =");
      out.println(A.mult(B));
      
      out.println("B*B = ");
      out.print(B.mult(B));
      
      in.close();
      out.close();
   }
}
