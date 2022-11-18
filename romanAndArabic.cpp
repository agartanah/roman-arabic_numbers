/********************************************************
 * Автор: Вяткин Владислав                              * 
 * Группа: ПИ-221                                       *
 * Название: Перевод чисел из Арабских                  *
 *  в Римские и наоборот                                *
 * Дата: 18.11.2022                                     *
 * Ссылка на OnlineGDB: https://onlinegdb.com/VzlL1S-Iu * 
 ********************************************************/

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int signRomanCount = 7;
char numberRoman[signRomanCount]  = {'I', 'V', 'X', 'L', 'C', 'D',  'M'};
int numberArabic[signRomanCount]  = { 1,   5,  10,  50, 100, 500, 1000 };

int main() {
  
  int numberIndex, numberIndexPrevious = -1, numberArabicTotal = 0;
  string numberRomanTotal = "", numberUsers;
  
  enum sign { NEG, POS } signSum;
  
  int userSelection;
  
  Instruction();
  
  cout << endl;
  cout << "1. Из Римских в Арабские" << endl;
  cout << "2. Из Арабских в Римские" << endl;
  cout << endl;
  cout << "Напишите номер выбранного пункта: ";
  cin  >> userSelection;
  cout << endl;
  
  if (userSelection == 1) {
    cout << "Введите римское число: ";
    cin  >> numberUsers;
    cout << endl;
    
    int signCount = numberUsers.length();
    
    for (int signIndex = signCount - 1; signIndex >= 0; --signIndex) {
      
      for (int findIndex = 0; findIndex < signRomanCount; ++findIndex) {
        if (numberUsers[signIndex] == numberRoman[findIndex]) {
          numberIndex = findIndex;
        } 
      }
      
      if ((numberIndex > numberIndexPrevious) || (signIndex == signCount - 1)) {
        numberArabicTotal += numberArabic[numberIndex];
        signSum = POS;
      } else if (numberIndex < numberIndexPrevious) {
        numberArabicTotal -= numberArabic[numberIndex];
        signSum = NEG;
      } else {              // numberIndex == numberIndexPrevious
        switch (signSum) { // Определяет прибавлять или отнимать идущие подряд цифры
          case POS:
            numberArabicTotal += numberArabic[numberIndex];
            break;
          case NEG:
            numberArabicTotal -= numberArabic[numberIndex];
            break;
        }
      }
      
      numberIndexPrevious = numberIndex;
    }
    
    cout << "Получившееся число (арабское): ";
    cout << numberArabicTotal << endl;
    
  } else if (userSelection == 2) {
    if ((signRomanCount - 1) % 2 == 0) {
      cout << "Введите число от 1 до " 
           << numberArabic[signRomanCount - 1] * 4 - 1
           << " : ";
      cin  >> numberUsers;
      cout << endl;
      
      if (stoi(numberUsers) > numberArabic[signRomanCount - 1] * 4 - 1
       || stoi(numberUsers) < 1) {
        cout << "Перезапустите программу и введите число в нужном формате!" << endl;
        return 0;
      }
    } else {
      cout << "Введите число от 1 до " 
           << numberArabic[signRomanCount - 1] * 2 - 1001
           << " : ";
      cin  >> numberUsers;
      cout << endl;
      
      if (stoi(numberUsers) > numberArabic[signRomanCount - 1] * 2 - 1001
       || stoi(numberUsers) < 1) {
        cout << "Перезапустите программу и введите число в нужном формате!" << endl;
        return 0;
      }
    }
    
    int signCount = numberUsers.length();

    int order = signCount - 1;
    
    for (int signIndex = 0; signIndex < signCount; ++signIndex) {
      bool coincidence = false;
      
      int numeral = numberUsers[signIndex] - '0';
      
      if (numeral != 0) {
        int numeralWithOrder = numeral * pow(10, order);
        
        for (int findIndex = 0; findIndex < signRomanCount; ++findIndex) {
          if (numeralWithOrder < numberArabic[findIndex]) {
            numberIndex = findIndex - 1;
            break;
          } else if (numeralWithOrder == numberArabic[findIndex]) {
            coincidence = true;
            numberIndex = findIndex;
            break;
          } else if (numeralWithOrder > numberArabic[signRomanCount - 1]) {
            numberIndex = signRomanCount - 1;
            break;
          }
        }
        int sumAdditional;
        
        if (coincidence) {
          numberRomanTotal += numberRoman[numberIndex];
        } else if (numberIndex % 2 != 0) {
          if ((numberArabic[numberIndex + 1] - numberArabic[numberIndex] / 5)
          == numeralWithOrder) { 
            numberRomanTotal += numberRoman[numberIndex - 1]; 
            numberRomanTotal += numberRoman[numberIndex + 1];
          } else {
            sumAdditional = numeralWithOrder - numberArabic[numberIndex];
            
            numberRomanTotal += numberRoman[numberIndex];
            
            for (int repeatIndex = 0; repeatIndex < sumAdditional / numberArabic[numberIndex - 1];
            ++repeatIndex) {
              numberRomanTotal += numberRoman[numberIndex - 1];
            }
          }
        } else if (numberIndex % 2 == 0) {
          if ((numberArabic[numberIndex + 1] - numberArabic[numberIndex])
          == numeralWithOrder) {  
            numberRomanTotal += numberRoman[numberIndex]; 
            numberRomanTotal += numberRoman[numberIndex + 1];
          } else {
            sumAdditional = numeralWithOrder / numberArabic[numberIndex];
            
            for (int repeatIndex = 0; repeatIndex < sumAdditional;
            ++repeatIndex) {
              numberRomanTotal += numberRoman[numberIndex];
            }
          }
        }
      }
      
      --order;
    }
    
    cout << "Получившееся число (римское): " << numberRomanTotal << endl;
  }
}















