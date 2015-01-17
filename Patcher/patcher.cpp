#include <iostream>
#include <SFML/Network.hpp>

#include <ctime>
#include <fstream>
using namespace std;

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://www.cplusplus.com/reference/clibrary/ctime/strftime/
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

int main()
{
    std::string input = "";

    while(input != "1" && input != "2")
    {
        cout << "Pick a task: ";
        cout << "\n[1] Update";
        cout << "\n[2] Download full .zip ";
        cout << "\n>> ";
        cin >> input;
    }

    sf::Ftp ftp;

    sf::Ftp::Response response = ftp.connect("93.188.160.61");

    if(input == "1")
    {
        std::string currVersion[200]; std::string line1; ifstream file1;
        std::string serverVersion[200]; std::string line4; ifstream file4;
        std::string binDownload[200]; std::string line2; ifstream file2;
        std::string dataDownload[200]; std::string line5; ifstream file5;
        std::string options[200]; std::string line3; ifstream file3;

        int i=0;

        if (response.isOk())
            std::cout << "Connected" << std::endl;
        else
        {
            std::cout << "Error connecting to the server.";
            sf::sleep(sf::seconds(2));
            return 0;
        }

        response = ftp.login("u639266956", "tillykke1");

        if (response.isOk())
            std::cout << "Logged in" << std::endl;
        else
        {
            std::cout << "Couldn't log in." << std::endl;
            sf::sleep(sf::seconds(2));
            return 0;
        }

        //check version (if it needs to update)
        ftp.download("game/version.txt", "patcher", sf::Ftp::Binary);

        file1.open("bin/version.txt");

        if (file1.is_open())
        {
            while (!file1.eof())
            {
                getline(file1,line1);
                currVersion[i]=line1;
                i++;
            }
            i=0;
        }

        file1.close();

        file4.open("patcher/version.txt");

        if (file4.is_open())
        {
            while (!file4.eof())
            {
                getline(file4,line4);
                serverVersion[i]=line4;
                i++;
            }
            i=0;
        }

        file4.close();

        if(currVersion[0] != serverVersion[0])
        {
            std::cout << "Update found!";
            sf::sleep(sf::seconds(1));
            std::cout << "\n\nClient:" << currVersion[0];
            sf::sleep(sf::seconds(1));
            std::cout << "\nServer:" << serverVersion[0];
            sf::sleep(sf::seconds(1));
        }
        else
        {
            std::cout << "Game is up to date.";
            sf::sleep(sf::seconds(0.5));
            std::cout << "\n\nClient:" << currVersion[0];
            sf::sleep(sf::seconds(0.5));
            std::cout << "\nServer:" << serverVersion[0];
            sf::sleep(sf::seconds(2));
            return 0;
        }

        ftp.changeDirectory("game");

        //Getting bin items to download
        ftp.download("binDownload.txt", "patcher", sf::Ftp::Binary);

        file2.open("patcher/binDownload.txt");

        if (file2.is_open())
        {
            while (!file2.eof())
            {
                getline(file2,line2);
                binDownload[i]=line2;
                i++;
            }
            i=0;
        }

        file2.close();
        int y = 0;
        std::cout << "\n\nDownloading bin files...";
        do
        {
            std::cout << "\n" << binDownload[y] << "...";
            ftp.download(binDownload[y], "bin", sf::Ftp::Binary);
            std::cout << "Downloaded!";
            sf::sleep(sf::seconds(0.2));
            y++;

        } while(binDownload[y] != "");

        y = 0;

        //Getting data items to download
        ftp.download("dataDownload.txt", "patcher", sf::Ftp::Binary);

        file5.open("patcher/dataDownload.txt");
        i = 0;
        if (file5.is_open())
        {
            while (!file5.eof())
            {
                getline(file5,line5);
                dataDownload[i]=line5;
                i++;
            }
            i=0;
        }

        file5.close();

        int b =0;
        std::cout << "\n\nDownloading data files...";
        do
        {
            std::cout << "\n" << dataDownload[b] << "...";

            int last = dataDownload[b].find_last_of("/");
            std::string temp = dataDownload[b];
            std::string whereTo = temp.erase(last, dataDownload[b].max_size());

            sf::Ftp::Response dResponse = ftp.download(dataDownload[b], whereTo, sf::Ftp::Binary);
            if(dResponse.isOk())
                std::cout << "Downloaded!";
            else
                std::cout << "Failed.";
            sf::sleep(sf::seconds(0.2));
            b++;

        } while(dataDownload[b] != "");

        cout << "\n\nUpdate successful!";

        ftp.download("version.txt", "bin", sf::Ftp::Binary);

        sf::sleep(sf::seconds(2));
    }


    if(input == "2")
    {
        std::string toDownload[200]; std::string line; ifstream file;

        int i=0;

        if (response.isOk())
            std::cout << "Connected" << std::endl;
        else
        {
            std::cout << "Error connecting to the server.";
            sf::sleep(sf::seconds(2));
            return 0;
        }

        response = ftp.login("u639266956", "tillykke1");

        if (response.isOk())
            std::cout << "Logged in" << std::endl;
        else
        {
            std::cout << "Couldn't log in." << std::endl;
            sf::sleep(sf::seconds(2));
            return 0;
        }

        ftp.changeDirectory("game");

        cout << "\n\nDownloading...";
        sf::Ftp::Response dResponse = ftp.download("uokesrecovery.zip", "", sf::Ftp::Binary);
        if(dResponse.isOk())
            std::cout << "Downloaded successfully!";
        else
            std::cout << "Failed to download.";
        sf::sleep(sf::seconds(2.5));
        return 0;
    }

    std::string connText[1000]; std::string connLine; ifstream connFile;
    ofstream connWriteFile;

    ftp.download("connections.txt", "patcher", sf::Ftp::Binary);

    connFile.open("patcher/connections.txt");
    int g = 0;
    if (connFile.is_open())
    {
        while (!connFile.eof())
        {
            getline(connFile,connLine);
            connText[g]=connLine;
            g++;
        }
    }
    connFile.close();
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

    connWriteFile.open("patcher/connections.txt");

    int l = 0;

    do
    {
        if(!connText[l].empty())
        {
            connWriteFile << connText[l] << "\n";
        }
        else
        {
            connWriteFile << currentDateTime();
            l = 1001;
        }

        l++;
    } while(l < 1000);
    connWriteFile.close();
    ftp.upload("patcher/connections.txt", "", sf::Ftp::Binary);

    connWriteFile.open("patcher/connections.txt");
    connWriteFile << "";
    connWriteFile.close();

    return 0;
}

