// Bank Project

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <conio.h> 

using namespace std;
enum enMenue { ShowClient = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Exit = 6 };

void GoTomainMenue();
void ProgramOption(enMenue Choice);

const string FileName = "Clients.txt";
struct stClients
{
    string AccountNumber;
    string PinCode;
    string ClientName;
    string PhoneNumber;
    double balance;
    bool MarkForDelete = false;
};

enMenue ReadMenueChoice()
{
    int Choice;
    do {
        cout << "Choose What Do You Want To Do ? [1 To 6]?";
        cin >> Choice;
    } while (Choice < 1 || Choice>6);
    return (enMenue)Choice;
}

vector<string>SplitString(string S1, string delim="#//#")
{
   
    vector<string>vString;
    string Word="";
    short Pos;
    
    while ((Pos = S1.find(delim)) != string::npos)
    {
            Word = S1.substr(0, Pos);
            if (Word != "")
            {
                vString.push_back(Word);
            }
            S1.erase(0, Pos + delim.length());
        }
        if (S1 != "")
        {
            vString.push_back(S1);
        }
    
    return vString;
}
stClients ConvertLineToStruct(string S1, string Separator = "#//#")
{
    stClients Client;
    vector<string>vString = SplitString(S1, Separator);
    Client.AccountNumber = vString[0];
    Client.PinCode = vString[1];
    Client.ClientName = vString[2];
    Client.PhoneNumber = vString[3];
    Client.balance =stod( vString[4]);
    return Client;

}
string ConvertStructToLine(stClients Clients, string Separator = "#//#")
{
    string Line="";
    Line += Clients.AccountNumber + Separator;
    Line += Clients.PinCode + Separator;
    Line += Clients.ClientName + Separator;
    Line += Clients.PhoneNumber + Separator;
    Line += to_string(Clients.balance);
    return Line;
}
vector<stClients>LoadClientDataFromFileToVector(string FileName)
{
    fstream MyFile;
    vector<stClients>vClients;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stClients Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToStruct(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;

}

void SaveClientdatatoFile(string FileName, vector<stClients> &vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out );
    if (MyFile.is_open())
    {
        string line;
        for (stClients& C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                line = ConvertStructToLine(C);
                MyFile << line<<endl;
            }
        }
        MyFile.close();
    }
}
bool SearchByAccountNumber(string AccountNumberToSearch,stClients &Client)
{
    vector<stClients>vClients;

    vClients = LoadClientDataFromFileToVector(FileName);
    for (stClients C : vClients)
    {
        if (C.AccountNumber == AccountNumberToSearch)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

stClients AddNewClient()
{
    stClients Client;
    cout << "Add new Client :\n";
    cout << "Please Enter Account Number:\n";
    getline(cin >> ws, Client.AccountNumber);
    cout << "Please Enter Pin Code:\n";
    getline(cin , Client.PinCode);
    cout << "Please Enter Name:\n";
    getline(cin , Client.ClientName);
    cout << "Please Enter Phone Number:\n";
    getline(cin, Client.PhoneNumber);
    cout << "Please Enter balance :\n";
    cin >> Client.balance;
    return Client;
}
stClients UpdateClientDetails(string AccountNumber)
{
    stClients Client;
    Client.AccountNumber = AccountNumber;
    cout << "Please Enter Pin Code:\n";
    getline(cin>>ws, Client.PinCode);
    cout << "Please Enter Name:\n";
    getline(cin, Client.ClientName);
    cout << "Please Enter Phone Number:\n";
    getline(cin, Client.PhoneNumber);
    cout << "Please Enter balance :\n";
    cin >> Client.balance;
    return Client;
}
bool MarkForDelte(vector<stClients>&vClients,string AccountNumberToSearch)
{
    for (stClients& C : vClients)
    {
        if (C.AccountNumber == AccountNumberToSearch)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

void PressAnyKeyToRestart() {
    cout << "\nPress Any Key To Go Back To Main Menue....";
    system("pause>0");
   
}
void mainScreen()
{
    
        system("cls"); 
        system("color 0F");

        cout << "===========================================\n"; 
        cout << "\t\tMain Menue Screen\n";  
        cout << "===========================================\n";  
        cout << "\t[1] Show Client List.\n";    
        cout << "\t[2] Add New Client.\n";   
        cout << "\t[3] Delete Client.\n";    
        cout << "\t[4] Update Client Info.\n"; 
        cout << "\t[5] Find Client.\n";     
        cout << "\t[6] Exit.\n";   
        cout << "===========================================\n";
        ProgramOption(ReadMenueChoice());

}
void ShowClientScreen()
{
    cout << "\n---------------------------------------\n";
    cout << "\tShow Client Screen\n";
    cout << "---------------------------------------\n";

}
void AddNewClientScreen()
{
    cout << "\n---------------------------------------\n";
    cout << "\tAdd New Client Screen\n";
    cout << "---------------------------------------\n";

}
void DeleteClientScreen()
{
    cout << "\n---------------------------------------\n";
    cout << "\tDelete Client Screen\n";
    cout << "---------------------------------------\n";

}
void UpdateClientScreen()
{
    cout << "\n---------------------------------------\n";
    cout << "\tUpdate Client Screen\n";
    cout << "---------------------------------------\n";

}
void FindScreen()
{
    cout << "\n---------------------------------------\n";
    cout << "\t\tFind Clinet Screen\n";
    cout << "---------------------------------------\n";

}
void EndScreen()
{
    cout << "\n---------------------------------------\n";
    cout << "\t\tProgram End:-)\n";
    cout << "---------------------------------------\n";

}
void ClearScreen()
{
    system("cls");
}
void PrintClientCard(stClients Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccount Number : " << Client.AccountNumber;
    cout << "\nPin Code       : " << Client.PinCode;
    cout << "\nName           : " << Client.ClientName;
    cout << "\nPhone          : " << Client.PhoneNumber;
    cout << "\nAccount Balance: " << Client.balance;
}
void PrintClientDetails(stClients Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.ClientName;
    cout << "| " << setw(12) << left << Client.PhoneNumber;
    cout << "| " << setw(12) << left << Client.balance;
}
void FinalShowClients()
{
    vector<stClients>vClients;
    vClients = LoadClientDataFromFileToVector(FileName);
    ClearScreen();
    system("color 0F");

    ShowClientScreen();
    cout << "\n\t\t\t\t\tClient List  Has (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stClients Client : vClients)
    {
        PrintClientDetails(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
stClients CheckAndAddnewClient(string AccountNumber)
{
    stClients Client;
    while(SearchByAccountNumber(AccountNumber, Client))
    {
        cout << "Account Number Has Already Exist [ " << AccountNumber << " ] Please Enter Another Account Number?";
        getline(cin >> ws, AccountNumber);
    }
    Client = UpdateClientDetails(AccountNumber);
    return Client;

}
string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void FinalAddNewClient()
{
    char AddMore = 'y';
    vector<stClients> vClients;
    stClients Client;
    string AccountNumber;

    vClients = LoadClientDataFromFileToVector(FileName);

    do
    {
        ClearScreen();
        system("color 0F");

        AddNewClientScreen();
        cout << "Adding New Client : \n";
        AccountNumber = ReadClientAccountNumber();

       
        Client = CheckAndAddnewClient(AccountNumber);
        vClients.push_back(Client);

        SaveClientdatatoFile(FileName, vClients);

        cout << "Client Added Successfully. Do You Want To Add More Clients [y/n]? ";
        cin >> AddMore;

    } while (AddMore == 'y' || AddMore == 'Y');
}
char AreYouSureYouWantToDelete()
{
    char DeleteAccount = 'n';
    cout << "\nAre You Sure You Want To Delete This Account [Y/N] ? ";
    cin >> DeleteAccount;
    return DeleteAccount;
}
char AreYouSureYouWantToUpdate()
{
    char DeleteAccount = 'n';
    cout << "\nAre You Sure You Want To Update This Account [Y/N] ? ";
    cin >> DeleteAccount;
    return DeleteAccount;
}
void FinalDeleteClient()
{
    
    vector<stClients>vClient = LoadClientDataFromFileToVector(FileName);
    string AccountNumber;
    stClients Client;
    char DeleteMore;

    do {
        ClearScreen();
        system("color 0F");
        DeleteClientScreen();
        AccountNumber = ReadClientAccountNumber();
        if (SearchByAccountNumber(AccountNumber, Client))
        {
            char deleteClient = 'y';
            
            PrintClientCard(Client);
            deleteClient = AreYouSureYouWantToDelete();
            if (deleteClient == 'y' || deleteClient == 'Y')
            {
                MarkForDelte(vClient, AccountNumber);
                SaveClientdatatoFile(FileName, vClient);
                vClient= LoadClientDataFromFileToVector(FileName);
                cout << "Client Deleted Succesfully ..\n";
            }
            else
            {
                cout << "You Choise Not To Deleted This Client Information \n";
               
            }
           
        }
        else {
            cout << "This Client Account Number Is Not Exist In Our System !!\n";
            
        }
        cout << "Do You Want To Delete Another Client [Y/N]?";
        cin >>ws>> DeleteMore;
    } while (DeleteMore == 'y' || DeleteMore == 'Y');

}
void FinalUpdateClientInfo()
{
    vector<stClients>vClients= LoadClientDataFromFileToVector(FileName);;
    stClients Client;
    string AccountNumber;
    char UpdateMore;
    do
    {
         ClearScreen();
         system("color 0F");

         UpdateClientScreen();

        AccountNumber = ReadClientAccountNumber();
        if (SearchByAccountNumber(AccountNumber, Client))
        {
            char UpdateClient;
            PrintClientCard(Client);
            UpdateClient = AreYouSureYouWantToUpdate();
            if (UpdateClient == 'y' || UpdateClient == 'Y')
            {
                
                for (stClients& C : vClients)
                {
                    if (C.AccountNumber == AccountNumber)
                    {
                       C= UpdateClientDetails(AccountNumber);
                       break;
                    }
                }
                SaveClientdatatoFile(FileName, vClients);

                cout << "Client Updated Succesfully ...\n";
            }
            else
            {
                cout << "\nYou Choice Not To Update This Client And It Will Be As Iw Was ....\n";
                cout << "\nThis Is Client Details TO Review It Again  ....\n";

                PrintClientCard(Client);
            }

        }
        else
        {
            cout << "This Account Number [ " << AccountNumber << " ] Is Not Exist In Our System !! \n";
        }
        cout << "\nDo You Want To Update Any Client Else [Y/N] ?";
        cin >> UpdateMore;

    } while (UpdateMore == 'y' || UpdateMore == 'Y');
}
bool CheckPasswordCorrectOrNot(stClients Client,string Password)
{
  
    if (Client.PinCode == Password)
    {
        cout << "Correct Password And This Is Your Details .\n";
            return true;
    }
    else
    {
       
        return false;
    }
}
void FinalFindClient()
{
    vector <stClients>vClients= LoadClientDataFromFileToVector(FileName);
     
    stClients Client;
    string AccountNumber;
    string CheckPassword;
    char FindMore;
    do
    {
        bool AccessGranted = false;

        ClearScreen();
        system("color 0F");
        FindScreen();
        AccountNumber = ReadClientAccountNumber();
        if (SearchByAccountNumber(AccountNumber, Client))
        {
            cout << "\nThe Account Has Existed Please Enter Password To Show Your Details ? ";
            cin >> CheckPassword;
            int Counter = 0;

            while (Counter < 3)
            {

                if (CheckPasswordCorrectOrNot(Client, CheckPassword))
                {
                    system("color 2F");
                    PrintClientCard(Client);
                    AccessGranted = true;
                    break;
                }
                else
                {
                    Counter++;
                    cout << "Incorrect Password !!!!!!\n";
                    system("color 4F");
                    if (Counter < 3)
                    {
                        cout << "You Have ( " << 3 - Counter << ") More Please Try Again ? ";
                        cin >> CheckPassword;
                    }

                    
                }
            }
            if (!AccessGranted)
            {
                cout << "\nYou entered wrong password 3 times. Access Denied!\n";
            }

        }
        else
        {
            cout << "Client With Account Number [ " << AccountNumber << " ] Has Not Exist In Our System \n ";
        }
        
        
        
        cout << "\nDo You Want To Find Any Client Else [Y/N] ?";
        cin >> FindMore;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  



    } while (FindMore == 'y' || FindMore == 'Y');
}
void FinalEndProgram()
{
    ClearScreen();
    system("color 0F");

    EndScreen();
    system("pause>0");
}
void ProgramOption(enMenue Choice)
{
    switch (Choice)
    {
    case enMenue::AddClient:
    {
        FinalAddNewClient();
        GoTomainMenue();

        break;
    }
    case enMenue::ShowClient:
    {
        FinalShowClients();
        GoTomainMenue();

        break;
    }
    case enMenue::DeleteClient:
    {
        FinalDeleteClient();
        GoTomainMenue();

        break;
    }
    case enMenue::UpdateClient:
    {
        FinalUpdateClientInfo();
        GoTomainMenue();

        break;
    }
    case enMenue::FindClient:
    {
        FinalFindClient();
        GoTomainMenue();
        break;
    }
    case enMenue::Exit:
    {
        FinalEndProgram();
        break;
    }

    }
}
void FinalMainMenueScreen()
{
    ClearScreen();
    mainScreen();
}
void GoTomainMenue()
{
    PressAnyKeyToRestart();
    FinalMainMenueScreen();

}
void Startprogram()
{
    ClearScreen();
    FinalMainMenueScreen();


}

int main()
{

    Startprogram();


return 0;
}

