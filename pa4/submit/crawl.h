///8.8 15:47
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <queue>
#include <stack>

using namespace std;
typedef queue<WebPage*> WebQ;
typedef stack<WebPage*> WebS;
int STARTINGINDEX = 0;

double TOLERANCE = 0.001;
double EPSINON = 10e-35;

///PRINT///
void printrout(WebQ TheRout){
    WebPage* currpage;
    while( TheRout.size() > 1){
        currpage = TheRout.front();
        TheRout.pop();
        printf("%d ", currpage->webpageID);
    }
    currpage = TheRout.front();
    printf("%d\n", currpage->webpageID);
};

void printstackrout(WebS TheRout){
    WebPage* currpage;
    if( TheRout.size() > 1){
        currpage = TheRout.top();
        TheRout.pop();
        printstackrout(TheRout);
        printf(" %d", currpage->webpageID);
    } else{
        currpage = TheRout.top();
        printf("%d", currpage->webpageID);
    }
};

void printrout(WebS TheRout){
    printstackrout(TheRout);
    printf("\n");
};

///PRINT///

///GREEDY///
WebPage *GreedyNext(Network &nw, int startindex){
    double mindist = INFINITY;
    double curdist;
    int nextindex;
    for(int i = 0; i < nw.size() ; i++){
        if (!nw.Pages[i].token){
            curdist = Distance(nw.Pages[startindex], nw.Pages[i]);
            if (curdist < mindist){
                mindist = curdist;
                nextindex = i;
            }
        }
    }
    nw.Pages[nextindex].token = 1;

    return &nw.Pages[nextindex];
};

void GreedyCrawl(Network &thisnetwork, WebQ &rout, int startindex){
    WebPage* nexthop;
    WebPage* currenthop;
    bool ALLTOKEN = false;
    int routlength = 0;
    currenthop = &thisnetwork.Pages[startindex];
    nexthop = GreedyNext(thisnetwork,currenthop->webpageID);
    rout.push(nexthop);
    thisnetwork.Pages[startindex].token = true;
    while (!ALLTOKEN){
        if (routlength < (thisnetwork.size() - 1)){
            routlength++;
            } else{
                ALLTOKEN = true;
                continue;
            }
        nexthop = GreedyNext(thisnetwork, nexthop->webpageID);
        rout.push(nexthop);

    }
    rout.push(&thisnetwork.Pages[startindex]);
};

///GREEDY///

///2-Approximation///
bool TriangleIneqtest(Network thisnetwork){
    double a, b, c;
    for (int i = 0; i < thisnetwork.size(); i ++){
        for( int j = i + 1; j < thisnetwork.size(); j ++){
            for(int k = j + 1; k < thisnetwork.size(); k ++){
                a = Distance(thisnetwork.Pages[j],thisnetwork.Pages[k]);
                b = Distance(thisnetwork.Pages[i],thisnetwork.Pages[j]);
                c = Distance(thisnetwork.Pages[i],thisnetwork.Pages[k]);
                if ((a > (1 + TOLERANCE)*(b + c)) || ((b > (1 + TOLERANCE)*(a + c))) || ((c > (1 + TOLERANCE)*(b + a)))){
                    return false;
                }
            }
        }
    }
    return 1;
};

class cmp{
    public:
    bool operator()(WebPage* a, WebPage* b){
        return ((a->cost - b->cost > EPSINON)
        || ((fabs(a->cost - b->cost) < EPSINON) && (a->webpageID > b->webpageID)));
    }
};

void InitializeNetwork(Network &thisnetwork, int startindex){
    for(int i = 0; i < thisnetwork.size(); i++){
        thisnetwork.Pages[i].cost = INFINITY;
        thisnetwork.Pages[i].token = false;
    }
    thisnetwork.Pages[startindex].cost = 0.0000000;
    thisnetwork.Pages[startindex].prev = NULL;
    thisnetwork.Pages[startindex].token = true;
};

void Prim(Network &thisnetwork, int startindex){
    priority_queue<WebPage*, vector<WebPage*>,cmp> pq;
    InitializeNetwork(thisnetwork,startindex);
    pq.push(&thisnetwork.Pages[startindex]);
    WebPage *nearestpage;

    double newcost;
    while (!pq.empty()){
        nearestpage = pq.top();
        pq.pop();
        if (!nearestpage->mst){
            nearestpage->mst = true;
            for( int i = 0; i < thisnetwork.size(); i ++){
                if(!thisnetwork.Pages[i].mst){///not on the mst
                    newcost = Distance(thisnetwork.Pages[i],*nearestpage);

                    if((thisnetwork.Pages[i].cost - newcost > EPSINON)
                    || (fabs(thisnetwork.Pages[i].cost - newcost) == 0
                    && nearestpage->webpageID < thisnetwork.Pages[i].prev->webpageID)){
                        cout<<"";
                        thisnetwork.Pages[i].cost = newcost;
                        thisnetwork.Pages[i].prev = nearestpage;
                        pq.push(&thisnetwork.Pages[i]);
                    }
                }
            }
        }
    }
    for (int i = 0; i < thisnetwork.size(); i ++){
        if (i != startindex){
            thisnetwork.Pages[i].prev->childlist.push(&thisnetwork.Pages[i]);
        }
    }
            return;
};

void DepthFirstTraversal(Network &thisnetwork, WebQ &therout, WebPage *startpage){
    WebPage *currentpage;
    while (!thisnetwork.Pages[startpage->webpageID].childlist.empty()){
        currentpage = thisnetwork.Pages[startpage->webpageID].childlist.top();
        thisnetwork.Pages[startpage->webpageID].childlist.pop();
        therout.push(currentpage);

        startpage = currentpage;
    }
        if (startpage->prev == NULL){
            therout.push(startpage);
            return;
        }
        DepthFirstTraversal(thisnetwork, therout, startpage->prev);

};

void TwoApproximationCrawl(Network &thisnetwork, WebQ &therout, int startindex){
    if (!TriangleIneqtest(thisnetwork)){
        cout<<"Invalid test case.\n";
        exit(0);
    } else {
        Prim(thisnetwork, startindex);
        therout.push(&thisnetwork.Pages[startindex]);
        DepthFirstTraversal(thisnetwork, therout, &thisnetwork.Pages[startindex]);
        }
};

///2-Approximation///

//////////////////
///Branch&Bound///
//////////////////

bool Promising(Network &thisnetwork, WebPage *currpage, double currentmin){
    bool ispromising = false;
    bool ALLTOKEN = true;
    for (int i = 0; i < thisnetwork.size() && !ispromising;i ++){
        if (!thisnetwork.Pages[i].token){
            ALLTOKEN = false;
            if (currpage->cost + Distance(*currpage, thisnetwork.Pages[i]) - currentmin < -EPSINON){
                ispromising = true;
            }
        }
    }
    if (ALLTOKEN){
        if (currpage->cost + Distance(*currpage, thisnetwork.Pages[0]) - currentmin < -EPSINON){
            return true;
        }
    }
    return ispromising;
};

double EstimateMin(Network thisnetwork, int startindex){
    double estimateroutlength = 0;
    WebQ Erout;
    GreedyCrawl(thisnetwork, Erout, startindex);
    WebPage *start = Erout.front();
    WebPage *next;
    Erout.pop();
    while(!Erout.empty()){
        next = Erout.front();
        Erout.pop();
        estimateroutlength += Distance(*start, *next);
        start = next;
    }
    return estimateroutlength;
};

void BranchandBoundCrawl(Network &thisnet, WebS &rout, WebPage *currpage, double &currentmin, queue<WebS> &routtable ){
    if (currpage->webpageID == STARTINGINDEX ){
        rout.push(&thisnet.Pages[STARTINGINDEX]);
    }
    thisnet.Pages[STARTINGINDEX].token = 1;
    thisnet.Pages[STARTINGINDEX].cost = 0;
    if (Promising(thisnet, currpage, currentmin)){
        if (rout.size() == thisnet.size()){
            if((currpage->cost + Distance(*currpage, thisnet.Pages[0])) - currentmin < - EPSINON){
                currentmin = currpage->cost + Distance(*currpage, thisnet.Pages[0]);
                rout.push(&thisnet.Pages[STARTINGINDEX]);
                if (!routtable.empty()){
                    routtable.pop();
                }
                routtable.push(rout);
                rout.pop();
                return;
            }
        } else {
            for (int n = 0; n < thisnet.size() ; n++){
                if (!thisnet.Pages[n].token){
                    thisnet.Pages[n].cost = currpage->cost + Distance(*currpage, thisnet.Pages[n]);
                    thisnet.Pages[n].token = true;
                    rout.push(&thisnet.Pages[n]);
                    BranchandBoundCrawl(thisnet,rout,&thisnet.Pages[n], currentmin, routtable);
                    if (rout.size() == thisnet.size()){
                    rout.top()->token = false;
                    rout.top()->cost = INFINITY;
                    rout.pop();
                    }
                }
            }
            if (rout.size() > 1){
            rout.top()->token = false;
            rout.top()->cost = INFINITY;
            rout.pop();
            }
        }
    } else  {
                rout.top()->token = false;
                rout.top()->cost = INFINITY;
                rout.pop();
    }
};

//////////////////
///Branch&Bound///
//////////////////
