#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <Windows.h>
using namespace std;
struct person {
    string name="";
    string birthdate="";
    string paretn_1="";
    string paretn_2="";
    string gender="";
    string partner="X";
    string marriagedate = "x";
    string death="X";
};
vector <string> parents = {
    "parent(zahar_polyana,tihon_polyana).",
    "parent(zahar_polyana,matrean_stolyarova).",
    "parent(matrean_stolyarova,erifim_stolyarov).",
    "parent(matrean_stolyarova,peter_stolyarov).",
    "parent(matrean_stolyarova,daria_stolyarova).",
    "parent(matrean_stolyarova,klavdia_stolyarova).",
    "parent(tihon_polyana,valentin_polin).",
    "parent(valentin_polin,gennadii_polin).",
    "parent(valentin_polin,arkadii_polin).",
    "parent(valentin_polin,aleksandr_polin).",
    "parent(valentin_polin,ekaterina_morozova).",
    "parent(valentin_polin,zinaida_dziba).",
    "parent(valentin_polin,olga_kyshunko).",
    "parent(tihon_polyana,daria_polina).",
    "parent(daria_polina,klavdia_kalinina)."
};
vector <string> birthdays = {
    "birth(tihon_polyana,1880,zahar_polyana,tatyana,female).",
    "birth(matrean_stolyarova,1880,zahar_polyana,tatyana,female).",
    "birth(erifim_stolyarov,1906,matrean_stolyarova,anakentii,male)",
    "birth(peter_stolyarov,1907,matrean_stolyarova,anakentii,male).",
    "birth(daria_stolyarova,1910,matrean_stolyarova,anakentii,female).",
    "birth(klavdia_stolyarova,1914,matrean_stolyarova,anakentii,female).",
    "birth(valentin_polin,1910,tihon_polyana,anastasia,male).",
    "birth(gennadii_polin,1953,valentin_polin,maria,male).",
    "birth(arkadii_polin,1949,valentin_polin,maria,male).",
    "birth(aleksandr_polin,1942,valentin_polin,maria,male).",
    "birth(ekaterina_morozova,1943,valentin_polin,maria,female).",
    "birth(zinaida_dziba,1952,valentin_polin,maria,female).",
    "birth(olga_kyshunko,1959,valentin_polin,maria,female).",
    "birth(daria_polina,1922,tihon_polyana,anastasia,female).",
    "birth(klavdia_kalinina,1945,daria_polina,valerii_kalinin,female).",
};
vector <string> marryages = {
    "marriage(tihon_polyana,anya,1900).",
    "marriage(matrean_stolyarova,konstantin_stolyarov,1905)",
    "marriage(erifim_stolyarov,tatyana_stolyarov,1925).",
    "marriage(peter_stolyarov,elena_stolyarov,1930).",
    "marriage(daria_stolyarova,peter,1930).",
    "marriage(valentin_polin,aleksandra,1930).",
    "marriage(daria_polina,valerii_kalinin,1944).",
};
vector <string> deaths = {
    "death(tihon_polyana,1968).",
    "death(matrean_stolyarova,1944).",
    "death(erifim_stolyarov,1945).",
    "death(daria_stolyarova,1969).",
    "death(peter_stolyarov,1970).",
    "death(klavdia_stolyarova,1933).",
    "death(valentin_polin,1973).",
    "death(daria_polina,1997).",
};
void out_prolog() {
    for (int i = 0; i < parents.size(); i++) {
        cout << parents[i] << endl;
    }
    for (int i = 0; i < birthdays.size(); i++) {
        cout << birthdays[i] << endl;
    }
    for (int i = 0; i < marryages.size(); i++) {
        cout << marryages[i] << endl;
    }
    for (int i = 0; i < deaths.size(); i++) {
        cout << deaths[i] << endl;
    }
}
void out_person(person p) {
    cout << "Вас зовут " << p.name << endl;
    cout << "Вы родились в " << p.birthdate << endl;
    cout << "Вот ваши родители " << p.paretn_1 << " " << p.paretn_2 << endl;
    cout << "Ваш пол " << p.gender<<endl;;
    cout << "Ваш супруг(а) " << p.partner << endl;
    cout << "Вы вышли замуж(женились) в " << p.marriagedate << endl;
}
void finder(string text) {
    regex pattern("Я родился в (\\d+) году, (моего|мою) (отца|мать) зовут (\\w+), мой пол (\\w+)");
    smatch match;
    if (std::regex_search(text, match, pattern)) {
        //cout << match[1] << "\n" << match[2] << "\n" << match[3] << "\n" << match[4] << "\n" << match[5] << "\n";
        vector<person> result;
        regex pattern_birth("birth\\((\\w+),(\\d+),(\\w+),(\\w+),(\\w+)\\)\\.");
        smatch match_birth;
        for (int i = 0; i < birthdays.size(); i++) {
            regex_search(birthdays[i], match_birth, pattern_birth);

            if ((match_birth[2] == match[1]) && ((match_birth[3] == match[4]) || (match_birth[4] == match[4])) && (match_birth[5] == match[5])) {
                person p;
                p.name = match_birth[1];
                p.birthdate = match_birth[2];
                p.paretn_1 = match_birth[3];
                p.paretn_2 = match_birth[4];
                p.gender = match_birth[5];
                result.push_back(p);
            }
        }
            if (result.size() == 0) {
                cout << "Нет совпдений \n";
                return;
            }
            if (result.size() > 1) {
                string sibling;
                cout << "Введите имя своего брата/сестры\n";
                getline(cin,sibling);
                int deleten=-1;
                for (int i = 0; i < result.size(); i++) {
                    if (result[i].name == sibling) {
                        deleten = i;
                    }
                }
                if(deleten!=-1) result.erase(result.begin() + deleten);
            }
            //marriage(tihon_polyana,anya,1900).
            regex pattern_marriage("marriage\\((\\w+),(\\w+),(\\d+)\\)\\.");
            smatch match_marriage;
            for (int i = 0; i < marryages.size(); i++) {
                regex_search(marryages[i], match_marriage, pattern_marriage);
                if (match_marriage[1] == result[0].name) {
                    result[0].partner=match_marriage[2];
                    result[0].marriagedate = match_marriage[3];
                        break;
                }
                if (match_marriage[2] == result[0].name) {
                    result[0].partner = match_marriage[1];
                    result[0].marriagedate = match_marriage[3];
                    break;
                }
            }
            out_person(result[0]);
    }
    else {
        cout << "Неверный запрос\n";
    }
    //Я родился в 1945 году, моего отца зовут valerii_kalinin, мой пол female
    //Я родился в 1953 году, моего отца зовут valerii_kalinin, мой пол male
    //Я родился в 1880 году, моего отца зовут zahar_polyana, мой пол female matrean_stolyarova
    //Я родился в 1942 году, моего отца зовут valentin_polin, мой пол male
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
    SetConsoleOutputCP(1251);
    string text;
    string gender;
    while (true) {
        cout << "Выберите действие\n";
        cout << "1. Вывести базу знаний\n";
        cout << "2. Выполнить поиск\n";
        cout << "3. Пример запроса\n";
        string action;
        getline(cin, action);
        int act = atoi(action.c_str());
        switch (act)
        {
        case 1:
            out_prolog();
            break;
        case 2:
            cout << "Введите запросу в виде \"Я родился в year году, (моего|мою) (отца|мать) зовут text, мой пол (male|female)\"\n";
            getline(cin, text);
            finder(text);
            break;
        case 3:
            cout << "Запрос \nЯ родился в 1953 году, моего отца зовут valentin_polin, мой пол female\n";
            finder("Я родился в 1910 году, моего отца зовут matrean_stolyarova, мой пол female");
            break;
        default:
            cout << "Неврное действие\n";
            break;
        }
       
    }
    return 0;
}
