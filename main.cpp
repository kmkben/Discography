#include "disco_utils.hpp"


int main()
{
	/* We start to the tests if the code is correct the program continue otherwise we will go to fix the error */
	test_creation_sound_enter_complete();
	test_creation_sound_with_space();
	test_creation_sound_artist();
	test_creation_sound_only();
	test_creation_sound_empty();


	//fill the disco 
	Artist const yans{ "Yans" };
	Artist const the_chainsmokers{ "The ChainSmokers" };
	Artist const alan_walker{ "Alan Walker" };

	Album const cli_cli_pan{ "Cli Cli Pan" };
	Album const dont_let_me_down{ "Don't let me down" };
	Album const i_am_fadded{ "I am fadded" };
	Album const spectre{ "Spectre" };

	Sound const cliclipan{ "Cli Cli Pan", yans, cli_cli_pan };
	Sound const dontLetMeDown{ "Don't let me Down", the_chainsmokers, dont_let_me_down };
	Sound const IamFadded{ "I am Fadded", alan_walker, i_am_fadded };
	Sound const darkside{ "Darkside", alan_walker, i_am_fadded };
	Sound const spectres{ "Spectre", alan_walker, spectre };

	Discography disco{ cliclipan, dontLetMeDown, IamFadded, darkside, spectres };

	bool keep{ true };

	do
	{
		try
		{
			std::string enter{ getCommand() };
			auto[command, instructions] = compileCommand(enter);
			instructions = treat_str(instructions);
			keep = runCommand(disco, command, instructions);
		}
		catch(std::runtime_error const& exception)
		{
			std::cout << "Error: " << exception.what() << std::endl;
		}
	} while(keep);

	return 0;
}
