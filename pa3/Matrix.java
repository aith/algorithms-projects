
//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa3: Sparse
// cmps101, spring 2019
// 
// Matrix.java
//-----------------------------------------------------------------------------
public class Matrix {

   int size;
   int nnz; //non-zero entries
   List[] A;
   
   //return Entry's col
   int getcol(Object x) {
      
      Entry E = (Entry)x;
      return E.col;
      
   }
   
   //return Entry's data
   double getdata(Object x) {
      
      Entry E = (Entry)x;
      return E.data;
   }
   
   private class Entry{
      // PIVs
      int col;
      double data;
     
      // Constructor
      Entry(int c, double d){
         col = c;
         data = d;
      }
      
      public String toString() {
         return "(" + String.valueOf(col)+ ", " + String.valueOf(data)+ ")";
           
      }
      
      public boolean equals(Object x) {
         if(!(x instanceof Entry)) return false;
         
         Entry cm = (Entry)x;
         if(this.col == cm.col && this.data == cm.data) return true;
         return false;
      }
   }
   
   // Makes a new n x n zero Matrix. pre: n>=1
   Matrix(int n){
      if(n < 1) {
         throw new RuntimeException("error: cannot create Matrix of size <1\n");
      }
      
      //initialize array w size n
      List[] Ar = new List[n];
      for(int i=0; i<n; i++) {
         Ar[i] = new List();
      }
      this.A = Ar;
      this.size = n;
      this.nnz = 0;
      
   }
   
   // Access functions
   
   // Returns n, the number of rows and columns of this Matrix
   int getSize() { 
      return size;
   }
   
   // Returns the number of non-zero entries in this Matrix
   int getNNZ() {
      return nnz;
   }
  
   // overrides Object's equals() method
   public boolean equals(Object x) {//CHANGED FROM OBJECT, right or not?
      
      if(!(x instanceof Matrix)) return false;
      
      Matrix cm = (Matrix)x;
      
      if(this.size != cm.size || this.nnz != cm.nnz) return false;
      
      for(int i=0; i < this.size; i++) {
         
         this.A[i].moveFront();
         cm.A[i].moveFront();
         
         while(this.A[i].index() > -1) {
            if(!((this.A[i].get()).equals(cm.A[i].get()))) return false;
            this.A[i].moveNext();
            cm.A[i].moveNext();
         }
      }
      
      return true;
   }
   
   // Manipulation procedures
 
// overrides Object's toString() method
   public String toString() {
      StringBuffer sb = new StringBuffer();
      for(int i = 0; i < this.size; i++) {
         if(this.A[i].length() > 0) sb.append((i+1) + ":" + this.A[i].toString() + "\n");
      }
      return new String(sb);
   }
   
// sets this Matrix to the zero state 
   void makeZero() {
      for(int i=0; i<this.size; i++) {
         this.A[i].clear();
      }
      this.nnz = 0;
   }
   
   void changeEntry(int i, int j, double x) {
   // changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
      
      if((i < 1 || i > this.getSize()) | (j < 1 || j > this.getSize())) {
         throw new RuntimeException("error: attempting to change an invalid array location.\n");
      }
      
      this.A[i-1].moveFront();
      while((this.A[i-1].index() > -1) && getcol(this.A[i-1].get()) < j){
         this.A[i-1].moveNext();
      }
      //if this.A[i].col() > j, then an element at that spot doesn't exist
      if(this.A[i-1].index() <= -1) {
         if(x != 0) {
            this.A[i-1].append(new Entry(j,x));
            this.nnz++;
         }
         }
      else if(getcol(this.A[i-1].get()) > j) {
         
         if(x!=0) { 
            this.A[i-1].insertBefore(new Entry(j,x));
            nnz++;
         }
         
      } else if(getcol(this.A[i-1].get()) == j) {
         
         if(x==0) {
            this.A[i-1].delete();
            nnz--;
         } else {
            this.A[i-1].setData(new Entry(j,x));
         }
         
      }
   }
   
   // returns a new Matrix having the same entries as this Matrix 
   Matrix copy() {
      
      Matrix C = new Matrix(this.size);
      
      for(int i=0; i<this.size;i++) {
         
         for(this.A[i].moveFront(); this.A[i].index() > -1; this.A[i].moveNext()){
            C.A[i].append(new Entry(getcol(this.A[i].get()), getdata(this.A[i].get())));
         }
         C.nnz = this.nnz;
      }
       
      return C;
   }
   
// returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x) {
      Matrix P = new Matrix(this.size);
      
      if(x != 0) {
         P.nnz = this.nnz;
         for(int i=0; i<this.size;i++) {
            for(this.A[i].moveFront(); this.A[i].index() > -1; this.A[i].moveNext()){
               P.A[i].append(new Entry(getcol(this.A[i].get()), x * getdata(this.A[i].get())));
            }
         }
      }
      return P;
   }
   
   // returns a new Matrix that is the transpose of this Matrix
   Matrix transpose() {
      
      Matrix T = new Matrix(this.size);
      T.nnz = this.nnz;
      
      for(int i = 0; i < this.size; i++) {
         for(this.A[i].moveFront(); this.A[i].index() > -1; this.A[i].moveNext()) {
             T.A[getcol(this.A[i].get())-1].append(new Entry(i+1, getdata(this.A[i].get()))); //flip rows w cols of data, might need to prepend
         }
      }
      return T;
   }
   
   // returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix add(Matrix M) {
      if(M.getSize() != this.getSize()) throw new RuntimeException("error: can only add Matrices of equal size.\n");

      Matrix A = new Matrix(this.size);
      
      for(int i = 0; i < this.getSize(); i++) {
         
         this.A[i].moveFront();
         M.A[i].moveFront();
         
         while(this.A[i].index() > -1 || M.A[i].index() > -1) {
            //case: M has an element not in this matrix
            if((this.A[i].index() == -1 || (M.A[i].index() != -1 && getcol(this.A[i].get()) > getcol(M.A[i].get())))) {
               A.A[i].append(new Entry(getcol(M.A[i].get()), getdata(M.A[i].get())));
               M.A[i].moveNext();
               A.nnz++;
            } else 
            if((M.A[i].index() == -1 || (this.A[i].index() != -1 && getcol(M.A[i].get()) > getcol(this.A[i].get())))){
            //case: this matrix has an element not in M
               A.A[i].append(new Entry(getcol(this.A[i].get()), getdata(this.A[i].get())));
               this.A[i].moveNext();
               A.nnz++;
            } else 
            //case: cursor column numbers are equal
            if(getcol(this.A[i].get()) == getcol(M.A[i].get())) {
               //System.out.println("!");
               if((getdata(this.A[i].get()) + getdata(M.A[i].get())) != 0) {
                  A.A[i].append(new Entry(getcol(this.A[i].get()), getdata(this.A[i].get()) + getdata(M.A[i].get())));
                  A.nnz++;
               } 
               this.A[i].moveNext();
               if(this != M) M.A[i].moveNext();
            }
         }  
      }   
      return A;
   }
   
// returns a new Matrix that is the scalar product of this Matrix with x
   Matrix sub(Matrix M) {
      if(M.getSize() != this.getSize()) throw new RuntimeException("error: can only add Matrices of equal size.\n");
            
      Matrix A = new Matrix(this.size);
      
      for(int i = 0; i < this.getSize(); i++) {
         
         this.A[i].moveFront();
         M.A[i].moveFront();
         
         while(this.A[i].index() > -1 || M.A[i].index() > -1) {
            
            //case: M has an element not in this matrix
            if((this.A[i].index() == -1 || (M.A[i].index() != -1 && getcol(this.A[i].get()) > getcol(M.A[i].get())))) {
               A.A[i].append(new Entry(getcol(M.A[i].get()), 0-getdata(M.A[i].get())));
               M.A[i].moveNext();
               A.nnz++;
            } else 
            if((M.A[i].index() == -1 || (this.A[i].index() != -1 && getcol(M.A[i].get()) > getcol(this.A[i].get())))){
            //case: this matrix has an element not in M
               A.A[i].append(new Entry(getcol(this.A[i].get()), getdata(this.A[i].get())));
               this.A[i].moveNext();
               A.nnz++;
            } else 
            //case: cursor column numbers are equal
            if(getcol(this.A[i].get()) == getcol(M.A[i].get())) {
               if(getdata(this.A[i].get()) - getdata(M.A[i].get()) != 0) {
                  A.A[i].append(new Entry(getcol(this.A[i].get()), getdata(this.A[i].get()) - getdata(M.A[i].get())));
                  A.nnz++;
               }
               this.A[i].moveNext();
               if(this != M) M.A[i].moveNext();
            }
         }  
      }   
      return A;
   }
   
   //returns dot product of two lists
 private double dot(List P, List Q) {
      
      double prod = 0;
      
      P.moveFront();
      Q.moveFront();
      
      while(P.index() > -1 && Q.index() > -1) {
         //case: cursor column numbers are equal
         if(getcol(P.get()) == getcol(Q.get())) {
            prod += getdata(P.get()) * getdata(Q.get());
            
            P.moveNext();
            Q.moveNext();
         } else
         //case: M has an element not in this matrix
         if((Q.index() != -1 && getcol(P.get()) > getcol(Q.get())) || P.index() == -1) {
            Q.moveNext();
         } else {
            //case: this matrix has an element not in M
            P.moveNext();
         }
      }
      return prod;
   }
   
//returns a new Matrix that is the product of this Matrix with M
// pre: getSize()==M.getSize()
   Matrix mult(Matrix M) {
      
      if(M.getSize() != this.getSize()) throw new RuntimeException("error: can only add Matrices of equal size.\n");
      
      Matrix A = new Matrix(this.size);
      Matrix T = M.transpose();
      
      for(int row = 0; row < this.size; row++) {
         
         this.A[row].moveFront();
         T.A[row].moveFront();
         
         for(int col = 0; col < this.size; col++) {
            double newdata = dot(this.A[row], T.A[col]);
            if(newdata != 0){
               A.A[row].append(new Entry(col+1, newdata));
               A.nnz++;
            }
         }
      }
      return A;
   }
      
}

