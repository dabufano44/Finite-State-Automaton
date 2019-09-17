/*
 * CISC 5200 (Compter Language Theory)
 * Spring, 2019
 *
 * Project 1: A Deterministic Finite-State Automaton
 *
 * Implementation file for FSA class
 *
 * Author: Danielle Bufano
 * Date:   2 Feb 2019
 */

//#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FSA.h"
using namespace std;

FSA::FSA(std::ifstream &ifs)
{
    string temp;
    int numAcceptStates;
    int acceptState;
    int state;
    // assigns the data from the ifstream file to private member variables of FSA class
    while (!ifs.eof())
    {
        ifs >> temp;
        int len = temp.length();
        for (int i = 0; i < len; i++)
        {
        sigma.push_back(temp.at(i));
        }
        
        ifs >> num_states >> start_state >> numAcceptStates;
        for (int i = 0; i < numAcceptStates; i++)
        {
            ifs >> acceptState;
            accept_states.push_back(acceptState);
        }
    
        for (int i = 0; i < (num_states); i++)
        {
            std::vector<int> temp;
            for (int j = 0; j < 2; j++)
            {
                ifs >> state;
                temp.push_back(state);
            }
            state_table.push_back(temp);
        }
    }
}

// returns the index of each inputted character where it's found in the sigma string. if the character is not in the sigma string, return -1
template <typename T> int FSA::find(const std::vector<T> v, const T x)
{
    int len = v.size();
    for (int i = 0; i < len; i++)
    {
        if (x == v[i])
            return i;
    }
    return -1;
}

void FSA::trace(const std::string& in_string)
{
    int col;
    int row;
    int state = start_state;
    int length = in_string.length();
    bool inputValid = true;
    // finds row and col in state table for each input character
    for (int i = 0; i < length; i++)
    {
        col = find(sigma, in_string.at(i));
        if (col < 0)
        {
            inputValid = false;
            break;
        }
        row = state;
        cout << state << " ";
        state = state_table[row-1][col];
    }
    int size = accept_states.size();
    bool validString = false;
    
    // checks whether final state is an accept state
    for (int i = 0; i < size; i++)
    {
        if (state == accept_states[i])
            validString = true;
    }
    
    if (validString && inputValid)
        cout << state << " ...string accepted!" << endl;
    else if (!validString && inputValid)
        cout << state << " ...string not accepted" << endl;
    else
        cout << "input invalid" << endl;

}


