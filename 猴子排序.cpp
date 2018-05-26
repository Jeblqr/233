#include<iostream>
#include<fstream>
#include<ctime>
#include<algorithm>
using namespace std;
///*
int a[100],n;
long long k;
bool pd()
{
	for (int i=2;i<=n;i++)
		if (a[i]<a[i-1])
			return 1;
	return 0;
}
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>a[i];
	int st=clock();
	while (pd())
		random_shuffle(a+1,a+n+1),k++;
	for (int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	cout<<endl<<"OK, used "<<clock()-st<<endl<<k;
	cin.get();
	cin.get();
	return 0;
}
//*/
/*int main()
{
	fstream fout("a.txt");
	int n;
	cin>>n;
	fout<<n<<endl;
	srand(clock());
	while (n--)
		fout<<rand()<<' ';
	return 0;
}
*/ 
