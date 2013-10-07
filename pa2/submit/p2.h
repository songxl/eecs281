///June 23rd 15:20 to 15:55 Katherine
///June 23rd 21:00 to 22:31 Katherine
///June 24th 12:00 to 15:30 Katherine
///June 24th 21:00 to 23:00 Katherine
///June 25th 14:15 to 19:20 Katherine
///June 25th 20:00 to 21:00 Katherine
///June 26th 1:00 to 3:00 Katherine
///June 26th 13:00 to 14:30 Katherine
///June 26th 19:00 to 21:00 Katherine
///June 27th 9:00 to 12:00 Katherine

#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct Location
{
    string latitude;
    string longitude;
    string name;
    string tag;

};

void Print_Loc(Location *targetloc)
{
    printf("%s ", targetloc->latitude.c_str());
    printf("%s ", targetloc->longitude.c_str());
    printf("%s ", targetloc->name.c_str());
    printf("%s\n", targetloc->tag.c_str());

};

class Hash
{

    public:
    Hash()
    {    };
    Hash(int size)
    {
        TableSize = size;
        TheTable = new node[TableSize];
        for (int i = 0; i < TableSize; i++)
        {
            TheTable[i].loc = NULL;
            TheTable[i].next = NULL;
        }
    };

    ~Hash()
    {

    };

    unsigned int getHashKey(string s) //get the hash key for the longitude&latitude s
    {
        unsigned int hashnum = 0;
        for (int i = 0; i < s.length(); i++)
        {
            int a = int(s.at(i));
            hashnum = 33*hashnum + a;
        }
        int key = hashnum % TableSize;
        return key;
    };

    void inserthash(Location *currentplace) //put the locations into the hash table||prepare for the searching
    {

        string currentloc = currentplace->latitude + currentplace->longitude;
        unsigned int Key = getHashKey(currentloc); //compute the key
        node *Hashtarget;
        Hashtarget = &TheTable[Key];

        while (Hashtarget->next != NULL)
        {
            Hashtarget = Hashtarget->next;
        }//go to the end of the linked-list
        if (Hashtarget->loc !=NULL)//the last node in this slot is not the first one
        {
            Hashtarget->next = new node;
            Hashtarget = Hashtarget->next;
        }
        //the last node is the first in this slot
            Hashtarget->loc = currentplace;
            Hashtarget-> next = NULL;
    };


    void MatchHash(string lat, string longi)
    {
        string placeloc = lat + longi;
        int TargetKey = getHashKey(placeloc);
        int Target_found = 0;
        node *targetslot = &TheTable[TargetKey];
        do
        {
            if(targetslot->loc!=NULL)
            {
                if((targetslot->loc->latitude == lat) && (targetslot->loc->longitude == longi))
                {
                    Target_found = 1;
                    Print_Loc(targetslot->loc);
                }
                targetslot = targetslot->next;
            }
            else
            {
                break;
            }
        }
        while( targetslot!= NULL);
        if (Target_found == 0)
        {
            cout<<"No record found"<<endl;
        }
    };

    private:

    struct node
    {
        Location *loc;
        node *next;
    };

    node *TheTable;
    int TableSize;//the hash table size
};


class Kdtree
{
    public:
    struct Kdleaf
    {
        Location *loc;
        Kdleaf *leftchild;
        Kdleaf *rightchild;
        double floc[2]; //the location information(in float)
    };

    Kdtree(int d)
    {
        dim = d;
        TheTree = NULL;
    };

    ~Kdtree()
    {   };

    double ConverttoFloat(string s)
    {
        return atof(const_cast<const char*>(s.c_str()));
    };

    void insertKdtree(Kdleaf * & root, Location *newloc, double fnewloc[], int disc)
    {

        if (root == NULL) //A root has never been assigned
        {
            root = new Kdleaf;
            root->loc = newloc;
            root->floc[0] = fnewloc[0];
            root->floc[1] = fnewloc[1]; // assign the newlocation information to the root
            root->leftchild = NULL; // initialize the children
            root->rightchild = NULL;
            return;
        }

        if (fnewloc[disc] <= root->floc[disc] ) // a root which is not a leaf
        {
            insertKdtree(root->leftchild, newloc, fnewloc, (disc+1)%dim); //go to the left child
        }
        else if( fnewloc[disc] > root->floc[disc] )
        {
            insertKdtree(root->rightchild, newloc, fnewloc, (disc+1)%dim); // go to the right child
        }

    };

    void SetUpTree(Location *newloc)
    {
        double fnewloc[2];
        fnewloc[0] = ConverttoFloat(newloc->latitude);
        fnewloc[1] = ConverttoFloat(newloc->longitude); //set up the new location information
        insertKdtree(TheTree, newloc, fnewloc, 0);
    };

    void SearchTree(string lat, string longi, string radius)
    {
        int TreeFlag = 0;        //indicate whether we found a record or not
        double f_lat, f_longi, f_radius;

        f_lat = ConverttoFloat(lat);
        f_longi = ConverttoFloat(longi);
        f_radius = ConverttoFloat(radius);
        double Rangemin[2] = {f_lat - f_radius,f_longi - f_radius};
        double Rangemax[2] = {f_lat + f_radius,f_longi + f_radius};

        search_helper(TheTree, 0, TreeFlag, Rangemin, Rangemax); ///recursive search down the tree
        if (TreeFlag == 0)
        {
            cout<<"No record found"<<endl;
        }

    };

    void search_helper(Kdleaf * & root, int disc, int &TreeFlag, double min[], double max[])
    {
        if (root == NULL) // come to the leaf
        {
            return;
        }

        if (root->floc[disc] < min[disc])
        {
            search_helper(root->rightchild, (disc+1) % dim, TreeFlag, min, max);
        }
        else if (root->floc[disc] > max[disc])
        {
            search_helper(root->leftchild, (disc+1) % dim, TreeFlag, min, max);
        }
        else //rootlat >= minlat && rootlat <= maxlat
        {
            if ((root->floc[(disc+1) % dim] >= min[(disc+1) % dim]) && (root->floc[(disc+1) % dim] <= max[(disc+1) % dim]))
            {
                TreeFlag = 1;
                Print_Loc(root->loc);
            }
            search_helper(root->rightchild, (disc+1) % dim, TreeFlag, min, max);
            search_helper(root->leftchild, (disc+1) % dim, TreeFlag, min, max);

        }

    };

    private:
    Kdleaf *TheTree;
    int dim;

};
