#include <cpr/cpr.h>
#include <iostream>
#include <json/json.h>
#include <string>
#include <filesystem>
#include <format>
#include <algorithm>
#define VERSION "1.2.2"


void fetchpkg( char** argv, int argc );
bool check_exists( std::string package_name );
void download_package(char** argv, int argc );
void delete_package( char** argv, int argc );
void search( std::string package_name, int num);
void print_help();
void print_version();
void noargs( char* n ) { std::cout << n << ": no arguments specified. (use -h for help)\n"; }


int main( int argc, char** argv ) {
    if ( argc == 1 ) {
       std::cout << argv[0] << ": no operation specified. (use -h for help)\n";
       return 1;
    }
    if ( strcmp( argv[1], "fetch" ) == 0 || strcmp( argv[1], "-F") == 0) { 
        if ( argc <= 3 ) {
            fetchpkg( argv, argc );
        } else {
            noargs( argv[0] );
        } } 
    else if ( strcmp( argv[1], "install" ) == 0 || strcmp( argv[1], "-S") == 0 ) {
         if ( argc <= 3 ) {
            download_package( argv, argc ); 
        } else {
            noargs( argv[0] );
        }}
    else if ( strcmp( argv[1], "remove" ) == 0 || strcmp( argv[1], "-R") == 0 ) { 
        if ( argc <= 3 ) {
            delete_package( argv, argc );
        } else {
            noargs( argv[0] );
        } }
    else if ( strcmp( argv[1], "search" ) == 0 || strcmp( argv[1], "-Ss") == 0 ) {
        if ( argc <= 3 ) {
            noargs( argv[0]); }
        if ( argc == 3 ) {
            search( argv[2], 5 );
        } else {
            search( argv[2], std::stoi(argv[3]));
        } }
    else if ( strcmp( argv[1], "-h" ) == 0 || strcmp( argv[1], "--help") == 0 ) { print_help(); }
    else if ( strcmp( argv[1], "-v" ) == 0 || strcmp( argv[1], "--version" ) == 0 ) { print_version(); }
    else { std::cout << "invalid option '" << argv[1] << "'\n"; return 1;}
    
	return 0;
}

void search( std::string package_name, int MAX_RESULTS ) {
    const std::string API_ENDPOINT = "https://aur.archlinux.org/rpc/v5/search/";
    const cpr::Response REQ_RESPONSE = cpr::Get( cpr::Url{ API_ENDPOINT+package_name+"?by=name-desc" } );
    Json::Value json_results;
    Json::Reader reader;
    reader.parse(REQ_RESPONSE.text, json_results);
    std::cout << "found " << json_results["resultcount"] << " packages.\n\n";
    unsigned int cur_result = 1;
    for (auto iterable : json_results["results"]) {
        if ( cur_result >= MAX_RESULTS+1 ) {
		break;
	}
	std::cout << iterable["Name"].asString() << " v" << iterable["Version"].asString() << "\n";
        std::cout << iterable["Description"].asString() << "\n\n";
	cur_result++;
    }
}

void fetchpkg( char** argv, int argc ) {
    for ( int i=2; i<argc; i++ ) {
        std::string package_name = argv[i];
        if ( check_exists(package_name) == true ) {
            const std::string clone_prompt = "git clone https://aur.archlinux.org/" + package_name + ".git";
	    	system( clone_prompt.data() );        
        } else {
            std::cout << "the package " << package_name << " doesn't exist\n"; } }
}

void print_version() {
    std::cout <<  " _   _  ___    yo version " << VERSION << "\n" <<  
                  "| | | |/ _ \\   copyright (C) 2024-2024 \n" <<
                  "| |_| | (_) | \n" <<
                  "\\__,  |\\___/ \n" << 
                  "|____/\n";       
}

void print_help() {
    std::cout << "usage:    yo <operation> [...]\n" <<
    "operations:\n" <<
    "   yo {-h --help}\n" <<
    "   yo {-v --version}\n" <<
    "   yo {install -S}\n" <<
    "   yo {remove  -R}\n" <<
    "   yo {search  -Ss} ... {num of results}\n" <<
    "   yo {fetch -F}\n";
}


void download_package( char** argv, int argc ) {
    for ( int i=2; i<argc; i++ ) {
        std::string package_name = argv[i];
        if ( check_exists( package_name ) == true ) {
	    const std::string HOME_PATH( getenv( "HOME" ) );
            const std::string pkg_path =  HOME_PATH + "/." + package_name;
            std::filesystem::create_directory( pkg_path );
            const std::string clone_prompt = "git clone https://aur.archlinux.org/" + package_name + ".git ~/." + package_name;
		    system( clone_prompt.data() );
            const std::string makepkg_prompt = "cd " + pkg_path + " && makepkg -si";
            system( makepkg_prompt.data() );
            std::filesystem::remove_all( pkg_path );
	    } else {
            std::cout << "the package " << package_name << " doesn't exist\n";
        }
    }
    
}

void delete_package ( char** argv, int argc ) {
    for ( int i=2; i<argc; i++ ) {
        std::string package_name = argv[i];
        if ( check_exists(package_name) == true ) {
            const std::string pacman_prompt = "sudo pacman -R " + package_name;
            system( pacman_prompt.data() );
        } else {
            std::cout << "the package " << package_name << " doesn't exist\n";
    }    }
}

bool check_exists( std::string package_name ) {
    const std::string API_ENDPOINT = "https://aur.archlinux.org/rpc/v5/info/";
    const cpr::Response REQ_RESPONSE = cpr::Get( cpr::Url{ API_ENDPOINT+package_name } );
    Json::Value json_results;

    Json::Reader reader;
    reader.parse( REQ_RESPONSE.text, json_results );
    
    return json_results["resultcount"].asInt();;
}

