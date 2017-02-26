/*main.cpp*/

//
// Netflix movie analysis: top-10 by rating and # of reviews.
//
// Sarah Kazi
// xCode
// U. of Illinois, Chicago
// CS341, Spring 2017
// Project #01:
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

//
// getFileName: inputs a filename from the keyboard, making sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is terminated.
//

/*movie class*/
class Movie
{
public:
    //variables for ID, name, and how many reviews it has
    int    movieID;
    string movieName;
    int    pubYear;
    int    numberOfReviews ;
    int    rating;


    //constructor
    Movie(int ID, string name, int year)
    : movieID(ID), movieName(name), pubYear(year)
    {
        numberOfReviews = 0;
        rating = 0;
    }

    //methods to return name, id, increase reviews
    string getName(){
        return movieName;
    }
    int getID(){
        return movieID;
    }

    //method to calculate average rating
    double getAverageRating(){
        if (numberOfReviews == 0)
            return 0;
        else
            return (double)rating/ (double)numberOfReviews;
    }

};

//class for reviews
class Review
{
public:
    int movieID;
    int userID;
    int movieRating;

    Review(int movie, int user, int rating)
    : movieID(movie), userID(user), movieRating(rating)
    {}

    int getID(){
        return movieID;
    }
    int getRating(){
        return movieRating;
    }
};

string getFileName()
{
  string filename;

  // input filename from the keyboard:
  getline(cin, filename);

  // make sure filename exists and can be opened:
  ifstream file(filename);
  if (!file.good())
  {
    cout << "**Error: cannot open file: " << filename << endl;
    std::terminate();
  }


  return filename;
}

//open and parse the movie file to store into vector
void openMovieFile(string filename, vector<Movie>& movies){
    ifstream file(filename);
    string line, ID, Name, PubYear;

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);

        getline(ss, ID, ',');
        getline(ss, Name, ',');
        getline(ss, PubYear, ',');

        Movie M(stoi(ID), Name, stoi(PubYear));

        //push to the end of the vector:
        movies.push_back(M);

    }


}

//open and parse the review file to store into vector
void openReviewFile(string filename, vector<Review>& reviews){
    ifstream file(filename);

    string line, movieID, userID, rating;

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);

        getline(ss, movieID, ',');
        getline(ss, userID, ',');
        getline(ss, rating, ',');
        getline(ss, line);

        Review R(stoi(movieID), stoi(userID), stoi(rating));

        //push to the end of the vector:
        reviews.push_back(R);

    }

}

//method to store averages and increase number of reviews
void getAverages(vector<Review>& r, vector<Movie>& m){
    //iterate through both vectors, when movie ID matches, add to ratings to calculate average and
    //increase number of reviews
    for (auto& x: m) {
        for (auto& y: r) {
            if(x.getID() == y.getID()){
                x.numberOfReviews++;
                x.rating += y.movieRating;
            }
        }
    }
}
//method to sort arrays and print out top ten
void findTopTenRating(vector<Movie>& m){
    //built in sort function to swap when average rating is less than the movie next to it
    sort(m.begin(), m.end(),
         [](Movie& m1, Movie &m2)
            {
                if(m1.getAverageRating() > m2.getAverageRating())
                    return true;
                else if(m1.getAverageRating() < m2.getAverageRating())
                    return false;
                else {
                    if(m1.getName() < m2.getName())
                        return true;
                    else
                        return false;
                }

            }
    );
    cout << std::fixed;
    cout << std::setprecision(6);
    cout << "**Top-10 by Rating**" << endl;
    //loop through first ten which are now sorted by average rating
    for(int i = 0; i < 10; i++){
        cout << i+1 << ": " << m[i].getAverageRating() << ",'" << m[i].getName() << "'" << endl;
    }

}
void findTopTenReviews(vector<Movie>m){
    //sort function again but this time according to how many reviews it has
    sort(m.begin(), m.end(),
         [](Movie& m1, Movie &m2)
         {
             if(m1.numberOfReviews > m2.numberOfReviews)
                 return true;
             else if(m1.numberOfReviews < m2.numberOfReviews)
                 return false;
             else {
                 if(m1.getName() < m2.getName())
                     return true;
                 else
                     return false;
             }

         }
         );
    cout << "**Top-10 by Num Reviews**" << endl;
    //display top ten bu number of reviews
    for(int i = 0; i < 10; i++){
        cout << i+1 << ": " << m[i].numberOfReviews << ",'" << m[i].getName() <<"'" << endl;
    }

}


int main()
{
  // get filenames from the user/stdin:
    string MoviesFileName = getFileName();
    string ReviewsFileName = getFileName();

    //initialize both vectors
    vector <Movie> movies;
    vector <Review> reviews;


    //store from file into vectors
    openMovieFile(MoviesFileName, movies);
    openReviewFile(ReviewsFileName, reviews);

    //print out how many movies and reviews there are
    cout << "Movies: " << movies.size() << endl;
    cout << "Reviews "<< reviews.size() << endl;

    //store averages and number of reviews by looping through vectors
    getAverages(reviews, movies);

    //sort and print out top ten
    findTopTenRating(movies);
    findTopTenReviews(movies);



  // done:
  return 0;
}
