#include "recount.h"

/**
 * @brief recount::recount empty constructor
 */
recount::recount()
{
    this->code = -1;
}

//TO_DO: all methods of the class

// Constructor
recount::recount(vector<string> data) {
    code = stoi(data[0]);
    municipal = data[1];
    zone = stoi(data[2]);
    section = stoi(data[3]);
    name = data[4][0];
    census = stoi(data[5]);
    abstentions = stoi(data[6]);
    v_cast = stoi(data[7]);
    v_invalid = stoi(data[8]);
    v_valid = stoi(data[9]);
    v_white = stoi(data[10]);
}


// Getters
int recount::get_v_cast() {
    return v_cast;
}

int recount::get_abstentions() {
    return abstentions;
}

int recount::get_census() {
    return census;
}

float recount::get_p_participation() {
    return p_participation;
}

float recount::get_p_abstention() {
    return p_abstention;
}





// Setters
void recount::set_p_participation(float p_participation) {
    this->p_participation = p_participation;
}

void recount::set_p_abstention(float p_abstention) {
    this->p_abstention = p_abstention;
}




// Print information
void recount::print() {
    cout << "Code: " << code << endl;
    cout << "Municipal: " << municipal << endl;
    cout << "Zone: " << zone << endl;
    cout << "Section: " << section << endl;
    cout << "Name: " << name << endl;
    cout << "Census: " << census << endl;
    cout << "Abstentions: " << abstentions << endl;
    cout << "Votes Cast: " << v_cast << endl;
    cout << "Invalid Votes: " << v_invalid << endl;
    cout << "Valid Votes: " << v_valid << endl;
    cout << "White Votes: " << v_white << endl;
}











