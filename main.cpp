#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <recount.h>
#include <algorithm>
#include <cstring>
#include <sys/time.h>
#include <omp.h>
#include <QDir>

using namespace std;

//PROTOTYPES
void calculate_p_participation(vector<recount> content, string mode="sequential");
void calculate_p_abstention(vector<recount> content, string mode="sequential");
int calculate_total_census(vector<recount> content, string comp_mode="sequential");
int calculate_total_abstention(vector<recount> content, string comp_mode="sequential");
recount get_min_census(vector<recount> content, string comp_mode="sequential");
recount get_max_census(vector<recount> content, string comp_mode="sequential");
float get_mean_p_participation(vector<recount> content, string mode="sequential");

//MAIN
int main()
{
    // It can be used to know the execution path
    //cout << "[EXECUTION PATH]: " << QDir::currentPath().toStdString() + '\n';
    // Path and name of the csv file
    string fname = "../project_base/elecciones_navarra_1999.csv";

    // Init variables
    vector<recount> content;
    vector<string> row;
    recount read_recount = recount();
    int count_row = 0;
    string line, word;


    //Read document
    ifstream file (fname, ios::in);
    if(file.is_open())
    {
        //Read each row of the file
        while(getline(file, line))
        {
            row.clear(); // Clear row array
            stringstream stream(line);
            // Divide the line by the separator (;) and each value is an element of the array row
            while(getline(stream, word, ';'))
                row.push_back(word);
            if (count_row>0){ //First row of the document correspond to the header
                // TO_DO: CREATE recount object and append to content

                //read_recount.print(); //To see the information uncomment this line
            }
            count_row++;
        }
        cout<<"[OK]: "<< count_row << " lines read from the file and added to the list of contents" << "\n";
    }
    else{
        cout<<"[ERROR]: Could not open the file, check the file path\n";
    }

    //TO_DO: CALL TO FUNCTIONS AND MEASURE TIMES

    return 0;
}

//TO_DO: FUNCTIONS

/**
 * @brief calculate_total_census calculate total number of census people
 * @param content vector of recount elements
 * @param comp_mode is the computational mode, it can be: sequential or parallel
 * @return number of census people in total
 */
int calculate_total_census(vector<recount> content, string comp_mode){
        // Init variables
        recount r = recount();
        struct timeval begin, end;
        double wt1 = 0,wt2 = 0;
        int total = 0;
        int census = 0;

        wt1=omp_get_wtime();
        gettimeofday(&begin, 0);
        // Sequential mode
        if(comp_mode=="sequential"){

            // TO_DO: calculate total in sequential mode

        // Parallel mode
        }else if(comp_mode=="parallel"){

            // TO_DO: calculate total in parallel mode
        }else{
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }
        gettimeofday(&end, 0);
        wt2=omp_get_wtime();

        //Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds*1e-6 + microseconds; //in microseconds
        printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);
        double omp_elapse = (wt2-wt1)*1e-6;
        printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), omp_elapse);
        return total;
}
