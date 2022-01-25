#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match(char* wzorzec, char* lancuch)
{
    int lenWzorzec = strlen(wzorzec);
    int lenLancuch = strlen(lancuch);

    if(lenWzorzec==0&&lenLancuch!=0)
        return false;

    for(int i=0; i<lenWzorzec; i++)
    {
        if(wzorzec[i]=='*')
        {
            if(wzorzec[i+1]=='\0')
                return true;
            else
            {
                int j;
                for(j=i; j<lenLancuch; j++)
                {
                    if(lancuch[j]==wzorzec[i+1])
                    {
                        if(match(wzorzec+i+1, lancuch+j))
                            return true;
                    }
                }
                if(j==lenLancuch)
                {
                    return false;
                }
            }
        }
        else if((wzorzec[i]!='?'&&wzorzec[i]!=lancuch[i])||lancuch[i]=='\0')
        {
            return false;
        }

        if(i==lenWzorzec-1&&lancuch[lenWzorzec]!='\0')
            return false;
    }
    return true;
}

int main()
{
    char wzorzec[101];
    char lancuch[101];
    printf("Podaj wzorzec i lancuch\n");
    scanf("%s", wzorzec);
    scanf("%s", lancuch);

    if(match(wzorzec, lancuch)==true)
        printf("Lancuchy sie zgadzaja\n");
    else
        printf("Lancuchy sie NIE zgadzaja\n");


    return 0;
}
