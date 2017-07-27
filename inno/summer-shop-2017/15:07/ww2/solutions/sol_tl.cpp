#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
 
int main()
{
    int t,n,m,i,j,k,l;
    long long res[31][31][32],fres[31],tmp[31][31],M=1000000007;
    long long ftmp[31],mov[31][31];
    scanf("%d",&t);
    while(t--)
    {
              scanf("%d%d",&n,&m);
              if(m==1)
              {
                      cout<<1<<endl;
                      continue;
              }
              if(n==1)
              {
                      cout<<m<<endl;
                      continue;
              }
              memset(mov,0,sizeof(mov));
              mov[1][1]=1; // for starting even
              mov[1][2]=1;
              mov[m][m]=1;
              mov[m][m-1]=1;
              for(i=2;i<m;++i)
                   for(k=-1;k<=1;++k)
                        mov[i][i+k]=1;
              memset(res,0,sizeof(res));
              res[1][2][1]=1;   // for starting odd
              res[m][m-1][1]=1;
              for(i=2;i<m;++i)
              {
                   res[i][i-1][1]=1;
                   res[i][i+1][1]=1;                           
              } 
              for(l=2;(1<<l)<=n;++l)
              {
                     memset(tmp,0,sizeof(tmp));                
                     for(i=1;i<=m;++i)
                     {
                        for(j=1;j<=m;++j)
                        {
                           for(k=1;k<=m;++k)
                           {
                                 tmp[i][k]=(tmp[i][k]+(res[i][j][l-1]*mov[j][k]))%M;
                           }
                        }
                     }
                     for(i=1;i<=m;++i)
                     {
                         for(j=1;j<=m;++j)
                         {
                              res[i][j][l]=0;
                              for(k=1;k<=m;++k)
                                    res[i][j][l]=(res[i][j][l] + (tmp[i][k]*res[k][j][l-1]))%M;
                         }
                     }
              }
              //cout<<"here!"<<endl;
              memset(fres,0,sizeof(fres));
              for(i=1;i<=m;++i)
                   fres[i]=1;
              if(n%2==0)
              {
              l=1;
              n>>=1;
              while(n>0)
              {
                 if(n&1)
                 {
                       //cout<<"l: "<<l<<endl; 
                       memset(ftmp,0,sizeof(ftmp)); 
                       for(j=1;j<=m;++j)
                       {
                           for(i=1;i<=m;++i) 
                               ftmp[j]=(ftmp[j] + (fres[i]*res[i][j][l]))%M;                        
                       }
                       for(j=1;j<=m;++j)                                     
                                fres[j]=ftmp[j];
                 }
                 n>>=1;
                 ++l;
              }
              }
              else
              {
              l=1;
              n>>=1;
              while(n>0)
              {
                 if(n&1)
                 {
                       memset(ftmp,0,sizeof(ftmp)); 
                       for(j=1;j<=m;++j)
                       {
                           for(i=1;i<=m;++i) 
                               ftmp[j]=(ftmp[j] + (fres[i]*res[i][j][l]))%M;                        
                       }
                       for(j=1;j<=m;++j)                                     
                                fres[j]=ftmp[j];
                       n-=(1<<l);
                       ++l;
                 }
              }
              ftmp[1]=fres[2];
              ftmp[m]=fres[m-1];
              for(i=2;i<m;++i)
                    ftmp[i]=(fres[i-1] + fres[i]) %M;
              for(j=1;j<=m;++j)                                     
                 fres[j]=ftmp[j];
              
              }    
              for(i=2;i<=m;++i)
                   fres[i]=(fres[i] + fres[i-1])%M;
              cout<<fres[m]<<endl;
    }
}     
