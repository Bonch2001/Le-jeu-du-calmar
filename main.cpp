#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Player
{
public:
    string name;
    string surname;
    string city;
    long int debt;
    int weigth;
    Player(string n, string s, string c, long int d, int w)
    {
        this->name = n;
        this->surname = s;
        this->city = c;
        this->debt = d;
        this->weigth = w;
    }
};

class Contestant : public Player
{
    int number;
    using Player::Player;
};

class Supervisor : public Player
{
    string mask;
    using Player::Player;
};

string nameGenerator(int length)
{
    string name;
    name += rand() % 26 + 65;
    for (int j = 1; j < length; j++)
    {
        name += rand() % 26 + 97;
    }
    return name;
}

int main()
{
    vector<Contestant> contestants;
    vector<Supervisor> supervisors;
    int i, j, nameLength, surnameLength, cityLength,  debt, weight;
    string name, surname, city;

    srand(time(NULL));

    for (i = 0; i < 99; i++)
    {
        nameLength = rand() % 12 + 2;
        name = nameGenerator(nameLength);

        surnameLength = rand() % 12 + 2;
        surname = nameGenerator(surnameLength);

        cityLength = rand() % 12 + 2;
        city = nameGenerator(cityLength);

        debt = rand() % 90001 + 10000;

        weight = rand() % 51 + 50;

        //cout << name <<" "<< surname <<" "<< city <<" "<< debt<<" "<< weight << endl;
    }

    return 0;
}