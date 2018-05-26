#include<bits/stdc++.h>
using namespace std;
int a[100],n;
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
		random_shuffle(a+1,a+n+1);
	for (int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	cout<<endl<<"OK, used "<<clock()-st;
	return 0;
}
