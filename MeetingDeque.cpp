#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define MAX_QUEUE_SIZE 105

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
            std::cout << "ERROR\n";
        else
        {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
        }
    }

    DATA dequeue()
    {
        if (isEmpty())
            std::cout << "ERROR\n";
        else
        {
            front = (front + 1) % MAX_QUEUE_SIZE;
            return data[front];
        }
    }

    DATA peek()
    {
        if (isEmpty())
            std::cout << "ERROR\n";
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
            std::cout << "ERROR\n";
        else
        {
            data[front] = val;
            front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
        }
    }

    DATA deleteRear()
    {
        if (isEmpty())
            std::cout << "ERROR\n";
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
            std::cout << "ERROR\n";
        else
            return data[rear];
    }
};

struct Male
{
    int time;
    std::string name;
    char sex;
    char pos;
};

struct Female : public Male{
};

int main()
{
    int num;
    std::string numberstr;
    std::getline(std::cin, numberstr);
    std::cin.clear();
    num = stoi(numberstr);

    std::string temp;
    std::vector<std::string> list;
    
    queue<Male> MQ;
    queue<Female> FQ;

    int match = 0;
    
    for (int i = 0; i < num; ++i)
    {
        std::getline(std::cin, temp);
        list.push_back(temp);
        std::cin.clear();

        std::vector<std::string> res;
        std::string token;
        std::istringstream tokenstream(temp);
        char t = ' ';

        while (std::getline(tokenstream, token, t))
        {
            res.push_back(token);
        }
        
        Male MT;
        Female FT;

        if (res.at(2).at(0) == 'm')
        {
            MT.time = stoi(res.at(0));
            MT.name = res.at(1);
            MT.sex = res.at(2).at(0);
            MT.pos = res.at(3).at(0);
            
            if (MT.pos == 'F')
                MQ.addFront(MT);
            if (MT.pos == 'R')
                MQ.addRear(MT);
        }

        if (res.at(2).at(0) == 'f')
        {
            FT.time = stoi(res.at(0));
            FT.name = res.at(1);
            FT.sex = res.at(2).at(0);
            FT.pos = res.at(3).at(0);

            if (FT.pos == 'F')
                FQ.addFront(FT);
            if (FT.pos == 'R')
                FQ.addRear(FT);
        }

        if (!MQ.isEmpty() && !FQ.isEmpty())
        {
            Male MTT = MQ.deleteFront();
            Female FTT = FQ.deleteFront();
            std::cout<<"Matched : "<<MTT.name<<" "<<FTT.name<<std::endl;
            ++match;
        }
    }

    int Mn = 0;
    while (!MQ.isEmpty())
    {
        MQ.deleteFront();
        Mn++;
    }

    int Fn = 0;
    while (!FQ.isEmpty())
    {
        FQ.deleteFront();
        Fn++;
    }

    std::cout<<match<<" "<<Mn<<" "<<Fn<<std::endl;

    return 0;
}
