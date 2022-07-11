/************************************
 * Created by :
 * ***** Kemoko KEITA kmkben
 *
 * at June 30th 2022
 *
 * **********************************
 */


#include "disco_utils.hpp"



/********   Functions utils **********/
std::string treat_str(std::string const& str)
{
	std::string copy { str };

	auto first_not_space { std::find_if_not(std::begin(copy), std::end(copy), isspace) };
	copy.erase(std::begin(copy), first_not_space);

	std::reverse(std::begin(copy), std::end(copy));
	first_not_space = std::find_if_not(std::begin(copy), std::end(copy), isspace);
	copy.erase(std::begin(copy), first_not_space);
	std::reverse(std::begin(copy), std::end(copy));

	return copy;
}


/****  Implement the functions of flux is/ostream ****/

std::ostream& operator<<(std::ostream& flux, Artist const& artist)
{
	return flux << artist.name;
}

std::ostream& operator<<(std::ostream& flux, Album const& album)
{
	flux << album.name;
	return flux;
}

std::ostream& operator<<(std::ostream& flux, Sound const& sound)
{
	flux << sound.name << " | " << sound.album << " | " << sound.artist;
	return flux;
}

std::istream& operator>>(std::istream& in, Sound& sound)
{
	std::string word {};
	std::ostringstream flux {};

	while (in >> word && word != "|")
	{
		flux << word << " ";
	}

	std::string sound_name { flux.str() };
       	if (sound_name.empty())
	{
		sound_name = "Unknown sound";
	}	

	sound.name = treat_str(sound_name);
	flux.str(std::string {});

	while (in >> word && word != "|")
	{
		flux << word << " ";
	}

	std::string album_name { flux.str() };
	if (album_name.empty())
	{
		album_name = "Unknown album";
	}

	sound.album.name = treat_str(album_name);
	flux.str(std::string {});

	while (in >> word)
	{
		flux << word << " ";
	}

	std::string artist_name { flux.str() };
	if (artist_name.empty())
	{
		artist_name = "Unknown artist";
	}

	sound.artist.name = treat_str(artist_name);
	flux.str( std::string {} );

	return in;
}



/************     Test creation sound operator>>   ***************/
void test_creation_sound_enter_complete()
{
	std::istringstream in {"Frica | Frica | Carla's Dreams" };
	Sound sound{};

	in >> sound;

	//std::cout << "\"" << sound.name << "\"" << std::endl;
	assert(sound.name == "Frica" && u8"The sound name should be Frica");
	assert(sound.album.name == "Frica" && u8"The Album should be Frica");
	//std::cout << "\"" << sound.artist.name << "\"" << std::endl;
	assert(sound.artist.name == "Carla's Dreams" && u8"The artist name should be Carla's Dreams");
	
}

void test_creation_sound_with_space()
{
	std::istringstream in {"Levels   |    Levels   |    Avicii" };
	Sound sound{};

	in >> sound;

	assert(sound.name == "Levels" && "The sound name should be Levels");
	assert(sound.album.name == "Levels" && "The album should be Levels");
	assert(sound.artist.name == "Avicii" && "The artist name should be Avicii");
}

void test_creation_sound_artist()
{
	std::istringstream in { "Lough Radio | | Enric Iglesias" };
	Sound sound{};

	in >> sound;

	assert(sound.name == "Lough Radio" && "The sound name should be Lough Radio");
	assert(sound.album.name == "Unknown album" && "The album should be unknown");
	assert(sound.artist.name == "Enric Iglesias" && "The artist name should be Enric Iglesias");
}

void test_creation_sound_only()
{
	std::istringstream in { "Dual of the fates | |" };
	Sound sound{};

	in >> sound;

	assert(sound.name == "Dual of the fates" && "The sound name should be Dual of the fates");
	assert(sound.album.name == "Unknown album" && "The album should be unknown");
	assert(sound.artist.name == "Unknown artist" && "The artist should be unknown");
}

void test_creation_sound_empty()
{
	std::istringstream in { "| |" };
	Sound sound{};

	in >> sound;

	assert(sound.name == "Unknown sound" && "The sound name should be unknown");
	assert(sound.album.name == "Unknown album" && "The album should be unknown");
	assert(sound.artist.name == "Unknown artist" && "The artist should be unknown");
}


/*************   Functions Save and Load of the file   ******************/
void save(Discography const& disco, std::string const& fileName)
{
	std::ofstream file { fileName };

	if (!file)
	{
		throw std::runtime_error("Impossible to open the file");
	}

	for (Sound const& sound : disco)
	{
		file << sound << std::endl;
	}
}

void load(Discography& disco, std::string const& fileName)
{
	std::ifstream file { fileName };

	if(!file)
	{
		throw std::runtime_error("Impossible to open the file");
	}

	std::string line {};

	while (std::getline(file, line))
	{
		Sound sound{};

		std::istringstream flux { line };
		flux >> sound;

		disco.push_back(sound);
	}
}



/***********   Functions for short and print      ********************/
void sort_sound(Discography& disco)
{
	std::sort(std::begin(disco), std::end(disco), [](Sound const& lhs, Sound const& rhs)
	{
		return lhs.name < rhs.name;
	});
}

void sort_album(Discography& disco)
{
	std::sort(std::begin(disco), std::end(disco), [](Sound const& lhs, Sound const& rhs)
	{
		if (lhs.album.name < rhs.album.name) 
			return true;

		return lhs.album.name == rhs.album.name && lhs.name < rhs.name;
	});
}

void sort_artist(Discography& disco)
{
	std::sort(std::begin(disco), std::end(disco), [](Sound const& lhs, Sound const& rhs)
	{
		if (lhs.artist.name < rhs.artist.name)
			return true;

		if (lhs.artist.name == rhs.artist.name)
		{
			if (lhs.album.name < rhs.album.name)
				return true;

			return lhs.album.name == rhs.album.name && lhs.name < rhs.name;
		}

		return false;
	});
}


void print_sound(Discography const& disco)
{
	for (Sound const& sound : disco)
	{
		std::cout << "--> " << sound << std::endl;
	}
}

void print_album(Discography const& disco)
{
	Album precedent_album {};
	for (Sound const& sound : disco)
	{
		if (sound.album.name != precedent_album.name)
		{
			std::cout << "--> " << sound.album << " | " << sound.artist << std::endl;
		}
		std::cout << "\t/--> " << sound.name << std::endl;

		precedent_album = sound.album;
	}
}

void print_artist(Discography const& disco)
{
	Artist precedent_artist {};
	Album precedent_album {};

	for (Sound const& sound : disco)
	{
		if (sound.artist.name != precedent_artist.name)
		{
			std::cout << "--> " << sound.artist << std::endl;
		}

		if (sound.album.name != precedent_album.name)
		{
			std::cout << "\t/--> " << sound.album << std::endl;
		}
		std::cout << "\t\t--> " << sound.name << std::endl;

		precedent_artist = sound.artist;
		precedent_album = sound.album;
	}
}

void print(Discography& disco, Print print_mode)
{
	if (print_mode == Print::Album)
	{
		sort_album(disco);
		print_album(disco);
	}
	else if (print_mode == Print::Artist)
	{
		sort_artist(disco);
		print_artist(disco);
	}
	else if (print_mode == Print::Sound)
	{
		sort_sound(disco);
		print_sound(disco);
	}
	else
	{
		throw std::runtime_error("Invalid command");
	}

}


/************      Functions to run Commands     ********************/
std::string getCommand()
{
	std::cout << "> ";

	std::string command;
	std::getline(std::cin, command);

	return command;
}

std::tuple<Command, std::string> compileCommand(std::string const& command_text)
{
	std::istringstream flux { command_text };

	std::string first_word{};
	flux >> first_word;
	first_word = treat_str(first_word);

	std::string instructions{};
	std::getline(flux, instructions);
	instructions = treat_str(instructions);

	if (first_word == "print")
	{
		return {Command::print, instructions};
	} 
	else if (first_word == "add")
	{
		return { Command::add, instructions };
	}
	else if (first_word == "save")
	{
		return { Command::save, instructions };
	}
	else if (first_word == "load")
	{
		return { Command::load, instructions };
	}
	else if (first_word == "quit")
	{
		return { Command::quit, std::string{} };
	}
	else
	{
		throw std::runtime_error("Invalid command");
	}
}

bool runCommand(Discography& disco, Command command, std::string const& instructions)
{
	if (command == Command::print)
	{
		if (instructions == "artists")
		{
			print(disco, Print::Artist);	
		}
		else if (instructions == "albums")
		{
			print(disco, Print::Album);
		}
		else if (instructions == "sounds")
		{
			print(disco, Print::Sound);
		}
		else
		{
			throw std::runtime_error("invalid command. type helpto get help");
		}
	}
	else if (command == Command::add)
	{
		std::istringstream flux{ instructions };
		Sound sound{};
		flux >> sound;

		disco.push_back(sound);
	}
	else if (command == Command::save)
	{
		save(disco, instructions);
	}
	else if (command == Command::load)
	{
		load(disco, instructions);
	}
	else if (command == Command::quit)
	{
		return false;
	}

	return true;
}
