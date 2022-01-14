#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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
    Player() {}
    Player(string n, string s, string c, long int d, int w)
    {
        this->name = n;
        this->surname = s;
        this->city = c;
        this->debt = d;
        this->weigth = w;
    }
    ~Player() {}
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

int rps(int player1, int player2) // rock/paper/scissors function needed in genken mini-game
{
    if (player1 == 1 && player2 == 2)
    {
        return player2;
    }
    else if (player1 == 2 && player2 == 3)
    {
        return player2;
    }
    else if (player1 == 3 && player2 == 1)
    {
        return player2;
    }
    else if (player1 == 1 && player2 == 3)
    {
        return player1;
    }
    else if (player1 == 2 && player2 == 1)
    {
        return player1;
    }
    else if (player1 == 3 && player2 == 2)
    {
        return player1;
    }
    else
        return 0;
}

int main()
{
    vector<Contestant> contestants;
    vector<Supervisor> supervisors;
    Supervisor aux;
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
         << "Weight "
         << "Mask"
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

    // calculate the total debt of the contestants
    int totalDebt;
    for (i = 0; i < contestants.size(); i++)
        totalDebt += contestants[i].debt;

    // calculate the sum which supervisor could get
    for (i = 0; i < 9; i++)
    {
        supervisors[i].debt *= (-1);
        for (j = 0; j < 11; j++)
            supervisors[i].debt += contestants[supervisors[i].getContestants()[j]].debt;
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
            contestantID = rand() % contestants.size() + 1; // generate a random ID of the contestants
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
                contestantID = rand() % contestants.size() + 1;                                                   // generate a random ID of the contestants
            } while (contestants[contestantID - 1].team != -1 || contestants[contestantID - 1].wildcard == true); // test if the contestant has already a team
            contestants[contestantID - 1].team = i;                                                               // assign contestant to the team
            j++;                                                                                                  // increment the number of contestants of the team
        }
    }

    cout << endl;
    // code to test the composition of the teams
    for (i = 0; i < 4; i++)
    {
        cout << "Team " << i + 1 << ": ";
        for (j = 0; j < contestants.size(); j++)
            if (contestants[j].team == i)
                cout << contestants[j].number << " ";
        cout << endl;
    }
    cout << "Lucky players: ";
    for (j = 0; j < contestants.size(); j++)
        if (contestants[j].wildcard == true)
            cout << contestants[j].number << " ";
    cout << endl;

    // calculate the weigths of each team
    int team1Weigth = 0, team2Weigth = 0, team3Weigth = 0, team4Weigth = 0, winner1, winner2, winnerWeigth1, winnerWeigth2;
    for (i = 0; i < contestants.size(); i++)
        switch (contestants[i].team) // add each player's weigth to his team's total weigth
        {
        case 0:
            team1Weigth += contestants[i].weigth;
            break;
        case 1:
            team2Weigth += contestants[i].weigth;
            break;
        case 2:
            team3Weigth += contestants[i].weigth;
            break;
        case 3:
            team4Weigth += contestants[i].weigth;
            break;
        default:
            break;
        }

    cout << "Team 1 weigth: " << team1Weigth << endl;
    cout << "Team 2 weigth: " << team2Weigth << endl;
    cout << "Team 3 weigth: " << team3Weigth << endl;
    cout << "Team 4 weigth: " << team4Weigth << endl;

    // team 1 vs team 2
    if (team1Weigth < team2Weigth)
    {
        winner1 = 1;                             // save the index of winning team
        winnerWeigth1 = team2Weigth;             // save the weigth of winning team
        for (i = 0; i < contestants.size(); i++) // remove the contestants of the losing team
            if (contestants[i].team == 0)
                contestants.erase(contestants.begin() + i);
    }
    else
    {
        winner1 = 0;
        winnerWeigth1 = team1Weigth;
        for (i = 0; i < contestants.size(); i++)
            if (contestants[i].team == 1)
                contestants.erase(contestants.begin() + i);
    }

    // team 3 vs team 4
    if (team3Weigth < team4Weigth)
    {
        winner2 = 3;
        winnerWeigth2 = team4Weigth;
        for (i = 0; i < contestants.size(); i++)
            if (contestants[i].team == 2)
                contestants.erase(contestants.begin() + i);
    }
    else
    {
        winner2 = 2;
        winnerWeigth2 = team3Weigth;
        for (i = 0; i < contestants.size(); i++)
            if (contestants[i].team == 3)
                contestants.erase(contestants.begin() + i);
    }

    // winner team 1 vs winner team 2
    if (winnerWeigth1 < winnerWeigth2)
    {
        for (i = 0; i < contestants.size(); i++)
            if (contestants[i].team == winner1)
                contestants.erase(contestants.begin() + i);
    }
    else
    {
        for (i = 0; i < contestants.size(); i++)
            if (contestants[i].team == winner2)
                contestants.erase(contestants.begin() + i);
    }

    /*  // another method which returns the same result
        int winnerWeigth, winnerTeam;

        // calculate the maximum weigth
        winnerWeigth1 = max(team1Weigth, team2Weigth);
        winnerWeigth2 = max(team3Weigth, team4Weigth);
        winnerWeigth = max(winnerWeigth1, winnerWeigth2);

        // find the team which has the maximum weigth
        if (winnerWeigth == team1Weigth)
            winnerTeam = 0;
        else if (winnerWeigth == team2Weigth)
            winnerTeam = 1;
        else if (winnerWeigth == team3Weigth)
            winnerTeam = 2;
        else
            winnerTeam = 3;

        for (i = 0; i < contestants.size(); i++) // remove the contestants who don't belong to the winning team
            if (contestants[i].team != winnerTeam)
                contestants.erase(contestants.begin() + i);
     */

    // print the remaining contestants after second round
    cout
        << endl
        << "CONTESTANTS AFTER SECOND ROUND"
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

    for (i = 0; i < contestants.size() && contestants.size() > 14; i++) // remove some contestants
        contestants.erase(contestants.begin() + i);

    // print the remaining contestants after second round
    cout
        << endl
        << "CONTESTANTS AFTER SECOND ROUND"
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

    // cancel the previous teams
    for (i = 0; i < contestants.size(); i++)
    {
        contestants[i].team = -1;
        contestants[i].wildcard = false;
    }

    // THIRD GAME: "MARBLES"
    k = (int)contestants.size() / 2; // theoretical number of teams
    for (i = 0; i < k; i++)
    {
        j = 0; // practical number of contestants in a team
        while (j < 2)
        {
            do
            {
                contestantID = rand() % contestants.size() + 1;                                                   // generate a random ID of the contestants
            } while (contestants[contestantID - 1].team != -1 || contestants[contestantID - 1].wildcard == true); // test if the contestant has already a team
            contestants[contestantID - 1].team = i;                                                               // assign contestant to the team
            j++;                                                                                                  // increment the number of contestants of the team
        }
    }
    int random1, random2;
    for (i = 0; i < contestants.size() - 1; i++) // iterate through contestants
    {
        for (j = i + 1; j < contestants.size(); j++)        // iterate through contestants
            if (contestants[i].team == contestants[j].team) // check if the two contestants have the same team
            {
            marbles:
                try
                {
                    random1 = rand() % 999 + 1; // generate a random number for first contestant
                    random2 = rand() % 999 + 1; // generate a random number for second contestant
                    if (random1 < random2)      // compare the generated numbers
                    {
                        contestants.erase(contestants.begin() + j);
                        break;
                    }
                    else if (random2 < random1)
                    {
                        contestants.erase(contestants.begin() + i);
                        i--;
                        break;
                    }
                    else
                        throw "Generated values are equal!";
                }
                catch (string s)
                {
                    goto marbles;
                }
            }
    }

    // print the remaining contestants after third round
    cout
        << endl
        << "CONTESTANTS AFTER THIRD ROUND"
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

    // cancel the previous teams
    for (i = 0; i < contestants.size(); i++)
    {
        contestants[i].team = -1;
    }

    // LAST GAME: "GENKEN"
    k = contestants.size() % 2; // find how many players are lucky
    for (i = 0; i < k; i++)
    {
        do
        {
            contestantID = rand() % contestants.size() + 1; // generate a random ID of the contestants
        } while (contestants[contestantID - 1].wildcard == true);
        contestants[contestantID - 1].wildcard = true;
    }
    k = (int)contestants.size() / 2; // theoretical number of teams
    for (i = 0; i < k; i++)
    {
        j = 0; // practical number of teams
        while (j < 2)
        {
            do
            {
                contestantID = rand() % contestants.size() + 1; // generate a random ID of the contestants
            } while (contestants[contestantID - 1].team != -1); // test if the contestant has already a team
            contestants[contestantID - 1].team = i;             // assign contestant to the team
            j++;                                                // increment the number of contestants of the team
        }
    }

    for (i = 0; i < contestants.size() - 1; i++) // iterate through contestants
    {
        for (j = i + 1; j < contestants.size(); j++)        // iterate through contestants
            if (contestants[i].team == contestants[j].team) // check if the two contestants have the same team
            {
            genken1:
                try
                {
                    random1 = rand() % 3 + 1; // generate a random number for first contestant
                    random2 = rand() % 3 + 1; // generate a random number for second contestant

                    if (rps(random1, random2) == random1) // compare the generated numbers
                    {
                        contestants.erase(contestants.begin() + j);
                        break;
                    }
                    else if (rps(random1, random2) == random2)
                    {
                        contestants.erase(contestants.begin() + i);
                        i--;
                        break;
                    }
                    else
                        throw 1;
                }
                catch (int s)
                {
                    goto genken1;
                }
            }
    }

    // cancel the previous teams
    for (i = 0; i < contestants.size(); i++)
    {
        contestants[i].team = -1;
    }
    k = (int)contestants.size() / 2; // theoretical number of teams
    for (i = 0; i < k; i++)
    {
        j = 0; // practical number of teams
        while (j < 2)
        {
            do
            {
                contestantID = rand() % contestants.size() + 1; // generate a random ID of the contestants
            } while (contestants[contestantID - 1].team != -1); // test if the contestant has already a team
            contestants[contestantID - 1].team = i;             // assign contestant to the team
            j++;                                                // increment the number of contestants of the team
        }
    }

    for (i = 0; i < contestants.size() - 1; i++) // iterate through contestants
    {
        for (j = i + 1; j < contestants.size(); j++)        // iterate through contestants
            if (contestants[i].team == contestants[j].team) // check if the two contestants have the same team
            {
            genken2:
                try
                {
                    random1 = rand() % 3 + 1; // generate a random number for first contestant
                    random2 = rand() % 3 + 1; // generate a random number for second contestant

                    if (rps(random1, random2) == random1) // compare the generated numbers
                    {
                        contestants.erase(contestants.begin() + j);
                        break;
                    }
                    else if (rps(random1, random2) == random2)
                    {
                        contestants.erase(contestants.begin() + i);
                        i--;
                        break;
                    }
                    else
                        throw 1;
                }
                catch (int s)
                {
                    goto genken2;
                }
            }
    }

genken3:
    try
    {
        random1 = rand() % 3 + 1; // generate a random number for first contestant
        random2 = rand() % 3 + 1; // generate a random number for second contestant

        if (rps(random1, random2) == random1) // compare the generated numbers
        {
            contestants.erase(contestants.begin() + 1);
        }
        else if (rps(random1, random2) == random2)
        {
            contestants.erase(contestants.begin() + 0);
        }
        else
            throw 1;
    }
    catch (int s)
    {
        goto genken3;
    }

    // print the winning contestant
    cout
        << endl
        << "WINNER"
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

    cout << "The winner won " << totalDebt << endl; // print the sum won by the winner

    supervisors[contestants[0].getSupervisor()].debt = contestants[0].debt * 10; // calculate the sum won by the supervisor of the winner

    // order the supervisors by the sum won
    for (i = 0; i < 8; i++)
        for (j = i + 1; j < 9; j++)
            if (supervisors[i].debt < supervisors[j].debt)
            {
                aux = supervisors[i];
                supervisors[i] = supervisors[j];
                supervisors[j] = aux;
            }
    // print the supervisors and the sum won by each
    cout << endl
         << "SUPERVISORS"
         << endl
         << "Name "
         << "Surname "
         << "City "
         << "Weight "
         << "Mask"
         << "Won "
         << endl;
    for (i = 0; i < 9; i++)
        cout << supervisors[i].name << " " << supervisors[i].surname << " " << supervisors[i].city << " " << supervisors[i].weigth << " " << supervisors[i].getMask() << " " << supervisors[i].debt << endl;

    int teamRectangle = 0, teamTriangle = 0, teamCircle = 0;
    for (i = 0; i < 9; i++) // calculate the sum won by each team of supervisors
    {
        if (supervisors[i].mask == "rectangle")
            teamRectangle += supervisors[i].debt;
        else if (supervisors[i].mask == "triangle")
            teamTriangle += supervisors[i].debt;
        else
            teamCircle += supervisors[i].debt;
    }

    k = max(max(teamRectangle, teamTriangle), teamCircle); // calculate which team won the biggest sum
    // print which team won the biggest sum
    if (k == teamRectangle)
        cout << "Team Rectangle won the biggest sum." << endl;
    else if (k == teamTriangle)
        cout << "Team Triangle won the biggest sum." << endl;
    else if (k == teamCircle)
        cout << "Team Circle won the biggest sum." << endl;

    return 0;
}
