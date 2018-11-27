#ifndef STACK
#define STACK

typedef char base;
class Stack {
public:
    Stack (){
        topOfStack = NULL;
    };
    base top (void);
    base pop2(void);
    void pop(void);
    void push (const base &x);
    bool isNull(void);
    void destroy(void);
private:
    struct node;
    node *topOfStack;
};

#endif
