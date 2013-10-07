/////////////// 31/05/2011 14:24:18 Katherine
/////////////// 03/06/2011 16:54:59 Katherine
/////////////// 03/06/2011 21:46:13 Katherine
/////////////// 04/06/2011 19:35:55 Katherine
/////////////// 08/06/2011 10:42:43 Katherine
/////////////// 08/06/2011 12:03
#include <string>
#include <iostream>
#include "p1.h"
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int map_reader(int sizen, int leveln, Tile grid[]);
char discard(char commentjudge);
bool Next_tile(Tile *t,Tile *nexttile,Tile grid[],int sizen, int leveln, int dir, int *found,int *UorD);
void Add_tile(Tile *item);
Tile *prevTile(Tile grid[],Tile t,int sizen);
void Map_Printer(Tile grid[],int leveln,int sizen);
int found = 0;
int UorD = 0;

int map_reader(int sizen, int leveln, Tile grid[])
{
    char comment;
    cin.get(comment);
    for (int l = 0; l < leveln; l++)
    {
        for (int rr = 0; rr < sizen; rr++)
        {
            int objectindex;
            for(int c = 0; c< sizen;c++)
            {
                objectindex = l*sizen*sizen+rr*sizen+c; //setup current object tile index

                if (!cin.get(comment)) //reach the end of map
                {
                    cerr<<"ILLEGAL INPUT FILE, PLEASE CHECK"<<endl;
                    exit(1);
                }
                else
                {
                    while((c == 0) && (comment == '\n'||comment == '#')) //comment lines
                    {
                        if(comment == '#')
                        {
                            while(cin.get(comment)!=0 && comment!='\n'){}
                            cin.get(comment);
                        }
                        else
                        {
                            cin.get(comment);
                        }
                    }
                        if ((c != 0)&& (comment == '\n')) //blank lines
                        {
                            cerr<<"ILLEGAL INPUT FILE, PLEASE CHECK"<<endl; exit(1);
                        }
                    grid[objectindex].type = comment;
                }

            }
            while(cin.get(comment)!=0 && comment!='\n'){} //destroy the extra characters after each line
        }
    }
    return 0;
};

bool Next_tile(Tile *t,Tile *nexttile,Tile grid[],int sizen, int leveln, int dir, int *found,int *UorD)
{
    int northi = t->index - sizen;
    int southi = t->index + sizen;
    int easti = t->index + 1;
    int westi = t->index - 1;
    int upi = t->index + sizen*sizen;
    int downi = t->index - sizen*sizen;

    switch(t->type)
    {
        case '<':
        {
            if(!grid[downi].taken){
            t->taken = 1;
            grid[downi].direction = 'z';
            grid[downi].taken = 1;
            *nexttile = grid[downi];
            *UorD = 1;
            return 1;}
            else {return 0;}

        }
        case '>':
        {
            if(!grid[upi].taken){
            t->taken = 1;
            grid[upi].direction = 'y';
            grid[upi].taken = 1;
            *nexttile = grid[upi];
            *UorD = 1;
            return 1;
            }
            else {return 0;}

        }
        case 'X':
        {
            *found = 1;
            return 0;
        }
        default:
        ////////////////////
        {
            switch(dir)
            {
                case 1://go to the north
                {
                    if ( northi > 0 ){
                    if ((t->index % (sizen*sizen) < sizen )||(grid[northi].type == 'W')||grid[northi].taken)
                    {
                        return false; //the first row of one level
                    }
                    else
                    {
                        grid[northi].direction = 'b';
                        grid[northi].taken = 1;
                        *nexttile = grid[northi];
                    }
                    break;
                    }
                    else {return false;}
                }
                case 2://go to the east
                {
                    if(easti < sizen*sizen*leveln) {
                    if ((easti % sizen == 0 )||(grid[easti].type == 'W')||grid[easti].taken)
                    {
                        return false; //the first row of one level
                    }
                    else
                    {
                        grid[easti].direction = 'd';
                        grid[easti].taken = 1;
                        *nexttile = grid[easti];
                    }
                    break;
                    }
                    else {return false;}
                }
                case 3://go to the south
                {
                    if(southi < sizen*sizen*leveln){
                    if ((southi % (sizen*sizen) < sizen )||(grid[southi].type == 'W')||grid[southi].taken)
                    {
                        return false; //the first row of one level
                    }
                    else
                    {
                        grid[southi].direction = 'n';
                        grid[southi].taken = 1;
                        *nexttile = grid[southi];
                    }
                    break;
                    }
                    else { return false;}
                }

                case 4://go to the west
                {
                    if ( westi > 0)
                    {
                        if ((t->index % sizen == 0 )||(grid[westi].type == 'W')||grid[westi].taken)
                        {
                            return false; //the first row of one level
                        }
                        else
                        {
                            grid[westi].direction = 'x';
                            grid[westi].taken = 1;
                            *nexttile = grid[westi];
                        }
                        break;
                    }
                    else {return false;}
                }
                default:
                break;
            }
            break;

        }
    }
    return 1;
}

Tile *prevTile(Tile grid[],Tile *t,int sizen)
{
    int indexoffset;

    switch (t->direction){
        case 'b':
        indexoffset = sizen;
        break;
        case 'd':
        indexoffset = -1;
        break;
        case 'x':
        indexoffset = 1;
        break;
        case 'n':
        indexoffset = -1*sizen;
        break;
        case 'z':
        indexoffset = sizen*sizen;
        break;
        case 'y':
        indexoffset = -1*sizen*sizen;
        break;
        default: break;
    }
    grid[t->index + indexoffset].type = t->direction;
    return &grid[t->index + indexoffset];
}

void Map_Printer(Tile grid[],int leveln,int sizen)
{
    Tile *TheWorld[leveln][sizen];
    cout<<sizen<<endl;
    cout<<leveln<<endl;
    for (int i =0;i<leveln;i++)
    {
        cout<<"#level "<<i+1<<"\n";
        for(int j =0;j<sizen;j++)
        {
            TheWorld[i][j] = &grid[i*sizen*sizen+j*sizen];
            for(int k =0;k<sizen;k++)
            {
                cout<<TheWorld[i][j][k].type;
            }
            cout<<"\n";
        }
    }
}

int main(int argc, char *argv[])
{
    Tile *NextStepTile,*currentTile;
	int SIZE_NUM, LEVEL_NUM, WORLD_SIZE;
	cin >> SIZE_NUM;
	cin >> LEVEL_NUM;
	WORLD_SIZE = SIZE_NUM * SIZE_NUM * LEVEL_NUM;
	Tile *TheGrid = (Tile*) malloc(sizeof (Tile)* (SIZE_NUM*SIZE_NUM*LEVEL_NUM)); //set up the map
    char opt;
    string op[argc];
    for (int g = 0; g < argc; g++)
    {
        op[g] = argv[g];
    } //get the opt
    int counts = 0;
    int countq = 0;
    for (int i = 0; i< argc;i++)
    {
        if (op[i] == "-s")
        {
            counts ++;
        }
        if (op[i] == "-q")
        {
            countq ++;
        }
    }
    if ((counts == 1) && !countq)
    {
        opt = 's';
    }
    else if ((countq == 1) && !counts)
    {
        opt = 'q';
    }
    else //more or less than one "s" or "q"
    {
        cerr<<"YOU HAVE WRONG COMMAND!"<<endl;
        exit(1);
    }

    map_reader(SIZE_NUM,LEVEL_NUM,TheGrid); //read the map

    ////////////FIND THE ROUT/////////////////////////////

    Queue TheQRout(WORLD_SIZE);
    Stack TheSRout;
    int StartIndex;
    for(int i = 0; i < WORLD_SIZE; i ++)
    {
        TheGrid[i].index = i;
        TheGrid[i].taken = 0;
        TheGrid[i].direction = ' ';
        if (TheGrid[i].type == 'I')
        {   StartIndex = i; NextStepTile = &TheGrid[i];}
    }
    //set up the grid
    switch(opt)
    {
        case 'q':
        TheQRout.enqueue(TheGrid[StartIndex]);//initialize Queue;
        break;
        case 's':
        TheSRout.push(TheGrid[StartIndex]);//initialize Stack;
        break;
    }
    while ((!(TheQRout.isEmpty()) || !(TheSRout.isEmpty())) && !found)
    {
        if (opt == 'q')
        {
            currentTile = TheQRout.dequeue();
            }
        else if(opt == 's')
        {
            currentTile = TheSRout.pop();
            }
        for(int i = 1; i <5; i++)//keep doing 4 directions navigation
        {
            if (Next_tile(currentTile,NextStepTile,TheGrid,SIZE_NUM,LEVEL_NUM,i,&found,&UorD))
            {
                if (opt == 'q')
                {
                    TheQRout.enqueue(*NextStepTile);
                }

                else if(opt == 's')
                {
                    TheSRout.push(*NextStepTile);
                }

                if (UorD) //going up or down
                {
                    UorD = 0; break;
                }
            }
            if (found){ break;}
        }
    }
    if(found)
    {
        while ( currentTile != &TheGrid[StartIndex])
        {
            currentTile = prevTile(TheGrid,currentTile,SIZE_NUM);
        }
        Map_Printer(TheGrid,LEVEL_NUM,SIZE_NUM);
    }
    else
    {
        TheGrid[StartIndex].type = 'I';
        Map_Printer(TheGrid,LEVEL_NUM,SIZE_NUM);
        cerr<<"NO ROUT FOUND!!!"<<endl;
        exit(1);
    }

    ////////////FIND THE ROUT/////////////////////////////

	return 0;
}
