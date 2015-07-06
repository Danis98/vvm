#include <main.h>

//Parsed commands
cmd_list cmds;
//Variables and their characteristics
variable_map var_map;

std::ifstream inFile;

void wrong_usage_msg(int arg_num){
	std::cout<<"[USAGE] vvm <input file>, "<<
		arg_num<<" args supplied\n";
	exit(0);
}

void invalid_arg_msg(const char* arg){
	std::cout<<"[INVALID ARGUMENT] "<<arg<<"\n";
	exit(0);
}

int main(int argc, const char* argv[]){
	//Check and parse the command line arguments
	if(argc<MIN_ARGC || argc>MAX_ARGC){
		wrong_usage_msg(argc-1);
	}
	
	//Leaving room for more future command line options
	std::string filename;
	bool inFileSupplied=false;
	for(int i=1;i<argc;i++){
		if(file_exists(argv[i])){
			filename=argv[i];
			inFileSupplied=true;
		}
		else{
			invalid_arg_msg(argv[i]);
		}
	}
	
	if(!inFileSupplied){
		std::cout<<"[ERROR] Input file not defined\n";
		exit(0);
	}
	
	inFile.open(filename);
	
	
	
	return 0;
}