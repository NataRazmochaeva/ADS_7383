#include <iostream>
#include <cstdlib>
#include "stack.h"
using namespace std ;

struct Stack::node {
    base hd;
    node *tl;
    node (){
     tl = NULL;
    }
};

base Stack::top (void){
    if (topOfStack == NULL) {
        cerr << "Error: top(null) \n";
        exit(1);
    }
        else return topOfStack->hd;
}

base Stack::pop2(void){
      if (topOfStack == NULL) {
          cerr << "Error: pop(null) \n";
          exit(1);
      }
      else {
          node *oldTop = topOfStack;
          base r = topOfStack->hd;
          topOfStack = topOfStack->tl;
          delete oldTop;
          return r;
      }
  }

void Stack::pop(void){
    if (topOfStack == NULL) {
        cerr << "Error: pop(null) \n";
        exit(1);
    }
    else {
        node *oldTop = topOfStack;
        topOfStack = topOfStack->tl;
        //delete oldTop->hd;
        delete oldTop;
    }
}

void Stack::push (const base &x){
  node *p;
  p = topOfStack;
  topOfStack = new node;
  if (topOfStack != NULL) {
       topOfStack->hd = x;
       topOfStack->tl = p;
  }
  else {
       cerr << "Memory not enough\n";
       exit(1);
  }
}

bool Stack::isNull(void){
    return (topOfStack == NULL) ;
}

void Stack:: destroy(void){
    while (topOfStack != NULL) {
         pop();
    }
}
