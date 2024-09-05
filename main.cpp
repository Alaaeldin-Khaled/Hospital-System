#include <iostream>
using namespace std;

const int specializations = 21;
const int spots = 6;
string queue[specializations][spots];
int spots_counter[specializations] = {0};
bool statuses[specializations][spots];

int menu()
{
    int choice;
    while (true)
    {
        cout << "Enter you choice: \n";
        cout << "1) Add new patient\n";
        cout << "2) Print all patients\n";
        cout << "3) Get next patient\n";
        cout << "4) Exit\n\n\t";

        cin >> choice;

        if (choice <= 4 && choice >= 1)
            break;
        else
            cout << "Invalid input\n";
    }
    return choice;
}

bool is_full(int specialization)
{
    return queue[specialization][spots - 1] != "";
}

void add_to_begin(string name, int specialization, bool status)
{
    for (int spot = spots - 1; spot > 1; --spot)
    {
        queue[specialization][spot] = queue[specialization][spot - 1];
        statuses[specialization][spot] = statuses[specialization][spot - 1];
    }

    queue[specialization][1] = name;
    statuses[specialization][1] = status;
}

void add_to_end(string name, int specialization, bool status)
{
    for (int i = 1; i < spots; ++i)
    {
        if (queue[specialization][i] == "")
        {
            queue[specialization][i] = name;
            statuses[specialization][i] = status;
            break;
        }
    }
}

void add_patient()
{
    cout << "\n*******************************************\n\n";
    int specialization, status;
    string name;

    cout << "Enter specialization, name, status: ";
    cin >> specialization >> name >> status;

    if (is_full(specialization))
    {
        cout << "Sorry can't add more patients for this specialization.\n";
    }
    else
    {
        if (status == 0)
        {
            add_to_end(name, specialization, status);
        }
        else
        {
            add_to_begin(name, specialization, status);
        }
        spots_counter[specialization]++;
    }

    cout << endl << endl;
}

void print_patients()
{
    cout << "\n*******************************************\n\n";
    for (int i = 1; i < specializations; ++i)
    {
        if (spots_counter[i] == 0)
            continue;
        cout << "There are " << spots_counter[i] << " patients in specialization " << i << ":\n\n";
        for (int j = 1; j < spots; ++j)
        {
            if (queue[i][j] == "")
                break;

            string cur_status;

            statuses[i][j] == 0 ? (cur_status = "regular") : (cur_status = "urgent");

            cout << queue[i][j] << " " << cur_status << endl;

        }
        cout << endl;
    }
    cout << endl << endl;
}

void get_next_patient()
{
    cout << "\n*******************************************\n\n";

    int specialization;
    cout << "Enter specialization: ";
    cin >> specialization;

    cout << "\n\n";

    if (spots_counter[specialization] != 0)
    {
        cout << queue[specialization][1] << " please go with the doctor";

        --spots_counter[specialization];

        int spot = 1;
        for (; spot <= spots - 1; ++spot)
        {
            if (queue[specialization][spot + 1] != "")
            {
                queue[specialization][spot] = queue[specialization][spot + 1];
                statuses[specialization][spot] = statuses[specialization][spot + 1];
            }
            else
            {
                queue[specialization][spot] = "";
                statuses[specialization][spot] = 0;
                break;
            }
        }

    }
    else
    {
        cout << "No patients in specialization " << specialization;
    }

    cout << endl << endl;
}

void hospital_system()
{
    while (true)
    {
        int choice = menu();
        if (choice == 1)
            add_patient();
        else if (choice == 2)
            print_patients();
        else if (choice == 3)
            get_next_patient();
        else if (choice == 4)
            break;
    }
}

int main()
{
    hospital_system();

    return 0;
}
