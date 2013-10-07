//8.8 15:47///
#include <string>
#include <iostream>
#include <stdio.h>
#include "p4.h"
#include "crawl.h"
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){
    string GREEDYOPT = "-g";
    string TWOAPPOPT = "-e";
    string BANDBOPT = "-b";
    string op[argc];
    int wp_totalNum;
    int FPLength;
    int trash;
    int countg = 0;
    int counte = 0;
    int countb = 0;
    trash = scanf("%d %d", &wp_totalNum, &FPLength);
    Network TheNetwork(wp_totalNum);
    TheNetwork.SetFPLength(FPLength);

    for(int i = 0; i < wp_totalNum; i++){
        TheNetwork.loadPage(i);
    }

    for (int i = 0; i < argc; i++){
        op[i] = argv[i];
        if(op[i] == GREEDYOPT){
            countg ++;
        } else if(op[i] == TWOAPPOPT){
            counte ++;
        } else if(op[i] == BANDBOPT){
            countb ++;
        }
    }

    if (countg == 1 && !(counte || countb)){
        ///Greedy///
        WebQ TheRout;
        GreedyCrawl(TheNetwork, TheRout, STARTINGINDEX);
        printrout(TheRout);
    } else if(counte == 1 && !(countg || countb)){
        ///2-Approximation///
        WebQ TheRout;
        TwoApproximationCrawl(TheNetwork, TheRout, STARTINGINDEX);
        printrout(TheRout);
    } else if(countb == 1 && !(countg || counte)){
        ///B&B///
        WebS TheRoutStack;
        queue<WebS> RoutTable;
        double EstMinRout;
        EstMinRout = (1 + TOLERANCE) * EstimateMin(TheNetwork, STARTINGINDEX);
        InitializeNetwork(TheNetwork, STARTINGINDEX);
        BranchandBoundCrawl(TheNetwork, TheRoutStack, &TheNetwork.Pages[STARTINGINDEX], EstMinRout, RoutTable);
        printrout(RoutTable.front());
    } else {
        cerr<<"Get Invalid Command!"<<endl;
        exit(0);
    }
    return 1;
};

