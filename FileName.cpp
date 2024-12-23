#include <iostream> 
using namespace std;

struct other {
    other* next = nullptr, *before = nullptr;
    int number{ 0 };
    other(int num) : number(num)
        {}
};

class List{
    other *start = nullptr, *tail = nullptr;
    static int circleObj;
    static List* valuseObj;
    List() = default;
public:

    static List* createObj() {
        if (circleObj == 0) {
            circleObj += 1;
            List* ptr = new List();
            valuseObj = ptr;
            return ptr;
        }
        cout << "Obj > 0";
        return valuseObj;
    }
    void push_back(const int a) {
        if(tail == nullptr){
            other* pere = new other(a);
            start = tail = pere;
        }
        else {
            other* pere = tail;
            tail = new other(a);
            pere->next = tail;
            tail->before = pere;
        }
    }
    void push_front(const int a) {
        if (start == nullptr) {
            other* pere = new other(a);
            start = tail = pere;
        }
        else {
            other* pere = start;
            start = new other(a);
            pere->before = start;
            start->next = pere;
        }
    }
    void insert(const int a, const int position) {
        if (position == 0) push_front(a);
        else {
            other* pere = start;
            if (pere == nullptr) {
                cout << "The specified position exceeds the deque" << endl;
                return;
            }
            other* next = pere->next;
            for (int i = 0; i < position && pere->next != nullptr; i++) {
                if (i+1 == position) {
                    other* perem = new other(a);
                    pere->next = perem; next->before = perem;
                    perem->next = next; perem->before = pere;
                }
                pere = next;
                next = pere->next;
            }
        }
        
    }
    int pop_back() {
        if (tail == nullptr) return 0;
        other* pere = tail->before;
        int result = tail->number;
        delete tail;
        tail = pere;
        tail->next = nullptr;
        return result;
    }
    int pop_front() {
        if (start == nullptr) return 0;
        other* pere = start->next;
        int result = start->number;
        delete start;
        start = pere;
        return result;
    }
    void erase(const int position) {
        if (start == nullptr) { cout << "deque is clear"; return; }
        other* pere = start;
        if (position == 0) {
            pop_front(); return;
        }
        for (int i = 0; i < position+1; i++) {
            other* next = pere->next;
            if (i == position) {
                other* prol = pere->before;
                if (pere == tail) {
                    delete pere;
                    tail = prol;
                    prol->next = nullptr;
                    return;
                }
                delete pere;
                prol->next = next;
                next->before = prol;
                return;
            }
            pere = next;
        }
        cout << "position not correctly"; return;
    }
    const void vivod() const {
        other* pere = start;
        while (pere) {
            other* next = pere->next;
            cout << pere->number << '-';
            pere = next;
       }
        cout << endl;
    }
    ~List() {
        other* pere = start;
        while(pere) {
            other* next = pere->next;
            delete pere;
            pere = next;
        }
    }
};
int List::circleObj = 0;
List* List::valuseObj{nullptr};
int main() {
    char value = ' ', valueIsSwitch = ' ';
    int numberIsSwitch{}, positionIsSwitch{};
    //List obj = List::createObj();
    List* obj = List::createObj();
    cout << "Hello, this is an int type deque";
    while (true) {
        cout << endl << "Enter the \"a\" - add the deque" << endl << "Enter the \"d\" - remove the deque" << endl << "Enter the \"q\" - quit" << endl;
        cin >> value;
        switch (value) {
        case 'a':
            cout << "Add to the end of the deque press   \"e\"" << endl << "Add to the top of the deque press  \"s\"" << endl << "Add to any location  \"h\"" << endl << "deque = ";
            obj->vivod();
            cin >> valueIsSwitch;
            switch (valueIsSwitch) {
            case 'e':
                cout << "Enter the number = ", cin >> numberIsSwitch;
                obj->push_back(numberIsSwitch);
                break;
            case 's':
                cout << "Enter the number = ", cin >> numberIsSwitch;
                obj->push_front(numberIsSwitch);
                break;
            case 'h':
                cout << "Enter the number = ", cin >> numberIsSwitch;
                cout << "Enter the position = ", cin >> positionIsSwitch;
                obj->insert(numberIsSwitch, positionIsSwitch);
                break;
            }
            break;
        case 'd':
            cout << "Remove to the end of the deque press   \"e\"" << endl << "Remove to the top of the deque press  \"s\"" << endl; 
            cout << "Remove to any location  \"h\"" << endl << "deque = ";
            obj->vivod();
            cin >> valueIsSwitch;
            switch (valueIsSwitch) {
            case 'e':
                obj->pop_back();
                break;
            case 's':
                obj->pop_front();
                break;
            case 'h':
                cout << "Enter the position = ", cin >> positionIsSwitch;
                obj->erase(positionIsSwitch);
                break;
            }
            break;
        case 'q':
            cout << "goodbay!";
            exit(0);
        }
    }
    
}
