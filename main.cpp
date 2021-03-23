#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "vocab.h"
#include <stdio.h>
#include <Windows.h>
using namespace std;


/*Разработать программу проверки орфографии (правильности
написания) слов в некоторой строке, сравнивая их со словами из
словаря. В качестве словаря использовать одномерный массив
слов, заданный в программе. При сравнении учитывать
возможность записи слов с прописными и строчными буквами.
*/

/*
При запуске программы мы выбираем словарик из уже имеющихся или создаём свой(можно сделать отдельный выбор в общем меню, типа настройки.
Так же, при выборе словаря сразу же происходит загрузка его составляющих в вектор типа стринг. При выполнении каждого пункта
(при окончании его выполнения происходит перезапись с файлом).
При закрытии файла настройка сохраняется в файл настройки. При открытии настройка загружается. При смене настройки она сохранится при завершении выполнения программы.
SAVE_VARIBLE_NAME(main);

*/
string VARIBLE_NAME = "NULL";//переменная, которая несёт имя функции
//#define SAVE_VARIBLE_NAME(varible) VARIBLE_NAME = string(#varible);//не знаю, что это, вычитал в интернете
string AGREE_NAME = "NULL";//переменная, которая несёт имя функции
#define SAVE_AGREE_NAME(varible) AGREE_NAME = string(#varible);

int menu()
{
    cout<<"Welcome! Menu:"<<endl<<"1.Check words"<<endl<<"2.Fill vocabulary"<<endl<<"3.Read vocabulary"<<endl<<"4.Delete from vocabulary"<<endl;
    cout<<"5.Setting"<<endl<<"6.Exit"<<endl<<endl;
    cout<<"Enter>> ";

    int input;
    cin>>input;
    if(cin.fail() || (input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 6))
    {
        cin.clear();
        cout<<"Oops, this input is invalid, please, try again."<<endl;
        cin.ignore(32767, '\n');
        exit(0);
    }
    else return input;
}

char agree()
{
    if(AGREE_NAME == "agree")
        cout<<"Are you sure?"<<endl;
    else cout<<"You want to pick or create vocabulary?"<<endl<<"P/C"<<endl;
    char agg;
    cin>>agg;
    if(AGREE_NAME == "agree")
    {
        if(cin.fail() || (agg!= 'Y' && agg != 'y' && agg != 'N' && agg != 'n'))
        {
            cin.clear();
            cout<<"Oops, this input is invalid, please, try again."<<endl;
            cin.ignore(32767, '\n');
            exit(0);
        }
        else return agg;
    }
    else {
        if(cin.fail() || (agg!= 'P' && agg != 'p' && agg != 'c' && agg != 'C'))
        {
            cin.clear();
            cout<<"Oops, this input is invalid, please, try again."<<endl;
            cin.ignore(32767, '\n');
            exit(0);
        }
        else return agg;
    }

}

class Vocabulary{
public:

    void get_input(int in)
    {
        input = in;
    }
    Vocabulary(string language)
    {
        VARIBLE_NAME = language;
    }
    void fill_word(string word)
    {
        setlocale(LC_ALL,"Russian");
        text.push_back(word);
    }
    void delete_word(string word)
    {
        for(int i = 0; i < text.size(); i++)
        {
            if(word == text[i])
            {
                text.erase(text.begin()+i);
            }
        }
    }
    void print_voc()
    {
        chech_voc();
        for(int k = 0; k < text.size(); k++)
        {
            cout<<text[k]<<'\t';
            if((k+1)%10==0)
                cout<<endl;
        }
        cout<<endl<<endl;
        clean();
    }
    void clean()
    {
        text.clear();
    }
    void chech_voc()
    {
        ifstream fout;
        string lang = VARIBLE_NAME + ".txt";
        fout.open(lang);
        string s_word;
        while(fout>>s_word)
        {
            text.push_back(s_word);
        }

        fout.close();
    }
    void setting()
    {
        SAVE_AGREE_NAME(setting);
        char aggr = agree();
        if(aggr == 'p' || aggr == 'P')
        {
            ifstream lang("languages.txt");
            string languages;
            vector<string> picks;
            picks.resize(0);
            while(lang>>languages)
            {
                picks.push_back(languages);
            }
            lang.close();
            for(int l = 0; l < picks.size(); l++)
            {
                cout<<l+1<<"."<<picks[l]<<endl;
            }
            cout<<endl<<"Enter: ";
            int in;
            cin>>in;
            in--;
            int key = 0;
            for(int j = 0; j < picks.size(); j++)
            {
                if(j==in)
                    key++;
            }
            if(cin.fail() || (key==0))
            {
                cin.clear();
                cout<<"Oops, this input is invalid, please, try again."<<endl;
                cin.ignore(32767, '\n');
                exit(0);
            }
            cout<<"You pick "<<picks[in]<<" language. "<<endl<<endl;

            VARIBLE_NAME=picks[in];
            ofstream sav("settings.txt");
            sav<<VARIBLE_NAME;
            sav.close();
        }
        else{//(aggr == 'C' || aggr == 'c')
            create();
        }


        SAVE_AGREE_NAME(agree);
    }

    void create()
    {
        cout<<"Enter name of vocabulary(without .txt): ";
        string namev;
        cin>>namev;
        if(cin.fail())
        {
            cout<<"Something goes wrong! Try again."<<endl<<endl;
            exit(0);
        }
        ifstream check("languages.txt");
        string lan;
        bool checker = false;
        while(check>>lan)
        {
            if(namev==lan)
            {
                checker = true;
            }
        }
        check.close();
        if(checker == true)
        {
            cout<<"Stop! Vocabulary with that name already exists. Try another one!"<<endl;
            exit(0);
        }
        //namev+=".txt";
        ofstream created(namev+".txt");
        //namev-=".txt";
        created.close();
        ofstream lang("languages.txt", ios_base::app);
        lang<<namev<<endl;
        cout<<"You created a "<<namev<<" vocabulary. Congratulations!"<<endl<<endl;

        VARIBLE_NAME=namev;
        ofstream sav("settings.txt");
        sav<<VARIBLE_NAME;
        sav.close();
    }
    void filling()
    {
        cout<<"Enter word or words what you want to include(end with *END*):"<<endl;
        vector<string> words;
        string word;
        words.resize(0);
        int z = 0;
        while(true)
        {
            cin>>word;
           // words.resize(z);
            words.push_back(word);
           // words[z]=word;
            if(word=="*END*")
            {
                //cin.ignore(32767, '\n');
                //words.resize(z-1);
                break;
            }
            else z++;
        }
        ifstream fin(VARIBLE_NAME + ".txt");
        string check;
        int counter = 0;
        while(fin>>check)
        {
            counter++;
            //cout<<"Counter: "<<counter<<" ";
            if(counter==10)
                counter=0;

        }
        ofstream fout(VARIBLE_NAME + ".txt", ios_base::app);
        for(int s = 0; s < words.size()-1; s++)
        {
            fout<<words[s]<<" ";
            counter++;
            if(counter==10)
            {
                fout<<endl;
                counter=0;
            }
        }
        fout.close();
        fin.close();
        words.clear();
        clean();
    }

    void del()
    {
        cout<<"What word or words do you want to delete?(*END*)"<<endl;
        vector<string> words;
        string word;
        words.resize(0);
        int z = 0;
        while(true)
        {
            cin>>word;
            words.push_back(word);
            if(word=="*END*")
            {
                //cin.ignore(32767, '\n');
                //words.resize(z-1);
                break;
            }
        }
        vector<string> previ;
        previ.resize(0);
        string mass;
        ifstream cop(VARIBLE_NAME + ".txt");
        while(cop>>mass)
        {
            previ.push_back(mass);
        }
        for(int i = 0; i < words.size()-1; i++)
        {
            int counter = 0;
            for(int l = 0; l < previ.size(); l++)
            {
                if(words[i] == previ[l])
                {
                    previ[l].erase();
                }
                else{
                    counter++;
                    if(counter==previ.size())
                    {
                        cout<<endl<<words[i]<<" can not be find!"<<endl;
                    }
                }
            }
        }
        cop.close();
        ofstream fout(VARIBLE_NAME + ".txt");
        for(int s = 0; s < previ.size(); s++)
        {
            fout<<previ[s]<<" ";
        }
        fout.close();
        words.clear();
        clean();
    }
    void testing()
    {
        vector<int> color;
        vector<string> ptrmass;
        ptrmass.resize(0);
        color.resize(0);
        int counter = 0, errors = 0;

        cout << "Write in "<<VARIBLE_NAME<<" (EXIT for end): " << endl;
        for (int i = 0; i < 100; i++)
        {
            string wor;
            cin >> wor;
            ptrmass.push_back(wor);
            counter++;
            color.push_back(0);
            if ((ptrmass[i] == "EXIT") || (ptrmass[i] == "ВЫХОД"))
            {
                break;
            }
        }
        //cin.ignore(32767, '\n');
        errors = orfo(ptrmass, color, counter);
        print(ptrmass, color, errors);
        cout << endl;
    }

    int orfo(const vector<string> &mass, vector<int> &colo, int length)
    {
        int countest = 0;
        for (int i = 0; i < length - 1; i++)
        {
            ifstream dict(VARIBLE_NAME + ".txt");
            if (!dict)
                exit(100500);
            string temp;
            int xx = 0;
            while (dict >> temp)
            {
                if (temp == mass[i])
                {
                    xx++;
                }
            }
            if (xx == 0)
            {
                //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                countest++;
                colo[i] = 1;
                //SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 4));
            }
            dict.close();
        }
        return countest;
    }

    void print(const vector<string> &mass, vector<int> &colo, const int &counter)
    {
        cout << "Your sentence:   ";
        for (int i = 0; i < colo.size(); i++)
        {

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (colo[i] == 1)
            {
                SetConsoleTextAttribute(hConsole, (WORD)((4 << 4) | 15));
            }
            cout << mass[i];
            SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
            cout << " ";
        }
        cout << endl << "And you have " << counter << " errors/unknowing points!" << endl;
    }


private:

    int input;
    vector<string> text;
    string name;
    string language;


};

int main()
{

    ifstream lang("settings.txt");
    lang>>VARIBLE_NAME;
    cout<<VARIBLE_NAME<<endl;
    lang.close();
    Vocabulary language(VARIBLE_NAME);
    while(true)
    {

        //Vocabulary english;
        int input = menu();
        switch(input)
        {
        case 1:
            //Check words - OK
            language.testing();
            language.get_input(input);
            break;
        case 2:
            //Fill - OK
            language.get_input(input);
            language.filling();
            break;
        case 3:
            //Read - OK
            language.get_input(input);
            language.print_voc();
            break;
        case 4:
            //Delete - OK
            language.get_input(input);
            language.del();
            break;
        case 5:
            //Setting - OK
            SAVE_AGREE_NAME(setting);
            language.setting();
            language.get_input(input);
            break;
        case 6:
            //EXIT - OK
            SAVE_AGREE_NAME(agree);
            char aggr = agree();
            if(aggr != 'n' && aggr != 'N')
            {
                exit(0);
            }
            break;
        }

        ofstream lang("settings.txt");
        lang<<VARIBLE_NAME;
        lang.close();
    }

    return 0;
}
