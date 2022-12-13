#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        size_t kLength = k.length();
        HASH_INDEX_T w[5] = {0,0,0,0,0};

        //setting substrings

        //less than or equal to 6 characters long
        if(kLength <= 6)
        {
            char a[6];
            //set the characters that exist
            for(size_t i = 0; i < kLength; ++i)
            {
                a[i] = k[kLength - 1 - i];
            }
            //set the rest to something outside of generating range;
            for(size_t i = kLength; i < 6; ++i)
            {
                a[i] = '-';
            }

            //adding up the values
            for(size_t i = 0; i < 6; ++i)
            {
                w[4] += pow(36,i) * letterDigitToNumber(a[i]);
            }
            
            return w[4] * rValues[4];
        }
        //length greater than 6 characters
        else
        {
            std::string a[6];

            int counter = 4;
            for(size_t i = kLength - 1; i+12 >= 12; i -= 6)
            {
                //adding the substring to character array to be prosessed 
                char b[6] = {'-','-', '-', '-', '-', '-'};
                size_t j = 0;
                for(; (j < 6) && (i - j + 6 >= 6); ++j)
                {
                    b[j] = k[i-j];
                }
                //set the rest to something outside of generating range;
                for(; j < 6; ++j)
                {
                    
                    b[j] = '-';
                }

                //adding up the values
                for(int k = 0; k < 6; ++k)
                {
                    w[counter] += pow(36,k) * letterDigitToNumber(b[k]);
                }
                --counter;
            }

            HASH_INDEX_T temp = 0;
            for(int i = 0; i < 5; ++i)
            {
                //multiply by correlated rValue and add to hash total
                temp += rValues[i] * w[i];
            }
            return temp;
        }
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = tolower(letter);

        //character is a letter
        if((int) letter >= 97 && (int) letter <= 122) return ((int) letter) - 97;
        //character is a number
        else if((int) letter >= 48 && (int) letter <= 57) return ((int) letter) - 22;
        //character is neither
        else return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
