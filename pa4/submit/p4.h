///8.8 15:47

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <queue>
#include <stack>

using namespace std;

class WebPage{

private:
    int trash;
    class da{
        public:
        bool operator()(WebPage* a, WebPage* b){
        return (a->webpageID > b->webpageID);
    }
};
public:

    int webpageID;
    bool token;
    char* fingerprint;
    int fp_length;
    int wp_x;
    int wp_y;
    bool mst;
    double cost;

    WebPage* prev;
    priority_queue<WebPage*, vector<WebPage*>, da> childlist;
    WebPage(){    };
    ~WebPage(){
    }
    void SetFPLength(int l){
        fp_length = l;
    };
    void ReadinWP(){
        fingerprint = (char*) malloc( sizeof(char)*fp_length);
        trash = scanf("%d %d %d %s\n", &webpageID, &wp_x, &wp_y, fingerprint);
    };
};

class Network{
    private:
    int NetworkSize;
    int FingerPrintLength;
    int EdgeNum;
    public:
    WebPage *Pages;

    Network(int s){
        NetworkSize = s;
        Pages = new WebPage[NetworkSize];

    };

    ~Network(){
    };

    void SetFPLength(int l){
        FingerPrintLength = l;
        for( int i = 0; i < NetworkSize; i++){
            Pages[i].SetFPLength(l);
        }
    };
    int size(){
        return NetworkSize;
    };
    void loadPage(int index){
        Pages[index].ReadinWP();
    }
    bool Pagetoken(int index){
        return Pages[index].token;
    }

    void PageSettoken(int index){
        Pages[index].token = true;
    }
};

int common_bits(char* a, char* b, int length){
    int result = 0;
    for (int i = 0; i < length; i++){
        if (a[i] == b[i]){
            result ++;
        }
    }
    return result;
};

double Delay(WebPage a, WebPage b){
    return sqrt(pow(a.wp_x - b.wp_x, 2) + pow(a.wp_y - b.wp_y, 2));
};

double Relevance(WebPage a, WebPage b){
    return 1 + (double)common_bits(a.fingerprint, b.fingerprint, a.fp_length)/(double)a.fp_length;
};

double Distance(WebPage a, WebPage b){
    double result;
    result = Delay(a, b) * Relevance(a, b);
    return result;
};
