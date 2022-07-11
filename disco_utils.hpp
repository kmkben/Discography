/**********************************
 * Created by :
 * **** Kemoko KEITA kmkben
 *
 * on June 30th
 *
 * ********************************
 */


#ifndef DISCO_UTILS_HPP
#define DISCO_UTILS_HPP


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <fstream>
#include <sstream>
#include <tuple>



enum class Command { print, add, save, load, quit };
enum class Print { Artist, Album, Sound };

 
struct Artist
{
	std::string name;
};


struct Album
{
	std::string name;
};

struct Sound
{
	std::string name;
	Artist artist;
	Album album;
};

using Discography = std::vector<Sound>;


/*** Others functions utils ********/
std::string treat_str(std::string const&);


/* Operators flux */
std::ostream& operator<<(std::ostream&, Artist const&);
std::ostream& operator<<(std::ostream&, Album const&);
std::ostream& operator<<(std::ostream&, Sound const&);
std::ostream& operator>>(std::ostream&, Sound&);

/**********   Test unitaire for operator>>     ******************/
void test_creation_sound_enter_complete();
void test_creation_sound_with_space();
void test_creation_sound_artist();
void test_creation_sound_only();
void test_creation_sound_empty();


/**********   Functions for Save and Load the file of stockage    ****************/
void save(Discography const&, std::string const&);
void load(Discography const&, std::string const&);


/*************   Functions for print and short    ****************/
void sort_sound(Discography&);
void sort_album(Discography&);
void sort_artist(Discography&);

void print_sound(Discography const&);
void print_album(Discography const&);
void print_artist(Discography const&);

void print(Discography&, Print);


/************    Command in console    ******************/
std::string getCommand();
std::tuple<Command, std::string> compileCommand(std::string const&);
bool runCommand(Discography&, Command, std::string const&);


#endif  //DISCO_UTILS_HPP
