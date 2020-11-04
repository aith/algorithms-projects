//-----------------------------------------------------------------------------
// Ari Iramanesh
// airanman, 1628897
// pa1: Lex, List ADT
// cmps101, spring 2019
// 
// List.java
//-----------------------------------------------------------------------------

class List{
   
   // Fields
   Node front;
   Node back;
   Node cursor;
   int length;
   int index = -1; //right?
   
   // toString()
   // Overides Object's toString() method.
   public String toString(){
      StringBuffer sb = new StringBuffer();
      Node N = front;
      while(N!=null){
         sb.append(" ");
         sb.append(N.toString());
         N = N.next;
      } 
      return new String(sb);
   }

   boolean isEmpty() { 
      return length==0; 
   }
   
   private class Node{
      int data; 
      Node next;
      Node prev;
      
      
   // Constructor
      Node(int data) { this.data = data; next = null; prev = null;}
      
      // toString():  overrides Object's toString() method
      public String toString() { 
         return String.valueOf(data); 
      }
   }
   
      // ACCESS FUNCTIONS ---------------------
      int front() {
         if(this.length() < 1) {
            throw new RuntimeException("error: List is empty or undefined");
         }
         return this.front.data;
      }

      int back() {
         if(this.length() < 1) {
            throw new RuntimeException("error: List is empty or undefined");
         }
         return this.back.data;
      }

      int length() {
         return this.length;
      }

      int index() {
         if(this.cursor != null || this.index == -1) {
            return this.index;
         }
         else {
           
            return -1; 
         }
      }
      
      int get() { 
         if(this.length() < 1) {
            throw new RuntimeException("error: List is empty or undefined");
         }
         if(this.index < 0) {
            throw new RuntimeException("error: Cursor is undefined");
         }
         return this.cursor.data;
         
      }
      
      boolean equals(List L) {
         Node A = this.front;
         Node B = L.front;
         if( this.length != L.length) return false;
         while(A!=null) {
            if(A.data != B.data) return false;  
            A = A.next;
            B = B.next;
         }
         return true;
      }
      
      // MANIPULATION FUNCTIONS --------------------
      
      void clear() {
         if(this.length == 0) return;
         
         Node iterator = this.front;
         Node next_node = iterator.next;
         while(iterator != null) {
            next_node = iterator.next;
            iterator.prev = null;
            iterator.next = null;
            //iterator.data = null;
            iterator = next_node;
         }
         this.front = null;
         this.back = null;
         this.cursor = null;
         this.length = 0;
      }
      
      void moveFront() {
         if(this.length > 0) {
            this.cursor = this.front;
            this.index = 0;//was 0, either this of get() is +1
         }
      }
      
      void moveBack() {
         if(this.length > 0) {
            this.cursor = this.back;
            this.index = length-1; //was length-1
         }
      }
      
      void movePrev() {
         if(this.index != -1) {
            //if cursor is defined
            if(this.cursor != this.front) {
               this.cursor = this.cursor.prev;
               this.index--;
            }
            else
               this.index = -1;
         }
      }
      
      void moveNext() {
         if(this.index != -1) {
            if(this.cursor != this.back) {
               this.cursor = this.cursor.next;
               this.index++;
            }
            else
               this.index = -1;
         }
      }
      
      void prepend(int data) {
         Node new_front = new Node(data);
         
         if(this.isEmpty()) {
            this.front = new_front;
            this.back = new_front;
         }
         else {
            new_front.next = this.front;
            this.front.prev = new_front;
            this.front = new_front;
         }
         this.length++;
         if(this.cursor != null) this.index++;
      }
      
     //based on Enqueue() from the example 
     void append(int data){
         Node N = new Node(data);
         if( this.isEmpty() ) { 
            this.front = back = N;
         }else{ 
            N.prev = this.back;
            this.back.next = N;
            this.back = N;
            
         }
         this.length++;
      }
      
      void insertBefore(int data) {
         //case: list length is 0 or below
         if(this.length() < 1) {
            throw new RuntimeException("error: List is empty or undefined");
         }
         
         //case: cursor is undefined or below 0
         if(this.get() < 0) {
            throw new RuntimeException("error: Cursor is undefined");
         }
         
         Node N = new Node(data);
         
         //case: cursor is at front
         if(this.index() == 0) {
            this.front.prev = N;
            N.next = this.front;
            this.front = N;
            this.length++;
            this.index++;
         }
         
         //case: cursor is in middle/end
         else {
            N.next = this.cursor;
            N.prev = this.cursor.prev;
            this.cursor.prev.next = N;
            this.cursor.prev = N;
            this.length++;
            this.index++;
         }
      }
      void insertAfter(int data) {
         //case: list length is 0 or below
         if(this.length() < 1) {
            throw new RuntimeException("error: List is empty or undefined");
         }
         
         //case: cursor is undefined or below 0
         if(this.get() < 0) {
            throw new RuntimeException("error: Cursor is undefined");
         }
         
         Node N = new Node(data);
         
         //case: cursor is at back
         if(this.cursor == back) {
            N.prev = this.back;
            this.back.next = N;
            this.back = N;
            this.length++;
         }
         
         //case: cursor is in middle/front
         else {
            N.next = this.cursor.next;
            N.prev = this.cursor.next.prev;
            this.cursor.next.prev = N;
            this.cursor.next = N;
            this.length++;
         }

      }
      
      void deleteFront() {
         if(this.length() < 1) {
            throw new RuntimeException("error: List is empty or undefined");
         }
         this.front.next.prev = null;
         this.front = this.front.next;
         this.length--;
         if(this.cursor != null) this.index--;
      }
      
      void deleteBack() {
         if(this.length() < 1) {
            throw new RuntimeException("error: List is empty or undefined");
         }
         if(this.cursor == this.back) {
            
            this.index = -1;
     
         }
         Node N = new Node(this.back.data);
         N = this.back;
         N.next = null;
         //(this.back.prev).next = null;
         this.back = this.back.prev;
         this.length--; 
         
      }
      
      void delete() { 
         if(this.length() < 1) {
            throw new RuntimeException("error: List is empty or undefined");
         }
         
         if(this.get() < 0) {
            throw new RuntimeException("error: Cursor is undefined");
         }
         if(this.cursor == this.back) {
            this.deleteBack();
         } else if (this.cursor == front){
            this.deleteFront(); 
         } else {
         Node Nprev = new Node(this.back.data);
         Nprev = this.cursor.prev;
         Node Nnext = new Node(this.back.data);
         Nnext = this.cursor.next;
         
         Nprev.next = this.cursor.next;
         Nnext.prev = this.cursor.prev;
         this.length--;
         this.cursor = null;
         this.index = -1;
         }
      }
      
      List copy(){
         List L = new List();
         Node N = this.front;

         while( N!=null ){
            L.append(N.data);
            N = N.next;
         }
         return L;
      }

}
