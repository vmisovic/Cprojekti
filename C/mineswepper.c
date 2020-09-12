#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int dx,dy,m,bp;
static int a[100][100],b[100][100];
void ispis(int c[][100])
{
    printf("Broj preostalih mina: %d\n",bp);
    printf("  ");
    for(int i=0;i<dx;i++)
        printf(" %d",i);
    printf("\n");
    for(int j=0;j<dy;j++)
    {
        printf("%d",j);
        if(j<10)putchar(' ');
        for(int i=0;i<dx;i++)
        {
            switch (c[i][j])
            {
            case 0: printf("| ");break;
            case -1: printf("|X");break;
            case -2: printf("|-");break;
            case -3: printf("|*");break;
            default: printf("|%d",c[i][j]);break;
            }
            if(i>=10)putchar(' ');
        }       
        printf("|\n");
    }
    printf("\n========================\n");
}
void povecaj(int mx,int my,int a[][100])
{
    int x[8]={-1,-1,-1,0, 0, 1,1,1};
    int y[8]={-1, 0, 1,1,-1,-1,0,1};
    for(int i=0;i<8;i++)
    {
        int px,py;
        px=mx+x[i];
        py=my+y[i];
        if(px>=0&&(px<dx)&&py>=0&&(py<dy))
            if(a[px][py]!=-1)
                a[px][py]++;
    }
}
void generisi(int x,int y)
{
    int mx,my,i=0;
    srand(time(0));
    while (i<m)
    {
        mx=rand()%dx;
        my=rand()%dy;
        if(a[mx][my]!=-1&&(mx>=(x-1)&&mx<=(x+1)&&my>=(y-1)&&my<=(y+1))!=1)//dodatan uslov da pocetno polje nije bomba vec 0
        {
            a[mx][my]=-1;
            povecaj(mx,my,a);
            i++;
        }
    }
}
int provera()
{
    int nereseno=0;
    for(int j=0;j<dy;j++)
        for(int i=0;i<dx;i++)
            if(a[i][j]!=b[i][j]&&a[i][j]!=-1)
                nereseno=1;
    return nereseno;
}
void otkrij(int x,int y)
{
    if(a[x][y]==-1)
    {
        printf("KRAJ IGRE-pogodili ste minu!\n");
        ispis(a);
        exit(2);
    }
    else if(a[x][y]==0)
    {
        b[x][y]=0;
        int mx[8]={-1,-1,-1,0, 0, 1,1,1};
        int my[8]={-1, 0, 1,1,-1,-1,0,1};
        for(int i=0;i<8;i++)
        {
            int px,py;
            px=x+mx[i];
            py=y+my[i];
            if(px>=0&&(px<dx)&&py>=0&&(py<dy))
                if(a[px][py]==0&&b[px][py]==-2)
                {
                    b[px][py]=0;
                    otkrij(px,py);
                }
                else if(b[px][py]!=-3)
                    b[px][py]=a[px][py];
        }
    }
    else
        b[x][y]=a[x][y];
}
void postavi_zastavice(int x,int y)
{
    int mx[8]={-1,-1,-1,0, 0, 1,1,1};
    int my[8]={-1, 0, 1,1,-1,-1,0,1};
    int prazna=0;
    for(int i=0;i<8;i++)
    {
        int px,py;
        px=x+mx[i];
        py=y+my[i];
        if(px>=0&&(px<dx)&&py>=0&&(py<dy)&&(b[px][py]==-2)||b[px][py]==-3)//ovde dodaj
            prazna++;
    }
    if(b[x][y]==prazna)
    {
        for(int i=0;i<8;i++)
        {
            int px,py;
            px=x+mx[i];
            py=y+my[i];
            if(px>=0&&(px<dx)&&py>=0&&(py<dy)&&(b[px][py]==-2))//ovde dodaj
            {
                b[px][py]=-3;
                bp--;
            }
        }
    }
}
void raskopaj_oko(int x,int y)
{
    int mx[8]={-1,-1,-1,0, 0, 1,1,1};
    int my[8]={-1, 0, 1,1,-1,-1,0,1};
    int zastavice=0;
    for(int i=0;i<8;i++)
    {
        int px,py;
        px=x+mx[i];
        py=y+my[i];
        if(px>=0&&(px<dx)&&py>=0&&(py<dy)&&(b[px][py]==-3))
            zastavice++;
    }
    if(b[x][y]==zastavice)
    {
        for(int i=0;i<8;i++)
        {
            int px,py;
            px=x+mx[i];
            py=y+my[i];
            if(px>=0&&(px<dx)&&py>=0&&(py<dy)&&(b[px][py]==-2))//ovde dodaj
                otkrij(px,py);
        }
    }
}
int main()
{
    int i=0;
    printf("======================================\nMinolovac v-1.5 1.9.2020. Dobrodosli!\n");
    printf("Na pocetku ne mozete pogogiti bombu\nKoristitie raskopavaje i automatsko\npostavljanje zastavica za vec otvorena polja\n======================================\n");
    printf("Unesite dimenzije X(kolone) i Y(redovi) kao i broj Mina:\n");
    scanf("%d %d %d",&dx,&dy,&m);
    printf("========================\nX:%d Y:%d Mine:%d\n",dx,dy,m);
    for(int j=0;j<dy;j++)
    {
        for(int i=0;i<dx;i++)
            b[i][j]=-2;
    }
    char izbor;
    int x,y,mx,my;
    bp=m;
    ispis(b);
    printf("Unesi kordinate (x,y):\n");
    scanf("%d %d",&x,&y);
    generisi(x,y);
    otkrij(x,y);
    ispis(b);
    while(provera())
    {
        printf("Unesi kordinate (x,y):\n");
        scanf("%d %d",&x,&y);
        if(b[x][y]==-3)
        {
            printf("Zastavica skinuta.\n");
            b[x][y]=-2;
            bp++;
        }
        else if(b[x][y]==-2)
        {
        printf("Kopaj [ENTER]; Zastavica [bilo koji karakter]; Izlaz [i]\n");
        while(getchar()!='\n');
        izbor=getchar();
        while(izbor!='\n'&&getchar()!='\n');
        if(izbor=='i')
        {
            printf("Napustili ste igru.\n");
            exit(1);
        }
        if(izbor=='\n')
        {
            otkrij(x,y);   
        }
        else
        {
            if(bp>0)
            {
                b[x][y]=-3;
                bp--;
            }
            else
                printf("Iskoristili ste sve mine!\n");
        }
        }
        else
        {
            postavi_zastavice(x,y);
            raskopaj_oko(x,y);
            //printf("Polje je vec otvoreno\n");
        }
        ispis(b);
    }
    printf("Resili ste igru!\n");
    ispis(a);
    return 0;
}