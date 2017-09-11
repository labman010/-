//edit test 2017.9.11 22:00
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <math.h>//加上没找到报错
using namespace std;
struct Matrix
{
	char name;
	int line;
	int row;
	double aup[50][50];
	int adown[50][50];
};
Matrix h[100];
int n=0;
Matrix mid[100];
int nmid=0;

void Bytxt()//如何用分数  不用了！！mdzz
{
	printf("请输入文件名和导入的矩阵名：\n");
	char p[20];
	char namet;
	char aa;
	scanf("%s%c%c",p,&aa,&namet);
	FILE*fp=fopen(p,"r");
	if(fp==NULL)
	{
		cout<<"error";
		return;
	}
	char temp[100];
	h[n].name=namet;
	int i=0;
	int ll=0;
	int r=1;
	while(fgets(temp,sizeof(temp),fp)!=NULL)
	{
		if(r==1)
			for(int i=0;temp[i]!='\0';i++)
			{
				if(temp[i]==' ')
					r++;
			}
		ll++;
	}
	h[n].row=r;
	h[n].line=ll;
	fclose(fp);
	FILE*fp2=fopen(p,"r");
	double a=0;
	for(int k=0;k<ll;k++)
	{	for(int j=0;j<r;j++)
		{
			fscanf(fp2,"%lf",&a);
			h[n].aup[k][j]=a;
			h[n].adown[k][j]=1;
		}
	}
	fclose(fp2);
	n++;
}

void Byinput()
{
	printf("请输入矩阵名:\n");
	scanf("%c",&h[n].name);
	printf("请输入行列：\n");
	scanf("%d%d",&h[n].line,&h[n].row);
	for(int i=0;i<h[n].line;i++)
	{
		printf("%s","请输入一行：");
		for(int j=0;j<h[n].row;j++)
		{
			scanf("%lf",&h[n].aup[i][j]);	
			h[n].adown[i][j]=1;
		}
	}
	n++;
}
void Aput()
{
	int t2=0;
	while(t2!=-1)
	{
		printf("请选择输入矩阵的方式：\n");
		printf("1.文件导入\n");
		printf("2.从控制台输入\n");
		printf("3.不搞了\n");
		cin>>t2;
		if(t2==1)
		{
			Bytxt();
		}
		else if(t2==2)
		{
			char ch=getchar();
			Byinput();
		}
		else if(t2==3)
			break;
	}
}

int plusz(char x,char y)
{
	int xn=0,yn=0;
	for(int i=0;i<n;i++)
	{	
		if(h[i].name==x)
			xn=i;
		if(h[i].name==y)
			yn=i;
	}
	if(h[xn].line!=h[yn].line || h[xn].row!=h[yn].row)
	{	
		cout<<"error when plus!"<<endl;
		return -1;
	}
	h[n].line=h[xn].line;
	h[n].row=h[xn].row;
	for(int i=0;i<h[xn].line;i++)
	{
		for(int j=0;j<h[xn].row;j++)
		{
			h[n].aup[i][j]=h[xn].aup[i][j]+h[yn].aup[i][j];
			h[n].adown[i][j]=1;
		}
	}
	h[n].name='a'+n; //keyi
	return 0;
}
int jianfa(char x,char y)
{
	int xn=0,yn=0;
	for(int i=0;i<n;i++)
	{	
		if(h[i].name==x)
			xn=i;
		if(h[i].name==y)
			yn=i;
	}
	if(h[xn].line!=h[yn].line || h[xn].row!=h[yn].row)
	{	
		cout<<"error when 减法!"<<endl;
		return -1;
	}
	h[n].line=h[xn].line;
	h[n].row=h[xn].row;
	for(int i=0;i<h[xn].line;i++)
	{
		for(int j=0;j<h[xn].row;j++)
		{
			h[n].aup[i][j]=h[xn].aup[i][j]-h[yn].aup[i][j];
			h[n].adown[i][j]=1;
		}
	}
	h[n].name='a'+n;
	return 0;

}
int multiply(char x,char y)
{
	int xn=0,yn=0;
	for(int i=0;i<n;i++)
	{	
		if(h[i].name==x)
			xn=i;
		if(h[i].name==y)
			yn=i;
	}
	if(h[xn].row!=h[yn].line)
	{	
		cout<<"error when muiltiply!"<<endl;
		return -1;
	}
	h[n].line=h[xn].line;
	h[n].row=h[yn].row;
	for(int i=0;i<h[n].line;i++)
		for(int k=0;k<h[n].row;k++)
		{
			double r=h[xn].aup[i][k];
			for(int j=0;j<h[n].row;j++)
			{	h[n].aup[i][j]+=r*h[yn].aup[k][j];
				h[n].adown[i][j]=1;
			}
		}
	h[n].name='a'+n;
	return 0;

}
double qiumo(int nm)
{
	double sum=0;
	if(mid[nm].line>2)
	{
		
		int u=1;
		int nm2=nm;
		for(int k=0;k<mid[nm].line;k++)
		{
			nm2++;
			mid[nm2].line=mid[nm].line-1;
			mid[nm2].row=mid[nm].row-1;
			for(int i=0;i<mid[nm2].line;i++)
			{
				for(int j=0;j<mid[nm2].row;j++)
				{
					if(j>=k)
					{
						mid[nm2].aup[i][j]=mid[nm].aup[i+1][j+1];
					}
					else
						mid[nm2].aup[i][j]=mid[nm].aup[i+1][j];
				}
			}
			sum+=u*mid[nm].aup[0][k]*qiumo(nm2);
			u=u*(-1);
		}
	}
	else
	{
		sum=mid[nm].aup[0][0]*mid[nm].aup[1][1]-mid[nm].aup[0][1]*mid[nm].aup[1][0];
	}
		return sum;
}
int overM(char x)
{
	int numx;
	for(int i=0;i<n;i++)
	{
		if(h[i].name==x)
		{
			numx=i;
			break;
		}
	}
	if(h[numx].line!=h[numx].row)
	{
		cout<<"row != line,error!"<<endl;
		return -1;
	}
	mid[nmid].line=h[numx].line;
	mid[nmid].row=h[numx].row;
	for(int i=0;i<h[numx].line;i++)
	{
		for(int j=0;j<h[numx].row;j++)
		{
			mid[nmid].aup[i][j]=h[numx].aup[i][j];
			mid[nmid].adown[i][j]=1;
		}
	}
	double mo=qiumo(nmid);
	if(mo==0)
		return -1;
	h[n].name='a'+n;
	h[n].line=h[numx].line;
	h[n].row=h[numx].row;
	mid[0].line=h[numx].line-1;
	mid[0].row=h[numx].row-1;
	for(int i=0;i<h[numx].line;i++)//求矩阵星号
	{
		for(int j=0;j<h[numx].row;j++)
		{	
			for(int a=0;a<h[numx].line-1;a++)
			{
				for(int b=0;b<h[numx].row-1;b++)
				{					
					if(a<i&&b<j)
					{
						mid[0].aup[a][b]=h[numx].aup[a][b];
					}
					else if(a<i&&b>=j)
					{
						mid[0].aup[a][b]=h[numx].aup[a][b+1];
					}
					else if(a>=i&&b<j)
					{
						mid[0].aup[a][b]=h[numx].aup[a+1][b];
					}
					else
					{
						mid[0].aup[a][b]=h[numx].aup[a+1][b+1];
					}
				}
			}
			double mmm=qiumo(0);
			h[n].aup[i][j]=qiumo(0)/mo;
			if((i+j)%2==1)
				h[n].aup[i][j]=-h[n].aup[i][j];
		}
	}
	for(int i=0;i<h[n].line;i++) //行列转置
	{
		for(int j=i;j<h[n].row;j++)
		{
			double tp=h[n].aup[i][j];
			h[n].aup[i][j]=h[n].aup[j][i];
			h[n].aup[j][i]=tp;
		}
	}
	nmid=0;
	return 0;
}
int divition(char x,char y)
{
	int xn=0,yn=0;
	for(int i=0;i<n;i++)
	{	
		if(h[i].name==x)
			xn=i;
		if(h[i].name==y)
			yn=i;
	}
	if(h[xn].row!=h[yn].line)
	{	
		cout<<"error when divide (line!=row)!"<<endl;
		return -1;
	}
	overM(y);
	n++;
	yn=n-1;
	h[n].line=h[xn].line;
	h[n].row=h[yn].row;
	for(int i=0;i<h[n].line;i++)
		for(int k=0;k<h[n].row;k++)
		{
			double r=h[xn].aup[i][k];
			for(int j=0;j<h[n].row;j++)
			{	h[n].aup[i][j]+=r*h[yn].aup[k][j];
				h[n].adown[i][j]=1;
			}
		}
	h[n].name='a'+n;
	return 0;
}
int Sc2(char*m2)
{
	for(int i=0;m2[i]!='\0';i++)
	{	
		if(m2[i]=='|')
		{
			int jn=overM(m2[i-1]);
			if(jn==-1)
				return -1;
			m2[i-1]=h[n].name;
			n++;
			int i2=i;
			for(int j=i+2;m2[j]!='\0';i2++,j++)
			{
				m2[i2]=m2[j];
			}
			m2[i2]='\0';
			i=0;
		}
	}
	for(int i=0;m2[i]!='\0';i++)
	{
		if(m2[i]=='*')
		{
			int jm=multiply(m2[i-1],m2[i+1]);
			if(jm==-1)
				return -1;
			m2[i-1]=h[n].name;
			n++;
			int i2=i;
			for(int j=i+2;m2[j]!='\0';i2++,j++)
			{
				m2[i2]=m2[j];
			}
			m2[i2]='\0';
			i=0;
		}
		if(m2[i]=='/')
		{
			int jd=divition(m2[i-1],m2[i+1]);
			if(jd==-1)
				return -1;
			m2[i-1]=h[n].name;
			n++;
			int i2=i;
			for(int j=i+2;m2[j]!='\0';i2++,j++)
			{
				m2[i2]=m2[j];
			}
			m2[i2]='\0';
			i=0;
		}
	}
	for(int i=0;m2[i]!='\0';i++)
	{
		if(m2[i]=='+')
		{
			int jj=plusz(m2[i-1],m2[i+1]);
			if(jj==-1)
				return -1;
			m2[i-1]=h[n].name;
			n++;
			int i2=i;
			for(int j=i+2;m2[j]!='\0';i2++,j++)
			{
				m2[i2]=m2[j];
			}
			m2[i2]='\0';
			i=0;
		}
		if(m2[i]=='-')
		{
			int jj=jianfa(m2[i-1],m2[i+1]);
			if(jj==-1)
				return -1;
			m2[i-1]=h[n].name;
			n++;
			int i2=i;
			for(int j=i+2;m2[j]!='\0';i2++,j++)
			{
				m2[i2]=m2[j];
			}
			m2[i2]='\0';
			i=0;
		}
	}
	return 0;
//	cout<<m2<<endl;
}
int Sc(char*nb)
{
L:	bool judge=false;
	for(int g=0;nb[g]!='\0';g++)
		if(nb[g]=='(')
		{
			judge=true;
			break;
		}
	if(judge==true)
	{
		int i=0;
		int x1=0,x2=0;
		int KL=0,KR=0;
		for(;nb[i]!='\0';i++)
		{
			if(nb[i]=='(')
			{
				if(x1==0)
					KL=i;
				x1++;
			}
			if(nb[i]==')')
			{
				x2++;
				if(x1==x2)
				{
					KR=i;
					char w[30];
					int q=0;
					for(;q<KR-KL-1;q++)
					{
						w[q]=nb[q+KL+1];
					}
					w[q]='\0';
					Sc(w);
					nb[KL]=h[n-1].name;
					int i2=KL+1;
					for(int j=KR+1;nb[j]!='\0';i2++,j++)
					{
						nb[i2]=nb[j];
					}
					nb[i2]='\0';
					goto L;
				}
			}
		}
	}
	else
	{	
		int js=Sc2(nb);	
		if(js==-1)
		{	
			return -1;
		}
	}
	return 0;
}
int Exam(char*pe)
{	int numl=0;
	int numr=0;
	int kk=0;
	int t=0;
	for(int i=0;pe[i]!='\0';i++)
	{
		if(pe[i]=='(')
		{
			numl++;
			kk++;
			t=i;
		}
		if(pe[i]==')')
		{
			if(kk==0)
			{
				cout<<"wrong with )( !"<<endl;
				return -1;
			}
			numr++;
			kk++;
			t=i;
		}
	}		
	if(t!=0&&(pe[t]=='('||numl!=numr))
	{
		cout<<"wrong with )( !"<<endl;
				return -1;
	}

	if(pe[0]==')'||pe[0]=='|'||pe[0]=='+'||pe[0]=='-'||pe[0]=='/'||pe[0]=='*')
	{
		cout<<"wrong!"<<endl;
		return -1;
	}
	for(int i=1;pe[i+1]!='\0';i++)
	{
		if(pe[i]=='(')
		{
			if(pe[i-1]!='+'&&pe[i-1]!='-'&&pe[i-1]!='*'&&pe[i-1]!='/'&&pe[i-1]!='(')
			{
				cout<<"wrong with ( )!"<<endl;
				return -1;
			}
			if(pe[i+1]==')'||pe[i+1]=='|'||pe[i+1]=='+'||pe[i+1]=='-'||pe[i+1]=='/'||pe[i+1]=='*')
			{
				cout<<"wrong with ( )!"<<endl;
				return -1;
			}
		}
		else if(pe[i]==')')
		{
			if(i==1)
			{
				cout<<"wrong with ( )!"<<endl;
				return -1;
			}
			if(pe[i+1]!='+'&&pe[i+1]!='-'&&pe[i+1]!='*'&&pe[i+1]!='/'&&pe[i+1]!=')'&&pe[i+1]!='|')
			{
				cout<<"wrong with ( )!"<<endl;
				return -1;
			}
		}
		else if(pe[i]=='|')
		{
			if(pe[i+1]!='1')
			{	cout<<"wrong with | !"<<endl;
				return -1;
			}
			if((pe[i-1]<65 || pe[i-1]>90)&&pe[i-1]!=')')
			{
				cout<<"wrong with | !"<<endl;
				return -1;
			}
		}
		else if(pe[i]=='+'||pe[i]=='-'||pe[i]=='/'||pe[i]=='*')
		{
			if((pe[i-1]<65 || pe[i-1]>90)&&pe[i-1]!='1'&&pe[i-1]!=')')
			{
				cout<<"wrong with +- !"<<endl;
				return -1;
			}
			if((pe[i+1]<65 || pe[i+1]>90)&&pe[i+1]!='(')
			{
				cout<<"wrong with +- !"<<endl;
				return -1;
			}
		}
		else
		{
			if((pe[i+1]>='A'&&pe[i+1]<='Z') || (pe[i-1]>='A'&&pe[i-1]<='Z'))
			{
				cout<<"wrong with repeat !"<<endl;
				return -1;
			}
		}
	}
	return 0;

}
void Ajisuan()
{
	printf("请输入表达式：");
	char p[30],p2[30];
	scanf("%s",p);
	int judge=Exam(p);
	if(judge==-1)
	{
		return;
	}
	strcpy(p2,p);
	int ja=Sc(p);
	if(ja==-1)
		return;
	printf("%s%c\n",p2,'=');
	for(int i=0;i<h[n-1].line;i++)
	{
		for(int j=0;j<h[n-1].row;j++)
		{
			printf("%.4lf ",h[n-1].aup[i][j]);
		}
		printf("\n");		
	}
}
int main()
{	
	int t=0;
	while(t!=-1)
	{
		printf("1.输入矩阵\n");
		printf("2.开始计算\n");
		printf("3.退出\n");
		printf("4.展示矩阵\n");
		scanf("%d",&t);
		if(t==3)
			break;
		else if(t==1)
		{
			Aput();
		}
		else if(t==2)
		{
			Ajisuan();
		}
		else if (t==4)
		{
			for(int p=0;p<n;p++)
				{
					printf("%c\n",h[p].name);
				for(int i=0;i<h[p].line;i++)
				{
					for(int j=0;j<h[p].row;j++)
					{
						printf("%.4lf ",h[p].aup[i][j]);
					}
					printf("\n");
				}
			}
		}


	
	}

}//http://www.jb51.net/article/36422.htm
