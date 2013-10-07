///July 15th 12:33 Katherine
///July 17th 1:00 Katherine
///July 17th 17:00 Katherine
///July 18th 21:00 Katherine
#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>

int partition(char sortkey, MediaInfo *ThisList[], int lindex, int rindex);
void qsort(char sortkey, MediaInfo *ThisList[], int lindex, int rindex);
template <typename T>
void swapPt(T * & a, T * & b);
void merge(char sortkey, MediaInfo *ThisList[], int lindex, int mid, int rindex);
void mergesort(char sortkey, MediaInfo *ThisList[], int lindex, int rindex);
void PrintMedia(MediaInfo *a[], int N, char key1, char key2);
char* Get_Infinity(char* a, char* b);
int Get_Infinity(int a, int b);
MediaInfo **TmpList(MediaInfo *ThisList[], int lindex, int mid, int rindex);
void isort(char sortkey, MediaInfo *x[],int length);
int RangeAfter(MediaInfo *a, MediaInfo *b, char comparefield);

template <typename T>
void swapPt(T * & a, T * & b){
    T *c;
    c = a;
    a = b;
    b = c;
    return;
};

int partition(char sortkey, MediaInfo *ThisList[], int lindex, int rindex){
    int i, j;
    int pivotindex;

    swapPt(ThisList[lindex],ThisList[(lindex + rindex) / 2]);
    pivotindex = lindex;

    for (i = lindex, j = i + 1; j <= rindex; j++){

        if (RangeAfter(ThisList[pivotindex],ThisList[j],sortkey)){
            i++;
            swapPt(ThisList[i],ThisList[j]);
            }
    }
    swapPt(ThisList[lindex],ThisList[i]);
    return i;
};

void qsort(char sortkey, MediaInfo *ThisList[],int lindex, int rindex)
{
    int pivotat;
    if (lindex >= rindex){
        return;
    }
    pivotat = partition(sortkey, ThisList, lindex, rindex);
    qsort(sortkey, ThisList, lindex, pivotat-1);
    qsort(sortkey, ThisList, pivotat + 1, rindex);
};

int RangeAfter(MediaInfo *a, MediaInfo *b, char comparefield)
{
    if (comparefield == 't') {
        return  (strcmp(a->title, b->title) >= 0);
    }
    else if (comparefield == 'g') {
        return  (strcmp(a->genre, b->genre) >= 0);
    }
    else if (comparefield == 'p') {
        return (a->popularity <= b->popularity);
    }
    else {
        exit(1);
    }
};

void mergesort(char sortkey, MediaInfo *ThisList[], int lindex, int rindex){
    int mid;

    if (lindex >= rindex){
        return;
    }

    mid = (lindex + rindex)/2;
    mergesort(sortkey, ThisList, lindex, mid);
    mergesort(sortkey, ThisList, mid + 1, rindex);
    merge(sortkey, ThisList, lindex, mid, rindex);

    return;
};

char* Get_Infinity(char* a, char* b){
    char* c = new char[41];
    if (strcmp(a, b) > 0){
        strcpy(c, a);
    } else {
        strcpy(c, b);
    }
    strcat(c,"z");
    return c;
};

int Get_Infinity(int a, int b){
    return (a > b) ? (-a - 1) : (-b - 1);
};

MediaInfo **TmpList(MediaInfo *ThisList[], int lindex, int mid, int rindex){
    MediaInfo* (*result) = new MediaInfo*[rindex - lindex +2];
    int k, j;
    //copy the array to a temp
    for (int m = 0; m < mid - lindex + 1; m++){
        result[m] = ThisList[lindex + m];
    }
    for (k = mid - lindex + 2 ,j = rindex; k < rindex - lindex + 2; j--, k++){
        result[k] = ThisList[j];
    }

    //insert an infinity in the middle of the temp array
    result[mid - lindex + 1] = new MediaInfo;
    char *InfTitle = Get_Infinity(result[mid - lindex]->title, result[mid - lindex + 2]->title);
    char *InfGenre = Get_Infinity(result[mid - lindex]->genre, result[mid - lindex + 2]->genre);

    strcpy (result[mid - lindex + 1]->title, InfTitle);
    strcpy (result[mid - lindex + 1]->genre, InfGenre);
    result[mid - lindex + 1]->popularity = Get_Infinity(result[mid - lindex]->popularity, result[mid - lindex + 2]->popularity);

    delete InfTitle;
    delete InfGenre;
    return result;
};


void merge(char sortkey, MediaInfo *ThisList[], int lindex, int mid, int rindex){
    int i, j, k;

    MediaInfo* (*tmp) = TmpList(ThisList, lindex, mid, rindex);

        for ( k = lindex, i = 0, j = rindex - lindex+ 1; k <= rindex; k++){
            ThisList[k] = ( RangeAfter(tmp[j], tmp[i], sortkey)) ? tmp[i++] : tmp[j--];
        }

    delete tmp[mid - lindex + 1];
    delete[] tmp;
    return;
};

void PrintMedia(MediaInfo *ThisList[], int N, char key1, char key2)
{
    if (key1 == 't'){
        if (key2 == 'g' || key2 == 'x'){
            for (int i = 0; i < N; i++){
                printf("%s ", ThisList[i]->title);
                printf("%s ", ThisList[i]->genre);
                printf("%i\n", ThisList[i]->popularity);
            }
            return;
        }
        if (key2 == 'p'){
            for (int i = 0; i < N; i++){
                printf("%s ", ThisList[i]->title);
                printf("%i ", ThisList[i]->popularity);
                printf("%s\n", ThisList[i]->genre);
            }
            return;
        }
    }
    else if(key1 == 'g'){
        if (key2 == 't' || key2 == 'x'){
            for (int i = 0; i < N; i++){
                printf("%s ", ThisList[i]->genre);
                printf("%s ", ThisList[i]->title);
                printf("%i\n", ThisList[i]->popularity);
            }
            return;
        }
        if (key2 == 'p'){
            for (int i = 0; i < N; i++){
                printf("%s ", ThisList[i]->genre);
                printf("%i ", ThisList[i]->popularity);
                printf("%s\n", ThisList[i]->title);
            }
            return;
        }
    }
    else if(key1 == 'p'){
        if (key2 == 't' || key2 == 'x'){
            for (int i = 0; i < N; i++){
                printf("%i ", ThisList[i]->popularity);
                printf("%s ", ThisList[i]->title);
                printf("%s\n", ThisList[i]->genre);
            }
            return;
        }
        if (key2 == 'g'){
            for (int i = 0; i < N; i++){
                printf("%i ", ThisList[i]->popularity);
                printf("%s ", ThisList[i]->genre);
                printf("%s\n", ThisList[i]->title);
            }
            return;
        }
    }

};
