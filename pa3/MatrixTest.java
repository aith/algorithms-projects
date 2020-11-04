
//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa3: Sparse
// cmps101, spring 2019
// 
// MatrixTest.java
//-----------------------------------------------------------------------------
public class MatrixTest {
   public static void main(String[] args){
      int n=50;
      Matrix A = new Matrix(10);
      Matrix B = new Matrix(15);
     A.changeEntry(1, 1, 1);
     B.changeEntry(1, 1, 1);
     //if (A.equals(B)) return 1;
     B = new Matrix(10);
     A.changeEntry(1, 1, 1);
     A.changeEntry(1, 3, 1);
     B.changeEntry(1, 1, 1);
     B.changeEntry(1, 3, 1);
     //if (!A.equals(B)) return 2;
     A.changeEntry(1, 3, 0);
     //if (A.equals(B)) return 3;
     A.changeEntry(1, 1, 0);
     B.makeZero();
     A.changeEntry(10, 10, 10);
     B.changeEntry(10, 10, 10);
    //if (!A.equals(B)) return 4;
      System.out.println(A);
     // System.out.println(B);
      /*A.changeEntry(1,2,1); B.changeEntry(1,1,1);
      A.changeEntry(1,3,4);
      A.changeEntry(1,3,1);
      A.changeEntry(1,1,3);
      A.changeEntry(2,3,2);
      System.out.println(A);
      Matrix C = A.copy();
      C = C.scalarMult(2);
      
      System.out.println(C);
      
      Matrix D = C.transpose();
      
      System.out.println(D);
      
      Matrix E = D.add(C);
      
      System.out.println(E);
      
      E = E.sub(D);
      
      System.out.println(E);
      
      Matrix F = C.mult(D);
      
      System.out.println(F);
      
      Matrix G = F.copy();
      
      System.out.println(G.equals(F));
*/
   }
}