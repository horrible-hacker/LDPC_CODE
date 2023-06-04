#include<iostream>
using namespace std;
int main()
{
  //---------------------------------sender_side-------------------------------
  cout<<"-------------------------------------sender-side------------------------------------------\n";
   int message[4],codeword[7];
   int parity_matrix[3][7]={{1,1,0,1,1,0,0},{1,0,1,1,0,1,0},{0,1,1,1,0,0,1}};  //entering values in parity check matrix
   int generator_matrix[4][7]={{1,0,0,0,1,1,0},{0,1,0,0,1,0,1},{0,0,1,0,0,1,1},{0,0,0,1,1,1,1}};  //entering vakues in generator matrix
   cout<<"Enter your 4-bit message:  ";
   for(int i=0;i<4;i++)
   {
     cin>>message[i];  //taking input from user/sender
   }
   
   for(int i=0;i<7;i++)
   {
    int add=0;  //introducing dummy variable
    for(int j=0;j<4;j++)
    {
      add=add+(generator_matrix[j][i]*message[j]);  //matrix multiplcation of M and G
    }
    codeword[i]=add%2;   //entering our codeword 
   }
   cout<<"Your Codeword is: ";
   for(int i=0;i<7;i++) //displaying our codeword
   {
    cout<<codeword[i]<<" ";
   }
   //now codeword transmitted to recieveer side
   //--------------------channel-side-------------------------------------------------------------
cout<<"\n-------------------------------------Channel-in------------------------------------------\n";
codeword[2]=(codeword[2]+1)%2;//noise
cout<<"Noise introduced at 3rd bit\n";
cout<<"-------------------------------------Channel-out------------------------------------------\n";
cout<<"-------------------------------------Reciever-side------------------------------------------\n";
   //-------------------------------------------receiver_side-------------------------------------
   int received[7];
   for(int i=0;i<7;i++)
   {
     received[i]=codeword[i];
   }
   
   int check_set[3][4]; //introducing parity check set
      for(int j=0;j<3;j++) //enetrinng value in check set
      {
        for(int k=0,l=0;k<7;k++)
        {
            if(parity_matrix[j][k]==1)
            {
                check_set[j][l]=k;
                l++;
            }
            if(l==4)
            {
                l=0;
            }
        }
      }
      cout<<endl;
      cout<<"Your parity check sets are :\n";
      for(int i=0;i<3;i++) //dispaying parity check set
      {
        cout<<"#"<<i+1<<": ";
        for(int j=0;j<4;j++)
        {
            cout<<check_set[i][j]+1<<" ";
        }
        cout<<endl;
      }
      bool error=false;
      cout<<"There is an error in ";
      for(int i=0;i<3;i++)
      {
        int dum[4]={0,0,0,0};
        for(int j=0;j<4;j++)
        {
            dum[j]=check_set[i][j];
        }
        if(received[dum[0]]^received[dum[1]]^received[dum[2]]^received[dum[3]]!=0)
        {
            cout<<"equation( "<<i+1<<" ) ";
            error=true;
        }
      }
      cout<<endl;
      if(error==false) //in case there is no error
      {
        cout<<"No error in your message\n";
      }
      int tree[7][3];
      for(int i=0;i<7;i++) //making parity check tree
      {
        int k=0;
        for(int j=0,k=0;j<3;j++,k++)
        {
            if(parity_matrix[j][i]==1)
            {
                tree[i][k]=j;
            }
            else if(parity_matrix[j][i]==0)
            {
                tree[i][k]=-1;
            }
        }
      }
      for(int i=0;i<7;i++) // displaying tree
      {
        cout<<i+1<<"-->";
        for(int j=0;j<3;j++)
        {
            cout<<tree[i][j]+1<<" ";
        }                 //0 represents null
        cout<<"\n";
      }
      if(error==true) //if there is error in message
      {
        cout<<"There is error in recieved message";
      }
}
