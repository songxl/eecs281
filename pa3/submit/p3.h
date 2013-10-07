///July 9th 13:32 Katherine
///July 14th 16:00 Katherine
///July 16th 14:00 Katherine
///July 18th 21:00 Katherine

#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

using namespace std;


struct MediaInfo{
    char title[40];
    char genre[40];
    int popularity;
};

class Dict{
    private:
    struct node{
        MediaInfo *media;
        node *next;
    };
    node *tail;
    int obj_number;
    int PAGE_SIZE;
    int mediaindex;

    public:
    node *MediaTable;
    Dict(int ps){
        PAGE_SIZE = ps;
        MediaTable = NULL;
        obj_number = 0;
    };

    ~Dict(){
        while ( MediaTable!= NULL){
        
            node *temp = MediaTable;
            MediaTable = MediaTable->next;
            delete[] temp->media;
            delete temp;
        }
    };

    int getlength(){
        return obj_number;
    };

    void insert(string first)
    {

        if (obj_number == 0){
            MediaTable = new node;
            MediaTable->media = new MediaInfo[PAGE_SIZE];  //set up the Dict
            mediaindex = 0;
            MediaTable->next = NULL;
            tail = MediaTable;
        }
        if (mediaindex >= PAGE_SIZE){ //add an array
            tail->next = new node;
            tail = tail->next;
            tail->media = new MediaInfo[PAGE_SIZE];
            mediaindex = 0;
            tail->next = NULL;
        }
        int collect;
        strcpy(tail->media[mediaindex].title, first.c_str());
        collect = scanf("%s",tail->media[mediaindex].genre);
        collect = scanf("%i",&tail->media[mediaindex].popularity);
        obj_number ++;
        mediaindex ++;
        return;
    };
};
