#include <stdio.h>
#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <cmath>
#include <math.h>
//#include <bits/stdc++.h>


using namespace std;

struct dirent *entry;
vector<string> files;
void list_dir(const char *path)
{
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
       // std::cout << entry->d_name << "\n";
        files.push_back(entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]){
char *var = "C:\\Users\\mouni\\Desktop\\IS\\Test";
list_dir(var);
std::cout<< "Count is: "<< files.size();
float disting[files.size()][files.size()];
for(int i=0;i<files.size();i++)
{
   std::cout << files[i] << "\n";
}
ifstream inFile;

string Doctets1;
string temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
string FirstPacket1;
string Duration1;
vector<string> Doctets;
vector<string> FirstPacket;
vector<string> Duration;
vector<float> od;
vector<string> Day;
vector<string> Month;
vector<string> Date;
vector<string> Hrs;
vector<string> Min;
vector<string> Sec;
vector<int> maxsize;
typedef vector<string> tempval;
vector<tempval> val;

float zab12[files.size()-5][files.size()-5];
float zab23[files.size()-5][files.size()-5];
float zab34[files.size()-5][files.size()-5];
int fl=0;
int days;

vector<vector<float> > filematrix(files.size()-5);
vector<vector<float> > rankmatrix(files.size()-5);
int slot = 10;//in seconds
int numslot =(24*60*60)/slot;
for(int i1=2;i1<files.size()-3;i1++)
{
inFile.open(files[i1]);
if (inFile.is_open()) {
    cout << "File has been opened " << files[i1] << endl;
}
else {
    cout << "NO FILE HAS BEEN OPENED " << files[i1] << endl;
    continue;
}


while (!inFile.eof()) {
     getline ( inFile, temp1, ',' );
     if(temp1=="")
        break;
    getline ( inFile, temp2, ',' );
    getline ( inFile, temp3, ',' );
    getline ( inFile, Doctets1 , ',' );
    getline ( inFile, temp4, ',' );
    getline ( inFile, FirstPacket1, ',' );
    getline ( inFile, temp5, ',' );
    getline ( inFile, temp6, ',' );
    getline ( inFile, temp7, ',' );
    getline ( inFile, Duration1);
    Doctets.push_back(Doctets1);
    FirstPacket.push_back(FirstPacket1);
    Duration.push_back(Duration1);

}
inFile.close();
unsigned long long epoch64;
 int year;
 for(int i=1; i<Doctets.size(); i++)
    {
      const char *d = FirstPacket[i].c_str();
      std::stringstream is(d);
      is >> epoch64;
      epoch64 /= 1000;
      time_t t = epoch64;
      char *epo;
      char delims[] = " ,:";
      char * tok;
      epo = ctime(&t);
      tok = strtok(epo, delims);
      int cnt =0;
      while(tok){
        if(cnt==0)
        {
          Day.push_back(tok);
        }
        if(cnt==1)
        {
            Month.push_back(tok);
        }
        if(cnt==2)
        {
            Date.push_back(tok);
        }
        if(cnt==3)
        {
            Hrs.push_back(tok);
        }
        if(cnt==4)
        {
            Min.push_back(tok);
        }
        if(cnt==5)
        {
            Sec.push_back(tok);
        }
        if(cnt==6)
        {
            year = stoi(tok);
        }
        cnt++;
        tok  = strtok(NULL, delims);
      }

      if(stoi(Duration[i])==0)
      {
        od.push_back(-0.1);
      }
      else
      {
          float x= stof(Doctets[i]);
          float y= stof(Duration[i]);
          od.push_back(x/y);
      }


    }
    int k;
    int sz = od.size();
   // cout << " oct/duration values: ";
    val.push_back(vector<string>());
    for(k=0;k<sz;k++)
    {

       // cout << od[k] <<"\n";
        val[fl].push_back(Date[k]);
    }

maxsize.push_back(sz);

vector<int> tottime;
vector<int> group;
for(int x=0;x<sz;x++)
{
 tottime.push_back(3600 * stoi(Hrs[x]) + 60 * stoi(Min[x]) + stoi(Sec[x]));
 //cout<<"tot time: "<<tottime[x]<<"\n";
 group.push_back(tottime[x]/slot);
 //cout<<"group is: "<<group[x]<<"\n";
}


int flag1=0, flag2=0;
int x=0,y=0,z=0;

//To get num of days in a month
   if(Month[0].compare("Feb") == 0)
	{
		if((year%400==0) || (year%4==0 && year%100!=0))
			days=29;
		else
			days=28;
	}
	//months which has 31 days
	else if(Month[0].compare("Jan") == 0 || Month[0].compare("Mar") == 0|| Month[0].compare("May") == 0|| Month[0].compare("Jul") == 0|| Month[0].compare("Aug") == 0||Month[0].compare("Oct") == 0|| Month[0].compare("Dec") == 0)
		days=31;
	else
		days=30;

//To assign the day of the week values
int month1;
string monthnames[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
for(int mo=0;mo<12;mo++)
{
    if(Month[0].compare(monthnames[mo])==0)
    {
        month1=mo+1;
        break;
    }
}
//cout<<"Month is"<<month1<<" year: "<<year<<endl;
int weekday[days];
int a, y1, m;
for (int day=1;day<=days;day++)
{
  a = (14 - month1) / 12;
  y1 = year - a;
  m = month1 + (12 * a) - 2;
 weekday[day-1]=(day + y1 + (y1 / 4) - (y1 / 100) + (y1 / 400) + ((31 * m) / 12)) % 7;
 //cout<< "Day value is: "<< weekday[day-1]<<endl;
}

//returns number. 0=sunday, 1=monday , so on

float mat[days][numslot] = {0.0};
float avg[days][numslot] = {0.0};
float du = 0.1;
//cout << "the days and numslot are: "<<days<<" " << numslot<<endl;
for(x=0;x<sz;x++)
{
    y = stoi(Date[x])-1;
    //cout << "value of y is: "<<y << "\n";
    z = group[x];
    //cout<< " value of z is: "<<z << "\n";
    if(od[x]==-du)
        continue;
    else
    {
      mat[y][z]+=od[x];
      //cout << " value in mat is: "<< mat[y][z] << "\n";
      avg[y][z]++;
      //cout<<" Value in avg is: "<< avg[y][z]<<"\n";
    }
}
//cout<<"Num of days are: "<<days<<endl;

for(int y=0; y<days;y++)
{
    //cout<< " Weekday value is: " <<weekday[y]<<endl;
    for(int z=0; z<numslot; z++)
    {
       if(avg[y][z]!=0.0)
       {
        mat[y][z] = mat[y][z]/avg[y][z];
      //  cout<< mat[y][z]<<"("<< y<< "," <<z<<") ";
       }
      // else
      //  cout<< mat[y][z] << " ";
    }
   // cout<<"\n";
}
int flagm=0,daycount=0;
for(int y=0; y<days;y++)
{
    //week starts with monday
    if(weekday[y]!=1 && flagm==0)
    {
        continue;
    }
    flagm=1;
    //exclude sat and sun
    if((weekday[y] == 6) || (weekday[y] == 0))
        continue;
    for(int z=0; z<numslot && daycount < 10; z++)
    {
         filematrix[fl].push_back(mat[y][z]);

    }
    daycount++;
}

//clear the matrix
for(int y=0; y<days;y++)
{
    for(int z=0; z<numslot; z++)
    {
     mat[y][z] = 0.0;
     avg[y][z] = 0.0;
    }
}

group.clear();
tottime.clear();
Doctets.clear();
FirstPacket.clear();
Duration.clear();
od.clear();
Day.clear();
Month.clear();
Date.clear();
Hrs.clear();
Min.clear();
Sec.clear();
fl++;
}

int itr;
int windweek=numslot*5;
//cout << "Final Values are: ";
for(int g=0; g<filematrix.size();g++)
{
 //cout<< "File size is: " << filematrix[g].size() << "\n";
 itr = 0;
 for(int h=0; h<filematrix[g].size() ;h++)
 {
   //cout<<"Enter in: " << h<< endl;
   for(int q=0;q<windweek;q++)
   {
       int r=1, s=1;
       //cout<< filematrix[g][h] << " ";
        // Count no of smaller elements
        // in 0 to q-1
        for(int t = 0; t < q; t++) {
            if (filematrix[g][t+itr*windweek] < filematrix[g][h] ) r++;
            if (filematrix[g][t+itr*windweek] == filematrix[g][h] ) s++;
        }
        // Count no of smaller elements
        // in q+1 to windweek-1
        for (int t = q+1; t < windweek; t++) {
            if (filematrix[g][t+itr*windweek] < filematrix[g][h] ) r++;
            if (filematrix[g][t+itr*windweek] == filematrix[g][h] ) s++;
        }

        // Use Fractional Rank formula
        // fractional_rank = r + (n-1)/2

        rankmatrix[g].push_back(r + (s-1) * 0.5);
      //  if(rankmatrix[g][h]!=950 && rankmatrix[g][h]!=950.5 )
       // cout << rankmatrix[g][h]<<"("<<h<<") ";
       h++;
       if(h>=filematrix[g].size())
            break;
   }
   h--;
   itr++;
 }
// cout << "\n";
}

//cout<< "Ranks for the weeks are: ";
for(int g=0; g<rankmatrix.size();g++)
{
 //cout<< "File size is: " << rankmatrix[g].size() << "\n";
 for(int h=0; h<rankmatrix[g].size() ;h++)
 {
     //if(h%windweek==0)
      //  cout<<"Next quadrant \n";
   //cout<<rankmatrix[g][h]<<" ";
 }
 //cout << "\n";
}

//r value calculation and z value calculation
float denominator,denom1,exp1;
float d12aa, d12ab,d22ab,d12aas,d12abs,d22abs,sum12aa=0,sum12ab=0,sum22ab=0,r12aa,r12ab,r22ab,rm=0.0,z12aa=0.0,z12ab=0.0,z=0.0,f=0.0,h1=0.0;
//cout<<"This is for z values \n";
 for(int g=0; g<rankmatrix.size();g++)
 {
     for(int g1=0;g1<rankmatrix.size();g1++)
     {

        for(int h=0; h<windweek;h++)
        {
                //r1a2a
              d12aa = rankmatrix[g][h]-rankmatrix[g][h+windweek];
              d12ab = rankmatrix[g][h]-rankmatrix[g1][h+windweek];
              d22ab = rankmatrix[g][h+windweek]-rankmatrix[g1][h+windweek];
              d12aas = d12aa * d12aa;
              d12abs = d12ab * d12ab;
              d22abs = d22ab * d22ab;
              sum12aa+=d12aas;
              sum12ab+=d12abs;
              sum22ab+=d22abs;
              if(h==windweek-1)
              {
                  denom1 = (windweek*windweek)-1;
                  r12aa = 1-((6*sum12aa)/ (windweek*denom1));
                  r12ab = 1-((6*sum12ab)/ (windweek*denom1));
                  r22ab = 1-((6*sum22ab)/ (windweek*denom1));
                  //cout << "R12aa value is: "<<r12aa<<" ";
                 // cout << "R12ab value is: "<<r12ab<<" ";
                 // cout << "R22ab value is: "<<r22ab<<" ";
                  sum12aa=0;
                  sum12ab=0;
                  sum22ab=0;
                  rm = ((r12aa*r12aa) + (r12ab*r12ab))/2;
                  f = (1-r22ab)/(2*(1-rm));
                  h1 = (1-(f*rm))/(1-rm);
                 // exp = (1+r12aa)/(1-r12aa);
                  z12aa = 0.5 * (log((1+r12aa)/(1-r12aa)));
                  z12ab = 0.5 * (log((1+r12ab)/(1-r12ab)));
                  exp1 = (sqrt(windweek-3))/(2*(1-r22ab)*h1);
                //  cout<<"exp value is: "<<exp<<" ";
                  z = (z12aa-z12ab)*(exp1);
                 // cout<<"Z value is: "<<z<<" ";
                  disting[g][g1]=z;
              }
          }
         // cout<<"\n";
      }
      //cout<<"\n \n";
  }

double p = 0.3275911;
double a1 = 0.254829592;
double a2 = -0.284496736;
double a3 = 1.421413741;
double a4 = -1.453152027;
double a5 = 1.061405429;
int sign,dis=0,indis=0;
double x,t,erf,z1,p1;
cout<< "P values are: \n";
for(int g=0; g<rankmatrix.size();g++)
 {
     for(int g1=0;g1<rankmatrix.size();g1++)
     {
       //cout<<disting[g][g1]<<" ";
       z1 = disting[g][g1];
       if(z1<0.0)
            sign = -1.0;
        else
            sign = 1.0;
        x = abs(z1) / sqrt(2.0);
        t = 1.0 / (1.0 + (p * x));
        erf = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);
       // cout<<" erf: "<<erf<<" ";
      //  cout<<"1-erf: "<<(1.0-erf)<<" ";
     /*   if(z1<0.0)
            p1 = 0.5 * (1.0 - erf);
        else
            p1 = 0.5 * (1.0 + erf);*/
            p1 = 0.5 * (1.0 + sign * erf);
        if(p1<=0.05)
            dis++;
        else
            indis++;
        cout<<p1<<" ";
     }
     cout<<"\n";
 }
 cout<<"Distinguishable are: "<<dis<< " Indistinguishable are: "<<indis;
return 0;

}
