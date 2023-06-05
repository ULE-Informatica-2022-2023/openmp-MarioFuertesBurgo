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
#include <QThread>

using namespace std;

//PROTOTYPES
void calculate_p_participation(vector<recount>& content, string mode="sequential");
void calculate_p_abstention(vector<recount>& content, string mode="sequential");
int calculate_total_census(vector<recount> content, string comp_mode="sequential");
int calculate_total_abstention(vector<recount> content, string comp_mode="sequential");
recount get_min_census(vector<recount> content, string comp_mode="sequential");
recount get_max_census(vector<recount> content, string comp_mode="sequential");
float get_mean_p_participation(vector<recount> content, string mode="sequential");
float get_mean_p_abstention(vector<recount> content, string mode="sequential");

//MAIN
int main()
{
    // It can be used to know the execution path
    cout << "[EXECUTION PATH]: " << QDir::currentPath().toStdString() + '\n';
    // Path and name of the csv file
    string fname = "../LabAssigment6/elecciones_navarra_1999.csv";

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
                recount read_recount(row);
                content.push_back(read_recount);
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

    //total_census
    int total_census = calculate_total_census(content, "parallel");
    total_census = calculate_total_census(content, "sequential");
    printf("[TOTAL_CENSUS] %d\n", total_census);


    //total_participation
    int total_abstention = calculate_total_abstention(content, "parallel");
    total_abstention = calculate_total_abstention(content, "sequential");
    printf("[TOTAL_ABSTENTIONS] %d\n", total_abstention);


    //get_min_census
    recount min_census = get_min_census(content, "parallel");
    min_census = get_min_census(content, "sequential");
    printf("[MIN_CENSUS]\n");
    min_census.print();

    //get_max_census
    recount max_census = get_max_census(content, "parallel");
    max_census = get_max_census(content, "sequential");
    printf("[MAX_CENSUS]\n");
    max_census.print();

    //calculate_p_participation
    calculate_p_participation(content, "parallel");
    calculate_p_participation(content, "sequential");

    //calculate_p_abstention
    calculate_p_abstention(content, "parallel");
    calculate_p_abstention(content, "sequential");

    //calculate_mean_p_participation
    float mean_p_participation = get_mean_p_participation(content, "parallel");
    mean_p_participation = get_mean_p_participation(content, "sequential");

    printf("[MEAN_P_PARTICIPATION] %f\n", mean_p_participation);


    //calculate_mean_p_abstention
    float mean_p_abstention = get_mean_p_abstention(content, "parallel");
    mean_p_abstention = get_mean_p_abstention(content, "sequential");

    printf("[MEAN_P_ABSTENTION] %f\n", mean_p_abstention);

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
        struct timeval begin, end;
        double wt1 = 0,wt2 = 0;
        int total_census = 0;

        wt1=omp_get_wtime();
        gettimeofday(&begin, 0);
        // Sequential mode
        if(comp_mode=="sequential"){

            // TO_DO: calculate total in sequential mode


            for (int i = 0; i < content.size(); ++i) {
                total_census += content[i].get_census();
            }

        // Parallel mode
        }else if(comp_mode=="parallel"){

            // TO_DO: calculate total in parallel mode


            #pragma omp parallel for reduction(+:total_census)
            for (int i = 0; i < content.size(); ++i) {
                total_census += content[i].get_census();
            }

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
        printf("[TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);
        return total_census;
}



/**
 * @brief calculate_p_abstention calculates the percentage of abstention
 * @param content vector of recount elements
 * @param comp_mode computational mode, either "sequential" or "parallel"
 * @return number of abstentions in total
 */
int calculate_total_abstention(vector<recount> content, string comp_mode) {
        // Init variables
        struct timeval begin, end;
        double wt1 = 0,wt2 = 0;
        int total_abstentions = 0;

        wt1=omp_get_wtime();
        gettimeofday(&begin, 0);
        // Sequential mode
        if(comp_mode=="sequential"){

            // TO_DO: calculate total in sequential mode

            for (int i = 0; i < content.size(); ++i) {
                total_abstentions += content[i].get_abstentions();
            }

            // Parallel mode
        }else if(comp_mode=="parallel"){

            // TO_DO: calculate total in parallel mode


            #pragma omp parallel for reduction(+:total_abstentions)
            for (int i = 0; i < content.size(); ++i) {
                total_abstentions += content[i].get_abstentions();
            }

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
        printf("[TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);
        return total_abstentions;
}


/**
 * @brief get_min_census Finds the recount object with the minimum census in the content vector.
 * @param content Vector of recount objects.
 * @param comp_mode Computational mode, can be "sequential" or "parallel".
 * @return The recount object with the minimum census.
 */
recount get_min_census(vector<recount> content, string comp_mode) {
        // Init variables
        struct timeval begin, end;
        double wt1 = 0, wt2 = 0;
        recount min_census_recount;

        wt1 = omp_get_wtime();
        gettimeofday(&begin, 0);

        // Sequential mode
        if (comp_mode == "sequential") {
            // Find recount with minimum census in sequential mode

            min_census_recount = content[0];

            for (int i = 0; i < content.size(); i++) {
                if (content[i].get_census() < min_census_recount.get_census()) {
                    min_census_recount = content[i];
                }
            }

        }
        // Parallel mode
        else if (comp_mode == "parallel") {

            min_census_recount = content[0];

            #pragma omp parallel for
            for (int i = 0; i < content.size(); i++) {
                #pragma omp critical
                if (content[i].get_census() < min_census_recount.get_census()) {

                    min_census_recount = content[i];
                }

            }





        } else {
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }

        gettimeofday(&end, 0);
        wt2 = omp_get_wtime();

        // Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds * 1e-6 + microseconds; // in microseconds
        printf("[TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);

        return min_census_recount;
}


/**
 * @brief get_max_census Finds the recount object with the maximun census in the content vector.
 * @param content Vector of recount objects.
 * @param comp_mode Computational mode, can be "sequential" or "parallel".
 * @return The recount object with the maximun census.
 */
recount get_max_census(vector<recount> content, string comp_mode) {
        // Init variables
        struct timeval begin, end;
        double wt1 = 0, wt2 = 0;
        recount max_census_recount;

        wt1 = omp_get_wtime();
        gettimeofday(&begin, 0);

        // Sequential mode
        if (comp_mode == "sequential") {
            // Find recount with minimum census in sequential mode

            max_census_recount = content[0];

            for (int i = 0; i < content.size(); i++) {
                if (content[i].get_census() > max_census_recount.get_census()) {
                    max_census_recount = content[i];
                }
            }

        }
        // Parallel mode
        else if (comp_mode == "parallel") {

            max_census_recount = content[0];

            #pragma omp parallel for
            for (int i = 0; i < content.size(); i++) {
                #pragma omp critical
                if (content[i].get_census() > max_census_recount.get_census()) {

                    max_census_recount = content[i];
                }

            }





        } else {
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }

        gettimeofday(&end, 0);
        wt2 = omp_get_wtime();

        // Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds * 1e-6 + microseconds; // in microseconds
        printf("[TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);

        return max_census_recount;
}


/**
 * @brief calculate_p_participation Calculates the percentage of participation (p_participation) for each recount element in the content vector.
 * @param content The vector of recount elements to be updated
 * @param comp_mode Computational mode, can be "sequential" or "parallel".
 */
void calculate_p_participation(vector<recount>& content, string comp_mode) {
        // Init variables
        struct timeval begin, end;
        double wt1 = 0, wt2 = 0;

        wt1 = omp_get_wtime();
        gettimeofday(&begin, 0);

        // Sequential mode
        if (comp_mode == "sequential") {
            // Calculate participation percentage in sequential mode
            for (int i = 0; i < content.size(); i++) {
                recount* ptr = &content[i];
                int v_cast = ptr->get_v_cast();
                int census = ptr->get_census();
                float p_participation = (v_cast * 100.0) / census;
                ptr->set_p_participation(p_participation);
            }
        }
        // Parallel mode
        else if (comp_mode == "parallel") {
            // Calculate participation percentage in parallel mode
            #pragma omp parallel for
            for (int i = 0; i < content.size(); i++) {
                recount* ptr = &content[i];
                int v_cast = ptr->get_v_cast();
                int census = ptr->get_census();
                float p_participation = (v_cast * 100.0) / census;
                ptr->set_p_participation(p_participation);
            }
        }
        else {
            cout << "[ERROR]: Invalid computational mode. Only 'sequential' and 'parallel' modes are supported." << endl;
            return;
        }

        gettimeofday(&end, 0);
        wt2 = omp_get_wtime();

        // Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds * 1e6 + microseconds; // in microseconds
        printf("[TIME]: %s \t Computational mode: %s \t %.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);

        return;
}



/**
 * @brief calculate_p_abstention Calculates the percentage of abstention (p_abstention) for each recount element in the content vector.
 * @param content The vector of recount elements to be updated
 * @param comp_mode Computational mode, can be "sequential" or "parallel".
 */
void calculate_p_abstention(vector<recount>& content, string comp_mode) {
        // Init variables
        struct timeval begin, end;
        double wt1 = 0, wt2 = 0;

        wt1 = omp_get_wtime();
        gettimeofday(&begin, 0);

        // Sequential mode
        if (comp_mode == "sequential") {
            // Calculate participation percentage in sequential mode
            for (int i = 0; i < content.size(); i++) {
                recount* ptr = &content[i];
                int abstention = ptr->get_abstentions();
                int census = ptr->get_census();
                float p_abstention = (abstention * 100.0) / census;
                ptr->set_p_abstention(p_abstention);
            }
        }
        // Parallel mode
        else if (comp_mode == "parallel") {
            // Calculate participation percentage in parallel mode
            #pragma omp parallel for
            for (int i = 0; i < content.size(); i++) {
                recount* ptr = &content[i];
                int abstention = ptr->get_abstentions();
                int census = ptr->get_census();
                float p_abstention = (abstention * 100.0) / census;
                ptr->set_p_abstention(p_abstention);
            }
        }
        else {
            cout << "[ERROR]: Invalid computational mode. Only 'sequential' and 'parallel' modes are supported." << endl;
            return;
        }

        gettimeofday(&end, 0);
        wt2 = omp_get_wtime();

        // Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds * 1e6 + microseconds; // in microseconds
        printf("[TIME]: %s \t Computational mode: %s \t %.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);

        return;
}



/**
 * @brief get_mean_p_participation calculates the mean percentage of participation from the given content vector.
 * @param content vector of recount elements
 * @param mode computational mode, either "sequential" or "parallel"
 * @return mean percentage of participation
 */
float get_mean_p_participation(vector<recount> content, string mode) {
        float meanParticipation = 0.0;

        struct timeval begin, end;
        double wt1 = 0, wt2 = 0;

        wt1 = omp_get_wtime();
        gettimeofday(&begin, 0);

        // Sequential mode
        if (mode == "sequential") {
            float sumParticipation = 0.0;
            for (int i = 0; i < content.size(); i++) {
                sumParticipation += content[i].get_p_participation();
            }
            meanParticipation = sumParticipation / content.size();
        }
        // Parallel mode
        else if (mode == "parallel") {
            float sumParticipation = 0.0;
            #pragma omp parallel for reduction(+:sumParticipation)
            for (int i = 0; i < content.size(); i++) {
                sumParticipation += content[i].get_p_participation();
            }
            meanParticipation = sumParticipation / content.size();
        } else {
            cout << "[ERROR]: Invalid mode. Only 'sequential' and 'parallel' modes are supported." << endl;
            return meanParticipation; // Return 0 if the mode is invalid
        }

        gettimeofday(&end, 0);
        wt2 = omp_get_wtime();

        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds * 1e6 + microseconds;

        cout << "[TIME]: get_mean_p_participation \tMode: " << mode << "\tElapsed time: " << elapsed << " microseconds" << endl;

        return meanParticipation;
}


/**
 * @brief get_mean_p_abstention calculates the mean percentage of abstention from the given content vector.
 * @param content vector of recount elements
 * @param mode computational mode, either "sequential" or "parallel"
 * @return mean percentage of abstention
 */
float get_mean_p_abstention(vector<recount> content, string mode) {
        float meanAbstention = 0.0;

        struct timeval begin, end;
        double wt1 = 0, wt2 = 0;

        wt1 = omp_get_wtime();
        gettimeofday(&begin, 0);

        // Sequential mode
        if (mode == "sequential") {
            float sumAbstention = 0.0;
            for (int i = 0; i < content.size(); i++) {
                sumAbstention += content[i].get_p_abstention();
            }
            meanAbstention = sumAbstention / content.size();
        }
        // Parallel mode
        else if (mode == "parallel") {
            float sumAbstention = 0.0;
            #pragma omp parallel for reduction(+:sumAbstention)
            for (int i = 0; i < content.size(); i++) {
                sumAbstention += content[i].get_p_abstention();
            }
            meanAbstention = sumAbstention / content.size();
        } else {
            cout << "[ERROR]: Invalid mode. Only 'sequential' and 'parallel' modes are supported." << endl;
            return meanAbstention; // Return 0 if the mode is invalid
        }

        gettimeofday(&end, 0);
        wt2 = omp_get_wtime();

        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds * 1e6 + microseconds;

        cout << "[TIME]: get_mean_p_abstention \tMode: " << mode << "\tElapsed time: " << elapsed << " microseconds" << endl;

        return meanAbstention;
}

