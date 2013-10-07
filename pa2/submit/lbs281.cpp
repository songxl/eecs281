///June 23rd 22:31 to 23:00 Katherine
///June 24th 22:00 to 23:00 Katherine
///June 25th 14:15 to 19:20 Katherine
///June 25th 20:00 to 21:00 Katherine
///June 26th 1:00 to 3:00 Katherine
///June 26th 13:00 to 14:30 Katherine
///June 27th 9:00 to 12:00 Katherine
#include <string>
#include <iostream>
#include "p2.h"
#include <stdio.h>

using namespace std;
int HASH_SIZE = 4093;
int TREE_DIMENSION = 2;

int main()
{
    Hash HashTable(HASH_SIZE);
    Kdtree KD_Tree(TREE_DIMENSION); //stands for the dimentional tree
    char fir[40],longi[40], name[40], tag[40], clat[40], clon[40], cradius[40];
    int trash;
    string Firstch;
    trash = scanf("%s", fir);
    Firstch = fir;
    while(cin.good()&& Firstch!= "@" && Firstch != "r")
    {
        Location *currentplace = new Location;
        currentplace->latitude = Firstch;
        trash = scanf("%s", longi);
        trash = scanf("%s", name);
        trash = scanf("%s", tag);
        trash = scanf("%s", fir);
        currentplace->longitude = longi;
        currentplace->name = name;
        currentplace->tag = tag;
        Firstch = fir;
        HashTable.inserthash(currentplace);
        KD_Tree.SetUpTree(currentplace);
    }
    while (cin.good())
    {
        string lat, lon, radius;
        if (Firstch == "@")
        {
            trash = scanf("%s", clat);
            trash = scanf("%s", clon);
            lat = clat;
            lon = clon;
            HashTable.MatchHash(lat, lon);
        }
        else if (Firstch == "r")
        {
            trash = scanf("%s", clat);
            trash = scanf("%s", clon);
            trash = scanf("%s", cradius);
            lat = clat;
            lon = clon;
            radius = cradius;
            KD_Tree.SearchTree(lat, lon, radius);
        }
        if(cin.good())
        {
            cin>>Firstch;
        }

    }
    return 1;
}
