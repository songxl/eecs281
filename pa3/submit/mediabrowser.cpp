///July 9th 13:32 Katherine
///July 18th 21:00 Katherine

#include <string>
#include <iostream>
#include "p3.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int PageSize = 50;
int main(int argc, char* argv[]){
    int medianum;
    string op[argc];
    char opt;
    char sortkey1; ///sortkey read in first
    char sortkey2; ///sortkey read in second
    for( int g = 0; g < argc; g++){
        op[g] = argv[g];
    }

    Dict mediadict(PageSize);
    ///input
    string temp;
    cin >> temp;
    while (cin.good()){
        mediadict.insert(temp);
        cin >> temp;
    }

    medianum = mediadict.getlength();
    MediaInfo *(*medialist) = new MediaInfo*[medianum];
    ///database
    for(int i = 0; i < medianum; i++){
        int pageindex = i / PageSize;
        int page_offset = i % PageSize;

        if (page_offset == 0 && pageindex !=0){
            mediadict.MediaTable = mediadict.MediaTable->next;
        }
        medialist[i] = &(mediadict.MediaTable->media[page_offset]);
    }


    ///sort by title

    if (op[1].length() == 2){
        sortkey1 = op[1][1];
        sortkey2 = 'x';
        mergesort(sortkey1, medialist, 0, medianum - 1);
    }
    else if(op[1].length() == 3){
        sortkey1 = op[1][1]; //second sort
        sortkey2 = op[1][2];// first sort
        qsort(sortkey2, medialist, 0, medianum - 1);
        mergesort(sortkey1, medialist, 0, medianum - 1);
    }
    PrintMedia(medialist, medianum, sortkey1, sortkey2);

    delete[] medialist;
    return 1;
};
