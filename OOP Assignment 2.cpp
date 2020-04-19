#include<iostream>
using namespace std;
struct sparse{
    int row;
    int col;
    int val;
    struct sparse *next;
};

class spmatrix{
    sparse *head;


    public:

    int no_of_rows;
    int no_of_columns;

    spmatrix(){
        head=NULL;
        no_of_rows=0;
        no_of_columns=0;
    }

    void read(){
        sparse *temp,*last;
        int r,c,no=0,a;
        cout<<"Enter how many rows and columns are there: ";
        cin>>r>>c;
        no_of_rows=r;
        no_of_columns=c;
        cout<<"Enter the matrix: \n";
        head=new sparse;
        head->row=r;
        head->col=c;
        head->next=NULL;

        for(int i=0;i<r;i++){
        for(int j=0;j<c;j++)
        {
                cin>>a;
                if(a!=0){
                      temp=new sparse;
                      no++;
                      temp->row=i+1;
                      temp->col=j+1;
                      temp->val=a;
                      temp->next=NULL;
                  if(head->next==NULL){
                       head->next=temp;
                       last=temp;
                   }
                   else{
                       last->next=temp;
                       last=temp;
                    }
                 }
             }
        }
        head->val=no;
    }

    void print(){
        int f;
        sparse *temp,*temp1;
        temp1=head->next;
        for(int i=0;i<head->row;i++){
            temp=temp1;
            for(int j=0;j<head->col;j++){
                f=1;
                temp=temp1;
                while(temp){
                   if(i+1==temp->row&&j+1==temp->col){
                        cout<<temp->val<<"\t";
                        f=0;
                        break;
                    }
                    temp=temp->next;
                }
                if(f==1)
                    cout<<0<<"\t";
            }
            cout<<endl;
          }
    }

    void insert(sparse *t){
          sparse *tr,*temp;
          temp=new sparse;
          temp->col=t->col;
          temp->row=t->row;
          temp->val=t->val;
          temp->next=NULL;

          if(head==NULL){
               head=new sparse;
               head->next=temp;
               head->val=1;
          }
          else{
               tr=head->next;
               while(tr->next!=NULL){
                    if(tr->row==temp->row&&tr->col==temp->col){
                      tr->val=tr->val+temp->val;
                      return;
                    }
                    tr=tr->next;
               }
               if(tr->row==temp->row&&tr->col==temp->col){
                    tr->val=tr->val+temp->val;
                    return;
               }
               tr->next=temp;
               (head->val)++;
          }
    }


    spmatrix multiply(spmatrix m){
          spmatrix res;
          if(no_of_columns!=m.no_of_rows){
                cout<<"\nCan't multiply them";
                return res;
          }

          sparse *t1,*t2,*temp;
          temp=new sparse;
          t1=head->next;
          t2=m.head->next;
          while(t1!=NULL){
           t2=m.head->next;
           while(t2->next!=NULL){
                if(t1->col==t2->row){
                    temp->row=t1->row;
                    temp->col=t2->col;
                    temp->val=(t1->val)*(t2->val);
                    temp->next=NULL;
                    res.insert(temp);
                }
                t2=t2->next;
           }
           if(t2->next==NULL){
                if(t1->col==t2->row){
                    temp->row=t1->row;
                    temp->col=t2->col;
                    temp->val=(t1->val)*(t2->val);
                    temp->next=NULL;
                    res.insert(temp);
                }
           }
           t1=t1->next;
          }
          res.head->row=head->row;
          res.head->col=m.head->col;
          return res;
        }
};

int main(){
    spmatrix s1,s2,s3;
    cout<<"Enter First sparse Matrix A: \n";
    s1.read();
    cout<<"\nEnter Second sparse Matrix B: \n";
    s2.read();

    cout<<"\nMultiplication of A and B: \n";
    s3=s1.multiply(s2);
    s3.print();
    return 0;
}
