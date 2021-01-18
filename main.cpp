//KruskalMTKe
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
//#include<windows.h>

#define MaxV 100
int A[MaxV][MaxV];
int V = 0;
int KQ[2][MaxV];
int B[2][MaxV];
typedef struct Egde
{
	int x,y;
}Egde;
void DocFile(int A[][MaxV], int &V)
{	
	FILE *f = fopen("input1.txt","rb");
	fscanf(f,"%d",&V);
	for(int i = 0; i < V; i++)
		for(int j = 0; j < V; j++)
			fscanf(f,"%d", &A[i][j]);
	fclose(f);
}
//nhap vao danh sach canh
int DSC[3][MaxV];
int canh = 0;
void NhapDuLieu(int DSC[][MaxV], int &V)
{
	printf("Nhap vao so luong dinh: ");
	scanf("%d",&V);
	printf("Nhap vao so luong canh: ");
	scanf("%d",&canh);
	for(int i = 0; i < canh; i++)
	{
		printf("\n-Nhap vao canh %d :",i+1);
		printf("\n");
		do{
			printf("\t+Nhap vao dinh dau: ");
			scanf("%d",&DSC[0][i]);
		}while(DSC[0][i] <= 0 || DSC[0][i] > V);
		do{			
			printf("\t+Nhap vao dinh cuoi: ");
			scanf("%d",&DSC[1][i]);
		}while(DSC[1][i] <= 0 || DSC[1][i] > V);		
		printf("\tNhap vao trong so cua canh %d: ",i+1);
		scanf("%d",&DSC[2][i]);
	}	
}
//chuyen danh sach canh thanh Ma Tran Ke
void Change(int A[][MaxV], int DSC[][MaxV], int V, int canh)
{
	//gan cho danh sach Ke bang 0
	for(int i = 0; i < V; i++)
		for(int j = 0; j < V; j ++)
			A[i][j] = 0;
	//chuyen sang Ma Tran Ke
	for(int  i = 0; i < canh; i++)
	{
		A[DSC[0][i]-1][DSC[1][i]-1] = DSC[2][i];
		A[DSC[1][i]-1][DSC[0][i]-1] = DSC[2][i];
	}		
}
void XuatMTKe(int A[][MaxV], int V)
{
	printf("So dinh la %d \n",V);
	printf("Ma Tran Ke:\n");	
	for(int i=0;i<V;i++)
	{
		for(int j=0;j<V;j++)
			printf("%d ",A[i][j]);
		printf("\n");
	}
}
void GhiFile(Egde*L,int V,int Sum) 
{
    FILE*f = fopen("output.txt","wb");
    fprintf(f,"%d\n",Sum);
    for(int i =0; i<V-1; i++)
      fprintf(f,"%d - %d\n",L[i].x+1,L[i].y+1);
  fclose(f);
}
void GhiDL(Egde *L,int V, int Sum)
{
	printf("\nTong chi phi trong so %d\n",Sum);
	printf("cac canh cua cay khung nho nhat la: \n");
	for(int i = 0; i < V - 1; i++)
		printf("%d - %d\n",L[i].x+1,L[i].y+1);
}
void GhiKQ(Egde *L,int V, int KQ[][MaxV])
{
	for(int i = 0; i < V - 1; i++)
	{
		KQ[0][i] = L[i].x;
		KQ[1][i] = L[i].y;
	}
}
void Circle(int x, int y)
{
	circle(x,y,17);	
}
void Name(int i, int x, int y)
{
	char cc[5];
	itoa(i,cc,10);
	settextstyle(10,0,2);
	outtextxy(x - 7,y - 11,cc);
}
void TaoDiem(int V, int A[][MaxV])
{		
	for(int i = 0; i < V; i ++)
	{
		B[0][i] = 40 + rand() % 941;
		B[1][i] = 40 + rand() % 621;			
	}
	for(int  i = 0; i < V; i ++)
	{
		int color = 1 + rand()%15;
		setcolor(color);
		Circle(B[0][i],B[1][i]);
		Name(i+1,B[0][i],B[1][i]);
	}
	for(int i = 0; i < V; i++)		
		for(int j = i; j < V; j++)
			if(A[i][j] != 0)
			{			
				setcolor(WHITE);	
				line(B[0][i],B[1][i],B[0][j],B[1][j]);
				Name(A[i][j],(B[0][i] + B[0][j]) / 2,(B[1][i] + B[1][j]) / 2);
				
			}	
			
}
void Kruskal (int A[][MaxV], int V)
{
	int *D = new int[V];
	Egde *L = new Egde[V-1];
	int Min = 99999, Dem = 0, Sum = 0, T = 0, Temp;
	for(int i = 0; i < V; i++)
		D[i] = 0;
	do{
		Min = 99999;
		for(int i = 0; i< V; i++)
			for(int j = 0; j<V;j++)
				if((A[i][j] > 0 && A[i][j] < Min) && !(D[i]!=0 && D[i]==D[j]))
				{
					Min = A[i][j];
					L[Dem].x = i;
					L[Dem].y = j;
				}
		if(D[L[Dem].x] == 0 && D[L[Dem].y] == 0)
		{
			T++;
			D[L[Dem].x] = D[L[Dem].y] = T;			
		}
		if(D[L[Dem].x] == 0 && D[L[Dem].y] != 0)
		{
			D[L[Dem].x] = D[L[Dem].y];
		}
		if(D[L[Dem].x] != 0 && D[L[Dem].y] == 0)
		{
			D[L[Dem].y] = D[L[Dem].x];
		}
		if(D[L[Dem].x] != D[L[Dem].y] && D[L[Dem].y] != 0)
		{
			Temp = D[L[Dem].x];
			for(int i = 0; i< V ;i++)
				if(Temp == D[i])
					D[i] = D[L[Dem].y];
		}
		Sum = Sum + Min;
		Dem++;
	}
	while(Dem < V - 1);
	GhiDL(L,V,Sum);
	GhiKQ(L,V,KQ);
}
void VeMain()
{
	rectangle(10, 10, 1000, 680);	
	rectangle(0,0,1010,690);
	setfillstyle(SOLID_FILL,RED);
 	floodfill(6,6,15);			
}
void VeCaculator()
{
	rectangle(1020,5,1350,685);
	setfillstyle(SOLID_FILL,BLUE);
 	floodfill(1021,51,15);
	
	settextstyle(10,0,7);
	setbkcolor(BLUE);
	setcolor(WHITE);
	outtextxy(1060,15,"KRUSKAL");
	setbkcolor(0);
	
	rectangle(1027,90,1343,580);
	setfillstyle(SOLID_FILL,BLACK);
 	floodfill(1028,100,15);
 	 	
 	
	settextstyle(3,0,2);
	setbkcolor(BLUE);
	outtextxy(1030,585,"Press any key to change Graph!");
	setbkcolor(0);
	
	settextstyle(10,0,3);
	rectangle(1020,645,1350,685);
	setfillstyle(SOLID_FILL,RED);
 	floodfill(1022,650,15);
 	setbkcolor(RED);
	outtextxy(1030,650,"PRESS ENTER TO KRUSKAL");
	setbkcolor(0);
}
void Input()
{
	settextstyle(3,0,1);
	outtextxy(1035,100,"Input:");
	outtextxy(1035, 130,"So dinh Ma Tran Ke: "); 
	char T[5];
	itoa(V,T,10);
	outtextxy(1250,130,T);
	for(int i = 0; i < V; i++)
	{
		setcolor(BLUE);
		Name(i+1,30*i+1075,170);		
		Name(i+1,1045,25*i+200);
	}
	for(int i=0;i<V;i++)
	{		
		for(int j=0;j<V;j++)
		{	setcolor(WHITE);	
			settextstyle(3,0,0);				
			Name(A[i][j],30*i+1075,25*j+200);
		}
	}
}
void Output()
{ 	
	outtextxy(1035,100,"Output:");
	outtextxy(1035, 130,"So canh cua cay khung"); 
	char T[5];
	itoa(V - 1,T,10);
	setcolor(BLUE);
	outtextxy(1035, 160, T);
	setcolor(WHITE);
	outtextxy(1055, 160, "Bao gom cac canh:");
	
}

void VeCayKhung1(int KQ[][MaxV], int V)
{
	cleardevice();
	VeMain();
	VeCaculator();
	Output();
	
	//ve lai cac diem, cac duong thang va cac trong so
	for(int i = 0; i < V; i++)		
		for(int j = i; j < V; j++)
			if(A[i][j] != 0)
			{				
				line(B[0][i],B[1][i],B[0][j],B[1][j]);
				Name(A[i][j],(B[0][i] + B[0][j]) / 2,(B[1][i] + B[1][j]) / 2);
				
			}	
	for(int  i = 0; i < V; i ++)
	{
		int color = 1 + rand()%15;
		setcolor(color);
		Circle(B[0][i],B[1][i]);
		Name(i+1,B[0][i],B[1][i]);
	}
	
	int c;
	int TS = 0;
	
	int i = 0;
	char key;
	int value;
	do
	{	
		if(i == (V-1)) break;
		setcolor(RED);		
		setlinestyle(c, 0, 3); 
		line(B[0][KQ[0][i]],B[1][KQ[0][i]],B[0][KQ[1][i]],B[1][KQ[1][i]]);
		setcolor(WHITE);		
		Name(A[KQ[0][i]][KQ[1][i]],(B[0][KQ[0][i]] + B[0][KQ[1][i]]) / 2,
		(B[1][KQ[0][i]] + B[1][KQ[1][i]]) / 2);	
		
		char out[10];
		itoa(KQ[0][i]+1,out,10);
		outtextxy(1045,25*i+200,out);
		outtextxy(1065,25*i+200,"-");
		itoa(KQ[1][i]+1,out,10);
		outtextxy(1085,25*i+200,out);
			
		TS += A[KQ[0][i]][KQ[1][i]];
		itoa(TS,out,10);
		outtextxy(1040,550,"Tong trong so:");
		setcolor(RED);
		settextstyle(10,0,5);
		outtextxy(1250,530,out);
		setcolor(WHITE);
		
		key = getch();
		value = key;
		if(value == 13)	i++;
		
	}while(1);
	/*
	for(int i = 0 ; i < V - 1; i++)
	{	
		setcolor(RED);		
		setlinestyle(c, 0, 3); 
		line(B[0][KQ[0][i]],B[1][KQ[0][i]],B[0][KQ[1][i]],B[1][KQ[1][i]]);
		setcolor(WHITE);		
		Name(A[KQ[0][i]][KQ[1][i]],(B[0][KQ[0][i]] + B[0][KQ[1][i]]) / 2,(B[1][KQ[0][i]] + B[1][KQ[1][i]]) / 2);	
		
		char out[10];
		itoa(KQ[0][i]+1,out,10);
		outtextxy(1045,25*i+200,out);
		outtextxy(1065,25*i+200,"-");
		itoa(KQ[1][i]+1,out,10);
		outtextxy(1085,25*i+200,out);
		
		TS += A[KQ[0][i]][KQ[1][i]];
		itoa(TS,out,10);
		outtextxy(1040,550,"Tong trong so:");
		outtextxy(1300,550,out);
		delay(1000);	
	}
	*/
	setlinestyle(c, 0, 0); 
}
void VeCayKhung2(int KQ[][MaxV], int V)
{
	cleardevice();
	VeMain();
	VeCaculator();
	Output();

	for(int  i = 0; i < V; i ++)
	{
		Circle(B[0][i],B[1][i]);
		Name(i+1,B[0][i],B[1][i]);		
	}
	int c;
	int TS = 0;
	for(int i = 0 ; i < V - 1; i++)
	{	
		setcolor(RED);		
		setlinestyle(c, 0, 3); 
		line(B[0][KQ[0][i]],B[1][KQ[0][i]],B[0][KQ[1][i]],B[1][KQ[1][i]]);
		setcolor(WHITE);		
		Name(A[KQ[0][i]][KQ[1][i]],(B[0][KQ[0][i]] + B[0][KQ[1][i]]) / 2,(B[1][KQ[0][i]] + B[1][KQ[1][i]]) / 2);	
		
		char out[10];
		itoa(KQ[0][i]+1,out,10);
		outtextxy(1045,25*i+200,out);
		outtextxy(1065,25*i+200,"-");
		itoa(KQ[1][i]+1,out,10);
		outtextxy(1085,25*i+200,out);
		
		TS += A[KQ[0][i]][KQ[1][i]];
		itoa(TS,out,10);
		outtextxy(1040,550,"Tong trong so:");
		setcolor(RED);
		settextstyle(10,0,5);
		outtextxy(1250,530,out);
		setcolor(WHITE);	
	}
	setlinestyle(c, 0, 0); 
}

int main()
{
	//phan mo dau chuon trinh
	printf("\t\t**WELCOME TO KRUSKAL ALGORIHM**\n\n");
	printf("Cac loai input:\t(press number you want to input!)\n\t1:Nhap tu file\n\t2:Nhap tu ban phim\n");
	char type;
	printf("\nNhap vao loai input: ");
    scanf("%c", &type);
    switch(type)
    {
    	case '1' :
			DocFile(A,V); break;
    	case '2' :
		{
			NhapDuLieu(DSC,V);
			Change(A,DSC,V,canh);
			break;
		}
		default: 
		{
			printf("Nhap sai loai. Mac dinh se chon loai nhap tu file\n");
			DocFile(A,V); break;
		}
	}
	//Phan thuat toan
	//system("cls");
	XuatMTKe(A,V);	
	Kruskal(A,V);
	
	//Phan do hoa	
	initwindow(1400,1000);
	settextstyle(10,0,10);
	outtextxy(400,200,"KRUSKAL");
	settextstyle(3,0,6);
	outtextxy(400,330,"-----Design by Quang----");
	//getch();
	delay(1000);	
	cleardevice();
	VeMain();	//ve khung Bieu dien
	VeCaculator();
	TaoDiem(V,A);
	Input();
	
	char key_press;
	int ascii_value;
	while(1)
	{
		key_press = getch();
		ascii_value = key_press;
		if(ascii_value == 13 ) // ENTER button
			break;			
		cleardevice(); 
		VeMain();
		VeCaculator();
		TaoDiem(V,A);	
		Input();	
	}	
	VeCayKhung1(KQ,V);
	cleardevice();
	VeCayKhung2(KQ,V);
	getch();
	cleardevice();
	setfillstyle(SOLID_FILL,WHITE);
 	floodfill(1,1,15);	
	setcolor(RED);
	setbkcolor(WHITE);
	settextstyle(10,0,10);
	outtextxy(10,200,"KRUSKAL Thank you!");
	delay(2000);
	//getch();
	closegraph();	
	
	return 1;
}
