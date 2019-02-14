#include <stdio.h>
#include <stdlib.h>

char** resize(int arg1, int* height, int* width, char** img);
char** rotate(int* height, int* width, int angle, char** img);
void flip(int height, int width, int flag, char** img);
char* copy(int x1, int y1, int c_h, int c_w, int height, int width, char** img);
void paste(int x2, int y2, int height, int width, char** img, char* temp);
void fill(int x, int y, char color, int height, int width, char** img);
void print_img(char** img,int height, int width);
int scan_img(char** img, int height, int width);
void numberquery(char** img, int height, int width, int numquery);
char** temp_img(int height, int width, char** img);
char** rotate_img(int height, int width, char** img);
int check_fill(int x, int y, int loop, int** que);

int main()
{
    int testcase, height, width, query,i,j,k;
    int numquery;
    char** img;
    printf("Input testcase : ");
    scanf("%d",&testcase);
    for(i=0;i<testcase;i++)
    {
        printf("Input height, width : ");
        scanf("%d %d",&height,&width);
        if(height>4096 || width>4096)
            printf("Size Error : Your image is too big!!\n");
        else
        {
            img=(char**)malloc(height * sizeof(char*));
            for(j=0;j<height;j++)
            {
                img[j]=(char*)malloc(width * sizeof(char));
            }
            printf("Input the image : \n");
            k=scan_img(img, height, width);
            if(k==0)
                continue;
            printf("Input number of query : ");
            scanf("%d",&numquery);
            numberquery(img, height, width, numquery);
        }
    }
}

int scan_img(char** img, int height, int width)
{
    int i,j;
    char temp;
    int check=0;
    j=0;
    scanf("%c",&temp);
    for(i=0;i<height;i++)
    {
        while(1)
        {
            scanf("%1c",&temp);
            if(temp=='\n' && j!=width)
            {
                printf("Size error : Your image is wrong!!\n");
                check++;
                break;
            }
            if(temp=='\n' && j==width)
                break;
            else 
            {
                img[i][j]=temp;
                j++;
            }
        }
        if(check!=0)
            break;
        else
            j=0;
    }
    if(check!=0)
        return 0;
    else return 1;
}
void print_img(char** img,int height, int width)
{
    int i,j;
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            printf("%c",img[i][j]);
        }
        printf("\n");
    }
}

char** temp_img(int height, int width, char** img)
{
    char** temp;
    int i,j;
    temp=(char**)malloc(height * sizeof(char*));
    for(i=0;i<height;i++)
        temp[i]=(char*)malloc(width * sizeof(char));
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            temp[i][j]=img[i][j];
        }
    }
    return temp;
}

void numberquery(char** img, int height, int width, int numquery)
{
    int i,query;
    char* temp;
    for(i=0;i<numquery;i++)
    {
        printf("Input query : ");
        scanf("%d",&query);
        switch(query)
        {
            case 1 : img=resize(0,&height,&width,img);
                     print_img(img,height,width);
                     break;
            case 2 : img=rotate(&height,&width,0,img);
                     print_img(img,height,width);
                     break;
            case 3 : flip(height,width,0,img);
                     print_img(img,height,width);
                     break;
            case 4 : temp=copy(0,0,0,0,height,width,img);
                     if(temp!='\0')
                         paste(0,0,height,width,img,temp);
                     print_img(img,height,width);
                     break;
            case 5 : fill(0,0,0,height,width,img);
                     print_img(img,height,width);
                     break;
            default : printf("Error : Your command is wrong\n");
                      break;
        }
    }
    for(i=0;i<height;i++)
        free(img[i]);
    free(img);
}

char** resize(int arg1, int* height, int* width, char** img)
{
    int i,j;
    char** temp;

    printf("\nResize\n");
    printf("Input 0 or 1 : ");
    scanf("%d",&arg1);
    if(arg1==0)
    {
        if(*height * 2 >4096 || *width * 2 >4096)
            printf("Size Error : Your image is too big to resize!!");
        else
        {
            temp=temp_img(*height,*width,img);
            *height=*height * 2;
            *width = *width * 2;
            img=(char**)malloc(*height * sizeof(char*));
            for(i=0;i<*height;i++)
                img[i]=(char*)malloc(*width * sizeof(char));
            printf("Result, resize height : %d, width : %d\n",*height,*width);
            printf("Result Image\n\n");
            for(i=0;i<*height/2;i++)
            {
                for(j=0;j<*width/2;j++)
                {
                    img[i*2][j*2]=temp[i][j];
                    img[i*2+1][j*2]=temp[i][j];
                    img[i*2][j*2+1]=temp[i][j];
                    img[i*2+1][j*2+1]=temp[i][j];
                }
            }
        }
    }
    else if(arg1==1)
    {
        if(*height/2 <1 || *width/2 <1)
            printf("Size Error : Your image is too small to resize!!");
        else
        {
            temp=temp_img(*height,*width,img);
            *height=*height/2;
            *width=*width/2;
            img=(char**)malloc(*height * sizeof(char*));
            for(i=0;i<*height;i++)
                img[i]=(char*)malloc(*width * sizeof(char));
            printf("Result, resize height : %d, width : %d\n",*height,*width);
            printf("Result Image\n\n");
            for(i=0;i<*height;i++)
            {
                for(j=0;j<*width;j++)
                {
                    img[i][j]=(char)(((int)(temp[i*2][j*2]+temp[i*2+1][j*2]
                                    +temp[i*2][j*2+1]+temp[i*2+1][j*2+1]))/4);
                }
            }
        }
    }
    else
        printf("Error : Your command is wrong!!\n");
    return img;
}

char** rotate_img(int height, int width, char** img)
{
    int i;
    img=(char**)realloc(img,width * sizeof(char*));
    for(i=0;i<width;i++)
        img[i]=(char*)realloc(img[i],height * sizeof(char));
    return img;
}
    

char** rotate(int* height, int* width, int angle, char** img)
{
    int i,j;
    char** temp;
    int temp_height;
    printf("\nRotate\n");
    printf("Input 0 or 1 or 2 : ");
    scanf("%d",&angle);
    if(angle==0)
    {
        temp=temp_img(*height, *width, img);
        img=rotate_img(*height, *width, img);
        for(i=0;i<*height;i++)
        {
            for(j=0;j<*width;j++)
            {
                img[j][*height-1-i]=temp[i][j];
            }
        }
        temp_height=*height;
        *height=*width;
        *width=temp_height;
        printf("Result_rotate height : %d width : %d\n",*height,*width);
        printf("Result Image\n\n");
    }
    else if(angle==1)
    {
        temp=temp_img(*height, *width, img);
        for(i=0;i<*height;i++)
        {
            for(j=0;j<*width;j++)
            {
                img[*height-1-i][*width-1-j]=temp[i][j];
            }
        }
        printf("Result_rotate height : %d, width : %d\n",*height,*width);
        printf("Result Image\n\n");
    }
    else if(angle==2)
    {
        temp=temp_img(*height, *width, img);
        img=rotate_img(*height, *width, img);

        for(i=0;i<*height;i++)
        {
            for(j=0;j<*width;j++)
            {
                img[*width-1-j][i]=temp[i][j];
            }
        }
        temp_height=*height;
        *height=*width;
        *width=temp_height;
        printf("Result_rotate height : %d, width : %d\n",*height,*width);
        printf("Result Image\n\n");
    }
    else
        printf("Error : Your command is wrong!!\n");
    return img;
    
}

void flip(int height, int width, int flag, char** img)
{
    int i,j;
    char** temp;
    printf("\nFlip\nInput 0 or 1 : ");
    scanf("%d",&flag);
    if(flag==0)
    {
        temp=temp_img(height,width,img);
        for(i=0;i<height;i++)
            for(j=0;j<width;j++)
                img[height-1-i][j]=temp[i][j];
        printf("Result Image\n\n");
    }
    else if(flag==1)
    {
        temp=temp_img(height,width,img);
        for(i=0;i<height;i++)
            for(j=0;j<width;j++)
                img[i][width-1-j]=temp[i][j];
        printf("Result Image\n\n");
    }
    else
        printf("Error : Your command is wrong!!\n");
}

char* copy(int x1, int y1, int c_h, int c_w, int height, int width, char** img)
{
    int x2, y2,i,j;
    int t=4;
    char* temp;
    printf("\nCopy and Paste\n");
    printf("x1, y1, c_h, c_w, x2, y2 : ");
    scanf("%d %d %d %d %d %d",&x1,&y1,&c_h,&c_w,&x2,&y2);
    
    if(c_h<1 || c_w<1)
    {
        printf("Error : Copy area is too small!!\n");
        return '\0';
    }
    else if(x1>=height || y1>=width || x1<0 || y1<0)
    {
        printf("Error : Your coordinates are out of image!!\n");
        return '\0';
    }
    else 
    {
        if(y1+c_h>=height)
            c_h=height-y1-1;
        else if(x1+c_w>=width)
            c_w=width-x1-1;
        temp=(char*)malloc((c_h*c_w+4+c_h)*sizeof(char));
        temp[0]=x2;
        temp[1]=y2;
        temp[2]=c_h;
        temp[3]=c_w;
        for(i=y1;i<y1+c_h;i++)
        {
            for(j=x1;j<x1+c_w;j++)
            {
                temp[t]=img[i][j];
                t++;
            }
            temp[t]='\n';
            t++;
        }
        temp[t]='\0';
        return temp;
    }
}

void paste(int x2, int y2, int height, int width, char**img, char* temp)
{
    int t=4;
    int c_h,c_w;
    int i,j,k,l;
    char** cimg;
    x2=temp[0];
    y2=temp[1];
    c_h=temp[2];
    c_w=temp[3];
    cimg=(char**)malloc(c_h*sizeof(char*));
    for(i=0;i<c_h;i++)
        cimg[i]=(char*)malloc(c_w*sizeof(char));
    j=0;
    for(i=0;i<c_h;i++)
    {
        while(1)
        {
            if(temp[t]=='\n')
            {
                t++;
                j=0;
                break;
            }
            else
            {
                cimg[i][j]=temp[t];
                t++;
                j++;
            }
        }
    }
    k=0;
    l=0;
    if(c_h+y2>height)
        c_h=height-y2;
    if(c_w+x2>width)
        c_w=width-x2;
    for(i=y2;i<c_h+y2;i++)
    {
        for(j=x2;j<c_w+x2;j++)
        {
            img[i][j]=cimg[k][l];
            l++;
        }
        l=0;
        k++;
    }
    
    printf("Result image\n\n");
}

void fill(int x, int y, char color, int height, int width, char** img)
{
    int flag=0;
    int current=0;
    int i,check;
    int** que=(int**)malloc(height*width*sizeof(int*));
    for(i=0;i<(height*width);i++)
        que[i]=(int*)malloc(2*sizeof(int));
    printf("\nFill\n");
    printf("Input y, x, color : ");
    scanf("%d %d %1c",&y,&x,&color);
    if(y<0 || x<0 || y>=height || x>=width)
        printf("Error : Your coordinates are out of image!!\n");
    else if(img[y][x]==color)
        printf("Number of colored pixels = 0\n");
    else
    {
    que[0][0]=y;
    que[0][1]=x;
    i=1;
    while(1)
    {
        if(y+1<height)
           if(img[y+1][x]==img[y][x])
            {
                check=check_fill(x,y+1,height*width,que);
                if(check==0)
                {
                    que[i][0]=y+1;
                    que[i][1]=x;
                    i++;
                }
            }
        if(x+1<width)
            if(img[y][x+1]==img[y][x])
            {
                check=check_fill(x+1,y,height*width,que);
                if(check==0)
                {
                que[i][0]=y;
                que[i][1]=x+1;
                i++;
                }
            }
        if(y>0)
            if(img[y-1][x]==img[y][x])
            {
                check=check_fill(x,y-1,height*width,que);
                if(check==0)
                {
                que[i][0]=y-1;
                que[i][1]=x;
                i++;
                }
            }
        if(x>0)
            if(img[y][x-1]==img[y][x])
            {
                check=check_fill(x-1,y,height*width,que);
                if(check==0)
                {
                que[i][0]=y;
                que[i][1]=x-1;
                i++;
                }
            }
        flag=i;
        img[y][x]=color;
        current++;
        if(flag==current)
            break;
        else
        {
            y=que[current][0];
            x=que[current][1];
        }
    }
    printf("Number of colored pixels = %d\n",flag);
    printf("Result Image\n\n");
    }
}      

int check_fill(int x, int y, int loop, int** que)
{
    int i;
    int check=0;
    for(i=0;i<loop;i++)
        if(que[i][0]==y && que[i][1]==x)
            check++;
    if(check==0)
        return 0;
    else return 1;
}


            
