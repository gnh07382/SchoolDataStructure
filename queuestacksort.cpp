#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define MAX_QUEUE_SIZE 100

template<typename DATA>
class queue
{
protected:
    int front;
    int rear;

    DATA data[MAX_QUEUE_SIZE];
public:
    queue()
    {
        front = rear = 0;
    }

    bool isEmpty()
    {
        return front == rear;
    }

    bool isFull()
    {
        return (rear + 1) % MAX_QUEUE_SIZE == front;
    }

    void enqueue(DATA val)
    {
        if (isFull())
            return;
        else
        {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
        }
    }

    DATA dequeue()
    {
        if (isEmpty())
            return 0;
        else
        {
            front = (front + 1) % MAX_QUEUE_SIZE;
            return data[front];
        }
    }

    DATA peek()
    {
        if (isEmpty())
            return 0;
        else
            return data[(front + 1) % MAX_QUEUE_SIZE];
    }

    void addRear(DATA val)
    {
        enqueue(val);
    }

    DATA deleteFront()
    {
        return dequeue();
    }

    DATA getFront()
    {
        return peek();
    }

    void addFront(DATA val)
    {
        if (isFull())
            return;
        else
        {
            data[front] = val;
            front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
        }
    }

    DATA deleteRear()
    {
        if (isEmpty())
            return 0;
        else
        {
            DATA ret = data[rear];
            rear = (rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
            return ret;
        }
    }

    DATA getRear()
    {
        if (isEmpty())
            return 0;
        else
            return data[rear];
    }
};

template<typename DATA>
class Stack
{
private:
    int top;
    std::vector<DATA> data;

public:
    Stack()
    {
    }

    ~Stack()
    {
    }

    void push(DATA x)
    {
        data.push_back(x);
    }

    DATA pop()
    {
        if (!empty())
        {
            DATA temp = data.back();
            data.pop_back();
            return temp;
        }
    }

    DATA peek()
    {
        if (!empty())
            return data.back();
    }

    [[maybe_unused]] void display()
    {
        std::cout << "Number of stack: " << data.size() << std::endl;

        for (const auto &i : data)
            std::cout << i << std::endl;
    }

    bool empty()
    {
        return data.empty();
    }
};

int main()
{
    std::string setting, token, element;
    std::getline(std::cin, setting);
    std::cin.clear();
    std::vector<std::string> res;
    std::istringstream iss(setting);
    char t = ' ';
    while (std::getline(iss, token, t))
        res.push_back(token);

    int number = stoi(res.at(0));
    char sort = res.at(1).at(0);

    std::getline(std::cin, element);
    std::cin.clear();

    std::string token2;
    std::vector<std::string> strelem;
    std::istringstream iiss(element);
    while (std::getline(iiss, token2, t))
        strelem.push_back(token2);

    queue<int> inque, outque;
    Stack<int> stack;
    for (const auto& x : strelem)
        inque.enqueue(stoi(x));

    if (sort == 'a')
    {
        int i = 1;
        while (!inque.isEmpty() || !stack.empty())
        {
            if (i == inque.getFront() || i == stack.peek())
            {
                if (i == inque.getFront())
                    outque.enqueue(inque.dequeue());
                if (i == stack.peek())
                    outque.enqueue(stack.pop());
                i++;
            }
            else if (!inque.isEmpty())
            {
                stack.push(inque.dequeue());
            }
            else
                break;
            //stack.display();
            //std::cout<<inque.isEmpty()<<stack.empty();
        }
    }

    if (sort == 'd')
    {
        int i = number;
        while (!inque.isEmpty() || !stack.empty())
        {
            if (i == inque.getFront() || i == stack.peek())
            {
                if (i == inque.getFront())
                    outque.enqueue(inque.dequeue());
                if (i == stack.peek())
                    outque.enqueue(stack.pop());
                i--;
            }
            else if (!inque.isEmpty())
            {
                stack.push(inque.dequeue());
            }
            else
                break;
            //stack.display();
            //std::cout<<inque.isEmpty()<<stack.empty();
        }
    }

    if (stack.empty())
        std::cout << "Yes\n";
    else
        std::cout << "No\n";

    return 0;
}
