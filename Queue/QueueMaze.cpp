#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define MAX_QUEUE_SIZE 100
#define HUGE_VAL 1e15

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

struct Location2D
{
    int row;
    int col;

    int history = 0;

    Location2D(int r = 0, int c = 0, int cnt = 0)
    {
        row = r;
        col = c;
        history = cnt;
    }

    bool isNeighbor(Location2D &p)
    {
        return ((row == p.row && (col == p.col - 1 || col == p.col + 1)) ||
                (col == p.col && (row == p.row - 1 || row == p.row + 1)));
    }

    bool operator==(Location2D &p)
    {
        return row == p.row && col == p.col;
    }
};

class map
{
private:
    int row, col;

public:
    char **mat;

    map(int row, int col) : row(row), col(col)
    {
        mat = new char *[row];
        for (int i = 0; i < row; i++)
            mat[i] = new char[col];
    }

    ~map()
    {
        if (mat != NULL)
        {
            for (int i = 0; i < row; ++i)
            {
                delete[] mat[i];
            }
            delete[] mat;
        }
    }

    bool isValidLoc(int r, int c)
    {
        if (r < 0 || c < 0 || r >= row || c >= col)
            return false;
        else
            return mat[r][c] == '0' || mat[r][c] == 'T';
    }
};

bool is_number(const std::string &s)
{
    char *end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}

int main()
{
    std::string Str, temp;

    std::string mapset;

    std::getline(std::cin, mapset);
    std::cin.clear();
    std::vector<std::string> res;
    std::string token;
    std::istringstream tokenStream(mapset);
    char t = ' ';
    while (std::getline(tokenStream, token, t))
    {
        res.push_back(token);
    }

    int row = stoi(res.at(0));
    int col = stoi(res.at(1));

    map map(row, col);

    for (int i = 0; i<row; i++)
    {
        std::getline(std::cin, temp);
        Str.append(temp);
        std::cin.clear();
    }

    int start, end;

    int cnt = 0;
    for (auto x : Str)
    {
        map.mat[cnt / col][cnt % col] = x;

        if (x == 'S')
            start = cnt;
        if (x == 'T')
            end = cnt;
        cnt++;
        //입구, 출구 위치 메모
    }//여기까지가 문자열 받아들이는거

    queue<Location2D> locqueue;//여기부터 문자열 처리
    Location2D entry(start / row, start % row);
    locqueue.enqueue(entry);

    while (!locqueue.isEmpty())
    {
        Location2D here = locqueue.getFront();
        locqueue.deleteFront();

        int r = here.row;
        int c = here.col;
        int cnt = here.history;

        if (map.mat[r][c] == 'T')
        {
            std::cout <<++cnt<<std::endl;
            return 0;
        }
        else
        {
            map.mat[r][c] = '.';
            if (map.isValidLoc(r - 1, c))
                locqueue.enqueue(Location2D(r - 1, c, cnt+1));
            if (map.isValidLoc(r + 1, c))
                locqueue.enqueue(Location2D(r + 1, c, cnt+1));
            if (map.isValidLoc(r, c - 1))
                locqueue.enqueue(Location2D(r, c - 1, cnt+1));
            if (map.isValidLoc(r, c + 1))
                locqueue.enqueue(Location2D(r, c + 1, cnt+1));
        }
    }

    std::cout<<"0\n";
    return 0;
}
