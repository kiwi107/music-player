#include <iostream>
#include <conio.h>
#include <cstring>
#include <string>
#include <dirent.h>
#include <windows.h>
#include <MMsystem.h>
#include <cmath>
#pragma comment(lib, "Winmm.lib") // linking this library for playsound function to work
using namespace std;

struct users
{
    char username[20];
    char password[20];
    char folder[100];
};

bool printfolder(char location[], int *dirptr, string directories[]);
void songpath(char folderpath[], char songname[], char userpath[], char modifiedsongname[]);
void PlaySong(char chartype[], char songname[]);
void CopySong(char frompath[], char topath[], char copysong[]);
void DeleteSong(char deletepath[], char deletename[]);

int main()
{
    char *password = new char[20];
    char temp;
    char *username = new char[20];
    users *member = new users[10];

    member[0] = {"karim", "1234", ".\\kiwi"};
    member[1] = {"ezz", "123", ".\\ezz"};
    member[2] = {"omar", "12345", ".\\korkor"};
    member[3] = {"abdulrahman", "12", ".\\abdulrahman"};
    member[4] = {"ali", "1", ".\\ali"};

    int i; // this i is seen by all the code because it represents which user is logged in
    string *directories = new string[20];
    int directorysize = 0; // count the non-blank elements of array
    string status;

    cout << "Enter username: ";
    cin.getline(username, 20, '\n');
    cout << "Enter passcode: ";

    while (status != "logged in")
    {

        int d = 0;
        while (true) // password input as asterisk
        {
            temp = _getch();                                                                                           // getch() make theentered character not show up on the console and instead we added an asterik everytime the user input.
            if ((temp >= 97 && temp <= 122) || (temp >= 65 && temp <= 90) || (temp >= 48 && temp <= 57) || temp == 32) // limit to uppercase, lowercase, numbers and space
            {
                password[d] = temp;
                d++;
                cout << "*";
            }
            if (temp == '\b' && d >= 1) // backspace to delete characters

            {
                cout << "\b \b";
                d--;
            }
            if (temp == '\r') // enter to break out of the loop
            {
                password[d] = '\0';
                break;
            }
        }
        cout << endl;
        for (i = 0; i < 6; i++)
        {
            if (strcmp(username, member[i].username) == 0 && strcmp(password, member[i].password) == 0) // comparing input with values stored in struct
            {
                status = "logged in";
                system("cls");
                cout << endl;
                cout << "Logged in successfully, Welcome back " << member[i].username << endl;
                cout << endl;

                cout << "Here is your playlist:" << endl;
                cout << endl;
                printfolder(member[i].folder, &directorysize, directories);

                break;
            }
            else
            {
                status = "not logged in";
            }
        }
        if (status != "logged in")
        {
            system("cls");
            cout << "Error occurred while logging in" << endl;
            cout << endl;
            cout << "Check username and password and try again" << endl;
            cout << endl;
            cout << "Enter username: ";
            cin.getline(username, 10, '\n');
            cout << "Enter passcode: ";
        }
    }
    // after logging in

    if (status == "logged in")
    {
        char *songname = new char[50];
        int playlistaction;

        cout << endl;
        cout << "PLAYLIST ACTIONS MENU" << endl;
        cout << "Type desired action number:" << endl;
        cout << "1: Play song" << endl;
        cout << "2: Add song" << endl;
        cout << "3: Delete song" << endl;
        cout << "4: Exit" << endl;
        cout << endl;
        cout << "Choice number: ";
        cin >> playlistaction;

        while (playlistaction != 4) // 4 will exit
        {
            system("cls");

            if (playlistaction == 1) // play song
            {
                cout << endl;
                cout << "Inside PLAY SONG" << endl;
                cout << endl;
                cout << "Here is your playlist: " << endl;
                cout << endl;
                printfolder(member[i].folder, &directorysize, directories);

                cout << "Enter the song name you want to play" << endl;
                cout << "-must type extenstion" << endl;
                cout << "-it is case sensetive" << endl;
                cout << endl;
                cout << "songname: ";
                cin.ignore();
                cin.getline(songname, 100, '\n');

                string stringsongname(songname); // converting char array to string because we stored the directory content in a string array (to compare must be same type)

                int songaction;
                bool found = false;
                for (int r = 0; r < directorysize; r++)
                {
                    if (directories[r] == songname) // searching if the song is found in the opened directory
                    {
                        found = true;
                        char modifiedsongname[50];
                        char userpath[50];
                        songpath(member[i].folder, songname, userpath, modifiedsongname);
                        strcat_s(userpath, modifiedsongname);

                        system("cls");
                        PlaySong(userpath, songname);
                        cout << "Here is your playlist: " << endl;
                        cout << endl;
                        printfolder(member[i].folder, &directorysize, directories);

                        cout << "SONG ACTIONS MENU" << endl;
                        cout << "Type desired action number" << endl;
                        cout << "1: Next track" << endl;
                        cout << "2: Previous track" << endl;
                        cout << "3: Repeat" << endl;
                        cout << "4: Pause" << endl;
                        cout << "5: Change volume" << endl;
                        cout << "6: Back (to get to the previous page)" << endl;
                        cout << endl;
                        cout << "Choice number: ";

                        cin >> songaction;
                        while (true)
                        {
                            if (songaction == 1) // next
                            {

                                for (int k = 0; k <= directorysize; k++)
                                {

                                    if (directories[k] == stringsongname) // searching for the song order in folder
                                    {
                                        while (k == directorysize - 1) // to make it loop from the begining if the last song is reached
                                        {
                                            k = -1; //-1 not 0 bec we will add one at the next line
                                        }
                                        stringsongname = directories[k + 1];

                                        char nextpath[100];
                                        char nextsong[30];

                                        char charsongname[30];

                                        for (int c = 0; c < stringsongname.length() + 1; c++) // converting the strings back to char to be accepted by songpath function
                                        {
                                            charsongname[c] = stringsongname[c];
                                        }

                                        songpath(member[i].folder, charsongname, nextpath, nextsong);

                                        strcat_s(nextpath, nextsong);

                                        system("cls");
                                        PlaySong(nextpath, charsongname);

                                        cout << "Here is your playlist: " << endl;
                                        cout << endl;
                                        printfolder(member[i].folder, &directorysize, directories);

                                        break;
                                    }
                                }
                            }

                            else if (songaction == 3) // repeat
                            {
                                for (int k = 0; k < sizeof(directories); k++)
                                {
                                    if (directories[k] == stringsongname)
                                    {

                                        char repeatpath[100];
                                        char repeatsong[30];

                                        char charsongname[30];

                                        for (int c = 0; c < stringsongname.length() + 1; c++) // converting the strings back to char to be accepted by songpath function
                                        {
                                            charsongname[c] = stringsongname[c];
                                        }

                                        songpath(member[i].folder, charsongname, repeatpath, repeatsong);

                                        strcat_s(repeatpath, repeatsong);

                                        system("cls");
                                        PlaySong(repeatpath, charsongname);

                                        cout << "Here is your playlist: " << endl;
                                        cout << endl;
                                        printfolder(member[i].folder, &directorysize, directories);
                                        break;
                                    }
                                }
                            }
                            else if (songaction == 2) // previous
                            {
                                for (int k = 0; k <= directorysize; k++)
                                {
                                    if (directories[k] == stringsongname) // searching for the song order
                                    {
                                        while (k == 0) // to make it loop from the end if the first song is reached
                                        {
                                            k = directorysize;
                                        }
                                        stringsongname = directories[k - 1];

                                        char previouspath[100];
                                        char previoussong[30];
                                        char charsongname[30];

                                        for (int c = 0; c < stringsongname.length() + 1; c++) // converting the strings back to char to be accepted by songpath function
                                        {
                                            charsongname[c] = stringsongname[c];
                                        }

                                        songpath(member[i].folder, charsongname, previouspath, previoussong);

                                        strcat_s(previouspath, previoussong);

                                        system("cls");
                                        PlaySong(previouspath, charsongname);

                                        cout << "Here is your playlist: " << endl;
                                        cout << endl;
                                        printfolder(member[i].folder, &directorysize, directories);
                                        break;
                                    }
                                }
                            }
                            else if (songaction == 5) // change volume
                            {

                                DWORD current_volume;
                                // getts the current volume
                                waveOutGetVolume(NULL, &current_volume);

                                // converts the current volume to an equivalent number from 0 to 10
                                int equivalent_volume = (int)round(((current_volume & 0x0000FFFF) / (double)0xFFFF) * 10);
                                cout << endl;
                                cout << "Current volume: " << equivalent_volume << endl;

                                int volume;
                                cout << "Enter the volume level from range 0 (lowest) to 10 (highest) : ";
                                cin >> volume;
                                while (true)
                                {
                                    if (volume > 10 || volume < 0)
                                    {
                                        system("cls");
                                        cout << endl;
                                        cout << volume << " is out of range, volume range is from 0 to 10" << endl;
                                        cout << endl;
                                        cout << "Here is your playlist: " << endl;
                                        cout << endl;
                                        printfolder(member[i].folder, &directorysize, directories);
                                        break;
                                    }
                                    else
                                    {
                                        // Convert the volume level to the format required by the waveOutSetVolume function
                                        DWORD volumelevel = (DWORD)(volume / 10.0 * 0xFFFF);
                                        volumelevel = (volumelevel << 16) | volumelevel;

                                        waveOutSetVolume(NULL, volumelevel);

                                        system("cls");
                                        cout << endl;
                                        cout << "Volume changed to " << volume << endl;
                                        cout << endl;
                                        cout << "Here is your playlist: " << endl;
                                        cout << endl;
                                        printfolder(member[i].folder, &directorysize, directories);
                                        break;
                                    }
                                }
                            }
                            else if (songaction == 4) // pause
                            {
                                for (int k = 0; k <= directorysize; k++)
                                {
                                    if (directories[k] == stringsongname) // searching for the song order
                                    {
                                        system("cls");
                                        cout << endl;
                                        cout << stringsongname << " stopped playing" << endl;
                                        cout << endl;
                                        PlaySound(NULL, NULL, 0);
                                        cout << "Here is your playlist: " << endl;
                                        cout << endl;
                                        printfolder(member[i].folder, &directorysize, directories);
                                    }
                                }
                            }
                            else if (songaction == 6)
                            {
                                system("cls");
                                cout << endl;
                                cout << "Back to the main page" << endl;

                                break;
                            }
                            else // if wrong number is entered
                            {
                                system("cls");
                                cout << endl;
                                cout << songaction << " is an invalid Choice" << endl;
                                cout << endl;

                                cout << "Here is your playlist: " << endl;
                                cout << endl;
                                printfolder(member[i].folder, &directorysize, directories);
                            }
                            cout << "SONG ACTIONS MENU" << endl;
                            cout << "Type desired action number" << endl;
                            cout << "1: Next track" << endl;
                            cout << "2: Previous track" << endl;
                            cout << "3: Repeat" << endl;
                            cout << "4: Pause" << endl;
                            cout << "5: Change volume" << endl;
                            cout << "6: Back (to get to the previous page)" << endl;
                            cout << endl;
                            cout << "Choice number: ";

                            cin >> songaction;

                        } // end  while song action

                    } // end if song is found

                } // end loop searching for sound

                if (found == false) // if song was not found
                {
                    system("cls");
                    cout << endl;
                    cout << songname << " was not found, check file name and extention and try again" << endl;
                }

            } // endif play choice

            else if (playlistaction == 2) // add song
            {
                cout << endl;
                cout << "Inside ADD SONG" << endl;
                cout << endl;
                cout << "Enter the file path of the song you want to add" << endl;
                cout << endl;
                // user-friendly way to input path
                char folder[100];
                char copypath[100];
                char userpath[100];
                char copysong[100];
                char exit[] = "done";

                cout << "Input DRIVE name (must be a single character)" << endl;
                cin >> copypath[0];
                copypath[1] = ':';

                int z = 2;
                cout << "Input FOLDER name or \"done\" to proceed" << endl;
                cin.ignore();
                cin.getline(folder, 100, '\n');
                while (strcmp(folder, exit) != 0)
                {
                    copypath[z] = '\\';
                    for (int f = 0; f <= strlen(folder); f++)
                    {
                        copypath[z + 1] = folder[f];
                        z++;
                    }

                    cout << "Input SUBFOLDER name or \"done\" to proceed" << endl;
                    cin.getline(folder, 100, '\n');
                }
                cout << endl;

                system("cls");

                cout << endl;
                cout << "This path is opened ( " << copypath << " )" << endl;
                cout << endl;

                if (printfolder(copypath, &directorysize, directories) == true)
                {

                    cout << endl;
                    cout << "Enter the name of the song that you want to add" << endl;
                    cout << "-must type extenstion" << endl;
                    cout << "-it is case sensetive" << endl;
                    cout << endl;
                    cout << "Songname: ";
                    cin.getline(copysong, 100, '\n');

                    char frompath[100];
                    char fromsong[30];

                    songpath(copypath, copysong, frompath, fromsong);

                    strcat_s(frompath, fromsong); // fromcopy now has the path we will copy from

                    char topath[100];
                    char tosong[30];

                    songpath(member[i].folder, copysong, topath, tosong);

                    strcat_s(topath, tosong); // topath now has the path we will copy to which is the user's playlist
                    system("cls");
                    CopySong(frompath, topath, copysong);
                }
                else
                {
                    system("cls");
                    cout << endl;
                    cout << "This path ( " << copypath << " )"
                         << " was not found, Check file path and try again" << endl;
                }
            }
            else if (playlistaction == 3) // delete song
            {
                cout << endl;
                cout << "Inside DELETE SONG" << endl;
                cout << endl;
                cout << "Here is your playlist:" << endl;
                cout << endl;
                printfolder(member[i].folder, &directorysize, directories);

                cout << "Enter the name of the song you want to delete" << endl;
                cout << "-must type extenstion" << endl;
                cout << "-it is case sensetive" << endl;
                cout << endl;
                cout << "Songname: ";

                char deletename[30];
                cin.ignore();
                cin.getline(deletename, 30, '\n');

                char deletepath[100];
                char modifieddeletename[30];

                songpath(member[i].folder, deletename, deletepath, modifieddeletename);
                strcat_s(deletepath, modifieddeletename); // now deletepath has the full path of the song to be deleted

                system("cls");
                DeleteSong(deletepath, deletename);
            }
            else
            {
                system("cls");
                cout << endl;
                cout << playlistaction << " is an invalid Choice" << endl;
            }
            cout << endl;
            cout << "Here is your playlist: " << endl;
            cout << endl;
            printfolder(member[i].folder, &directorysize, directories);
            cout << "PLAYLIST ACTIONS MENU" << endl;
            cout << "Type desired action:" << endl;
            cout << "1: Play song" << endl;
            cout << "2: Add song" << endl;
            cout << "3: Delete song" << endl;
            cout << "4: Exit" << endl;
            cout << endl;
            cout << "Choice number: ";
            cin >> playlistaction;
        } // endwhile playlist action

        delete[] songname;
    } // endif logged in
    delete[] member;
    delete[] password;
    delete[] username;
    delete[] directories;

} // endmain

// functions

// this function adds the contents of the folder to an array called directories to be used in searching later
// it displays the contents of the folder
// it counts the number of files(songs) in that folder
bool printfolder(char location[], int *dirptr, string directories[])
{
    for (int i = 0; i < 20; i++) // Reset the directories array before reading the contents of the directory
    {
        directories[i] = "";
    }

    bool status = false;
    int directorysize = 0;
    int dcount = 0;

    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(location)) != NULL)
    {

        while ((entry = readdir(dir)) != NULL)
        {
            status = true;

            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) // to remove the dots printed from the readdir function and get the correct size of songs in folder
            {
                directories[dcount] = entry->d_name;
                dcount++;
            }
        }
        closedir(dir);
    }
    else
    {
        status = false;
        cout << "error" << endl;
    }

    if (status == true)
    {
        for (int c = 0; c < dcount; c++) // printing the contents of directory
        {
            cout << directories[c] << endl;
        }

        for (int d = 0; d < 20; d++) // Iterate through the array and count the non-blank elements
        {
            if (directories[d] != "")
            {
                directorysize++;
            }
        }
        cout << endl;
        cout << directorysize << " items found." << endl;

        cout << endl;
        cout << endl;
        *dirptr = directorysize;
    }
    return status;
}

// this function adds the path of user playlist to another array to keep it unchanged by the strcat function
// also it adds '\' to the songname so when they are joined with the path with strcat, the right format is created (xx\xx\xx)
void songpath(char folderpath[], char songname[], char userpath[], char modifiedsongname[])
{
    modifiedsongname[0] = '\\';
    for (int m = 0; m <= strlen(songname) + 1; m++)
        modifiedsongname[m + 1] = songname[m];

    for (int L = 0; L <= strlen(folderpath); L++)
        userpath[L] = (folderpath)[L];
}

// this function plays a song inside the user's playlist
// displays a message if the operation was successfull or not
// it takes the full songpath and the songname
void PlaySong(char chartype[], char songname[])
{
    // playsound function takes LPCWSTR data type so we converted the char to LPCWSTR
    string stringtype(chartype);
    wstring temp = wstring(stringtype.begin(), stringtype.end());
    LPCWSTR LPCWSTRtype = temp.c_str();

    bool play;
    play = PlaySoundW(LPCWSTRtype, NULL, SND_FILENAME | SND_ASYNC);
    if (play == true)
    {
        cout << endl;
        cout << songname << " is playing" << endl;
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << songname << " could not be found, check songname and extention and try agai" << endl;
        cout << endl;
    }
}

// this function copies a song from any place on the pc to the user's playlist
// displays a message if the operation was successfull or not
// it takes the place we copy from, the place we copy to, and the songname
void CopySong(char frompath[], char topath[], char copysong[])
{
    // copyfile function takes LPCWSTR data type so we converted the char to LPCWSTR
    string stringtype(frompath);
    wstring temp = wstring(stringtype.begin(), stringtype.end());
    LPCWSTR LPCWSTRfrompath = temp.c_str();

    string stringtype2(topath);
    wstring temp2 = wstring(stringtype2.begin(), stringtype2.end());
    LPCWSTR LPCWSTRtopath = temp2.c_str();

    bool copied = CopyFileW(LPCWSTRfrompath, LPCWSTRtopath, 0);
    if (copied == true)
    {
        cout << endl;
        cout << copysong << " was copied successfuly" << endl;
    }
    else
    {
        cout << endl;
        cout << copysong << " was not added as it was not found, check file name and extension and try again" << endl;
    }
}

// this function deletes a song from the user playlist
// displays a message if the operation was successfull or not
// it takes the path of userplaylist and song name
void DeleteSong(char deletepath[], char deletename[])
{
    bool deleted = remove(deletepath);
    if (deleted == 0)
    {
        cout << endl;
        cout << deletename << " was deleted successfuly" << endl;
    }
    else
    {
        cout << endl;
        cout << deletename << " was not deleted as it was not found, check file name and extension and try again" << endl;
    }
}
