#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void fill(int Tab[1296][5])
{
    int i=0;
    for(int a=1; a<=6; a++)
    {
        for(int b=1; b<=6; b++)
        {
            for(int c=1; c<=6; c++)
            {
                for(int d=1; d<=6; d++)
                {
                    Tab[i][0]=1;
                    Tab[i][1]=a;
                    Tab[i][2]=b;
                    Tab[i][3]=c;
                    Tab[i][4]=d;
                    i++;
                }
            }
        }
    }
}

void fillAns(int Ans[14][2])
{
    int red, white, i=0;
    for(red=0; red<4; red++)
    {
        white=0;
        while(red+white<=4)
        {
            Ans[i][0]=red;
            Ans[i][1]=white;
            white++;
            i++;
        }
    }
}

void compare(int Tmp[8], int *red, int *white)
{
    for(int i=0; i<4; i++)
    {
        if(Tmp[i]==Tmp[i+4])
        {
            Tmp[i]=0;
            Tmp[i+4]=0;
            *red+=1;
        }
    }
    for(int i=4; i<8; i++)
    {
        if(Tmp[i]!=0)
        {
            for(int j=0; j<4; j++)
            {
                if(Tmp[i]==Tmp[j])
                {
                    Tmp[i]=0;
                    Tmp[j]=0;
                    *white+=1;
                    break;
                }
            }
        }
    }
}

int checkMax(int Tab[1296][5], int Ans[14][2])
{
    int max=0, number, curr, min, red, white;
    for(int i=0; i<1296; i++)
    {
        if(Tab[i][0]==1)
        {
            min = 1296;
            for(int j=0; j<14; j++)
            {
                number = 0;
                for(int k=0; k<1296; k++)
                {
                    if(Tab[k][0]==1)
                    {
                        int Tmp[8] = {Tab[k][1], Tab[k][2], Tab[k][3], Tab[k][4], Tab[i][1], Tab[i][2], Tab[i][3], Tab[i][4]};
                        compare(Tmp, &red, &white);
                        if(red!=Ans[j][0]||white!=Ans[j][1])
                            number++;
                    }
                }
                if(number<min)
                    min = number;
            }
            if(min>max)
            {
                max=min;
                curr=i;
            }
        }
    }

    return curr;
}

void eliminate(int Tab[1296][5], int a, int b, int c, int d, int red, int white)
{
    for(int i=0; i<1296; i++)
    {
        if(Tab[i][0]==1)
        {
            int Tmp[8] = { Tab[i][1], Tab[i][2], Tab[i][3], Tab[i][4], a, b, c, d };
            int red_1=0, white_1=0;
            compare(Tmp, &red_1, &white_1);
            if(red_1!=red||white_1!=white)
            {
                Tab[i][0]=0;
            }
        }
    }
}

int count(int Tab[1296][5])
{
    int sum=0;
    for(int i=0; i<1296; i++)
    {
        sum+=Tab[i][0];
    }
    return sum;
}


int main()
{
    //deklaracje tablic
    int Tab[1296][5];
    int Ans[14][2];
    //wype³nienie tablic
    fill(Tab);
    fillAns(Ans);
    //deklaracja zmiennych
    int i=0, red, white;
    //pocz¹tek pêtli
    while(true)
    {
        //interakcja z u¿ytkownikiem
        printf("[%d] [%d] [%d] [%d]?\n", Tab[i][1], Tab[i][2], Tab[i][3], Tab[i][4]);
        printf("  red: ");
        scanf("%d", &red);
        printf("white: ");
        scanf("%d", &white);
        //warunki
        assert(red>=0&&red<=4);
        assert(white>=0&&white<=4);
        assert(red+white<=4);
        //dalsze dzia³anie
        if(red==4)
        {
            printf("I win\n");
            return 0;
        }
        else eliminate(Tab, Tab[i][1], Tab[i][2], Tab[i][3], Tab[i][4], red, white);
        printf("%d possibilities remaining\n", count(Tab));
        //sprawdzenie czy u¿ytkownik nie oszukuje
        if(count(Tab)==0)
        {
            printf("you are cheating!\n");
            return 0;
        }
        //przygotowanie nastêpnego optymalnego pytania
        i=checkMax(Tab, Ans);
    }
}
