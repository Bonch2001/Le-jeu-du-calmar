#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// base class for both Contestants and Supervisors
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
public:
    bool wildcard = false; // needed later in case the player remain without a team
    int team = -1;         // needed later when dividing contestants in teams
    int number;
    void setNumber(int n)
    {
        this->number = n;
    }
    int getNumber()
    {
        return this->number;
    }
    int Supervisor;
    void setSupervisor(int b)
    {
        this->Supervisor = b;
    }
    int getSupervisor()
    {
        return this->Supervisor;
    }
    using Player::Player; // using the same constructor as the base class
};

class Supervisor : public Player
{
public:
    string mask;
    void setMask(string m)
    {
        this->mask = m;
    }
    string getMask()
    {
        return this->mask;
    }
    int Contestants[11];
    void setContestants(int a[11])
    {
        for (int i = 0; i < 11; i++)
            this->Contestants[i] = a[i];
    }
    int *getContestants()
    {
        return this->Contestants;
    }
    using Player::Player; // using the same constructor as the base class
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
} // function that generate a name of a specified length

int main()
{
    vector<Contestant> contestants;
    vector<Supervisor> supervisors;
    int i, j, k, nameLength, surnameLength, cityLength, debt, weigth, maskID, maskNumber[3] = {0, 0, 0}, v[11], global[99] = {}, contestantID, check;
    string name, surname, city, mask, maskTypes[3] = {"rectangle", "triangle", "circle"};

    srand(time(NULL));

    // generate the contestants
    for (i = 0; i < 99; i++)
    {
        // assign random name, surname, city, debt and weight for each contestant
        nameLength = rand() % 12 + 2;
        name = nameGenerator(nameLength);

        surnameLength = rand() % 12 + 2;
        surname = nameGenerator(surnameLength);

        cityLength = rand() % 12 + 2;
        city = nameGenerator(cityLength);

        debt = rand() % 90001 + 10000;

        weigth = rand() % 51 + 50;

        Contestant c = Contestant(name, surname, city, debt, weigth); // create the object
        c.setNumber(i + 1);                                           // assign an ID to the contestant

        contestants.push_back(c); // add the created object to the vector of contestants
    }

    // generate the supervisors
    for (i = 0; i < 9; i++)
    {
        // assign random name, surname, city, debt and weight for each supervisor
        nameLength = rand() % 12 + 2;
        name = nameGenerator(nameLength);

        surnameLength = rand() % 12 + 2;
        surname = nameGenerator(surnameLength);

        cityLength = rand() % 12 + 2;
        city = nameGenerator(cityLength);

        debt = rand() % 90001 + 10000;

        weigth = rand() % 51 + 50;

        Supervisor s = Supervisor(name, surname, city, debt, weigth); // create the object

        do
        {
            maskID = rand() % 3;
            maskNumber[maskID]++;
        } while (maskNumber[maskID] > 3); // generate a random yet valid mask
        mask = maskTypes[maskID];
        s.setMask(mask); // assign a random mask to the supervisor

        supervisors.push_back(s); // add the created object to the vector of supervisors
    }

    // print the contestants
    cout << endl
         << "CONTESTANTS"
         << endl
         << "Number "
         << "Name "
         << "Surname "
         << "City "
         << "Debt "
         << "Weight"
         << endl;
    for (i = 0; i < 99; i++)
        cout << contestants[i].getNumber() << " " << contestants[i].name << " " << contestants[i].surname << " " << contestants[i].city << " " << contestants[i].debt << " " << contestants[i].weigth << endl;

    // print the supervisors
    cout << endl
         << "SUPERVISORS"
         << endl
         << "Name "
         << "Surname "
         << "City "
         << "Debt "
         << "Weight"
         << "Mask "
         << endl;
    for (i = 0; i < 9; i++)
        cout << supervisors[i].name << " " << supervisors[i].surname << " " << supervisors[i].city << " " << supervisors[i].debt << " " << supervisors[i].weigth << " " << supervisors[i].getMask() << endl;

    // assign a number of 11 contestants to each supervisor
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 11; j++) // vector of contestants' numbers assigned to each supervisor
            v[j] = 0;
        for (j = 0; j < 11; j++)
        {
            do
            {
                contestantID = rand() % 99 + 1;      // generate a random ID of the contestants
            } while (global[contestantID - 1] != 0); // check if the ID wasn't already assigned
            global[contestantID - 1] = 1;            // modify the global frequency vector of IDs
            v[j] = contestantID;                     // add the ID to the vector of contestants
        }
        supervisors[i].setContestants(v); // assign the vector to the supervisor
    }

    // based on the previous step, assign to each contestant the number of his supervisor
    for (i = 0; i < 9; i++)                                                           // iterate through all supervisors
        for (j = 0; j < 11; j++)                                                      // iterate through the contestants of each supervisor
            contestants[supervisors[i].getContestants()[j] - 1].setSupervisor(i + 1); // the supervisors don't have IDs, so use the position in the vector

    // print the contestants and their supervisors
    cout << endl
         << "CONTESTANTS EXTENDED"
         << endl
         << "Number "
         << "Name "
         << "Surname "
         << "City "
         << "Debt "
         << "Weight "
         << "Supervisor"
         << endl;
    for (i = 0; i < 99; i++)
        cout << contestants[i].getNumber() << " " << contestants[i].name << " " << contestants[i].surname << " " << contestants[i].city << " " << contestants[i].debt << " " << contestants[i].weigth << " " << contestants[i].getSupervisor() << endl;

    // print the supervisors and their contestants
    cout << endl
         << "SUPERVISORS EXTENDED"
         << endl
         << "Name "
         << "Surname "
         << "City "
         << "Debt "
         << "Weight "
         << "Mask "
         << "Contestants"
         << endl;
    for (i = 0; i < 9; i++)
    {
        cout << supervisors[i].name << " " << supervisors[i].surname << " " << supervisors[i].city << " " << supervisors[i].debt << " " << supervisors[i].weigth << " " << supervisors[i].getMask() << " ";
        for (j = 0; j < 11; j++)
            cout << supervisors[i].getContestants()[j] << " ";
        cout << endl;
    }

    // FIRST GAME: "RED LIGHT GREEN LIGHT"
    for (i = 0; i < contestants.size(); i++)
        if (contestants[i].getNumber() % 2 == 0)
        {
            contestants.erase(contestants.begin() + i);
        }

    // print the remaining contestants after first round
    cout << endl
         << "CONTESTANTS AFTER FIRST ROUND"
         << endl
         << "Number "
         << "Name "
         << "Surname "
         << "City "
         << "Debt "
         << "Weight"
         << endl;
    for (i = 0; i < contestants.size(); i++)
        cout << contestants[i].getNumber() << " " << contestants[i].name << " " << contestants[i].surname << " " << contestants[i].city << " " << contestants[i].debt << " " << contestants[i].weigth << endl;

    // SECOND GAME: "TUG OF WAR"
    k = contestants.size() % 4; // find how many players are lucky
    for (i = 0; i < k; i++)
    {
        do
        {
            contestantID = rand() % 99 + 1; // generate a random ID of the contestants
        } while (contestants[contestantID - 1].wildcard == true);
        contestants[contestantID - 1].wildcard = true;
    }
    k = (int)contestants.size() / 4; // theoretical number of contestants in a team
    for (i = 0; i < 4; i++)
    {
        j = 0; // practical number of contestants in a team
        while (j < k)
        {
            do
            {
                contestantID = rand() % 50 + 1;                 // generate a random ID of the contestants
            } while (contestants[contestantID - 1].team != -1); // test if the contestant has already a team
            contestants[contestantID - 1].team = i;             // assign contestant to the team
            j++;                                                // increment the number of contestants of the team
        }
    }

    return 0;
}
