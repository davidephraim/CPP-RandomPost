#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Stack{
    int top;
    int size;
    string data[100];

    Stack(int stackSize){
        top = -1;
        size = stackSize;
    }
};

void push(string dataInput, Stack** stackName){
    if((*stackName)->top < (*stackName)->size) (*stackName)->data[++(*stackName)->top] = dataInput;
}

string pop(Stack** stackName){
    if((*stackName)->top > -1) return (*stackName)->data[(*stackName)->top--];
    return "";
}

Stack* destroyString(Stack* stackName){
    Stack* stackB = new Stack(stackName->size);
    while(stackName->top > -1){
        push(pop(&stackName), &stackB);
        if(stackName->top > -1){
            while((stackB->top > -1) && (stackB->data[stackB->top] == stackName->data[stackName->top])){
                pop(&stackName);
                pop(&stackB);
            }
        }
    }
    return stackB;
}

void display(Stack* stackName){
    cout<<stackName->top + 1<<endl;
    while(stackName->top > -1) cout<<pop(&stackName)<<endl;
}

int menu(){
    int choice;
    cout<<"Enter sentences and the program will remove redundant"<<endl;
    cout<<"[1] Input Sentences"<<endl;
    cout<<"[2] Display Updated Sentences"<<endl;
    cout<<"[3] Exit Program"<<endl;
    cout<<"Input choice: "; 

    while(!(cin>>choice) || (choice < 1 || choice > 3)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid input! Please re-enter a integer between 1 and 3: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main(){
    int mn, inSize;
    string sentence;
    Stack* stackA = NULL;

    while(mn = menu()){
        switch(mn){
            case 1:
                cout<<"Input Size: ";
                while(!(cin>>inSize) || inSize <= 0 || inSize > 100){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout<<"Invalid input! Please re-enter a positive integer betwwen 1 to 100: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if(stackA != NULL) delete stackA;

                stackA = new Stack(inSize);
                for(int i=0; i<inSize; ++i){
                    cout<<"Input Sentence ["<<i+1<<"]: "; getline(cin, sentence);
                    push(sentence, &stackA);
                }
            break;
            case 2:
                if(stackA != NULL){
                    Stack* stackB = destroyString(stackA);
                    display(stackB);
                    delete stackB;
                }
                else cout<<"Database is empty! Please input sentences first."<<endl;
            break;
            case 3:
                if(stackA != NULL) delete stackA;
                exit(0);
            break;
            default:
                cout<<"Invalid Input!"<<endl;
            break;
        }
    }
    return 0;
}