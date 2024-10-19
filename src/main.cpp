#include "include/cpr/cpr.h"
#include <iostream>
#include <json/json.h>
#include <string>
#include <filesystem>
#include <format>

#define VERSION "1.0.0"

bool fetch_package( std::string package_name );
bool check_exists( std::string package_name );
void download_package( std::string package_name );
void delete_package ( std::string package_name );
void print_help();
void print_version();

std::string s_getenv(std::string const& key)
{
    char const* val = getenv(key.c_str()); 
    return val == NULL ? std::string() : std::string(val);
}

int main( int argc, char** argv ) {
    if ( argc < 2 ) {
        std::cout << argv[0] << ": no operation specified. -h for help\n";
        return 1;
    }
    if ( strcmp( argv[1], "search" ) == 0 || strcmp( argv[1], "-Q") == 0) { check_exists(argv[2]); } 
    else if ( strcmp( argv[1], "install" ) == 0 || strcmp( argv[1], "-S") == 0 ) { download_package(argv[2]); }
    else if ( strcmp( argv[1], "remove" ) == 0 || strcmp( argv[1], "-R") == 0 ) { delete_package(argv[2]); }
    else if ( strcmp( argv[1], "-h" ) == 0 || strcmp( argv[1], "--help") == 0 ) { print_help(); }
    else if ( strcmp( argv[1], "-v" ) == 0 || strcmp( argv[1], "--version" ) == 0 ) { print_version(); }
    else { std::cout << "invalid option '" << argv[1] << "'\n"; return 1;}
    
	return 0;
}

void fetch( std::string package_name ) {
    if ( check_exists(package_name) == true ) {
        const std::string clone_prompt = "git clone https://aur.archlinux.org/" + package_name + ".git";
		system( clone_prompt.data() );        
    } else {
        std::cout << "the package " << package_name << " doesn't exist\n";
    }
}

void print_version() {
    const std::string yo_version = VERSION;
    std::cout <<  " _   _  ___    yo version " << yo_version << "\n" <<  
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
    "   yo {search  -Q}\n";
}


void download_package( std::string package_name ) {
    if ( check_exists(package_name) == true ) {
        //std::stringstream promptstream; promptstream << "git clone https://aur.archlinux.org/" << package_name << ".git"; 
        //const std::string prompt = promptstream.str();
        const std::string pkg_path = s_getenv( "HOME" ) + "/." + package_name;
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

void delete_package ( std::string package_name ) {
    if ( check_exists(package_name) == true ) {
        const std::string pacman_prompt = "sudo pacman -R " + package_name;
        system( pacman_prompt.data() );
    } else {
        std::cout << "the package " << package_name << " doesn't exist\n";
    }
}

bool check_exists( std::string package_name ) {
    const std::string INFO_ENDPOINT_URL = "https://aur.archlinux.org/rpc/v5/info/";
    const cpr::Response REQ_RESPONSE = cpr::Get(cpr::Url{INFO_ENDPOINT_URL+package_name});
    Json::Value json_results;

    Json::Reader reader;
    reader.parse(REQ_RESPONSE.text, json_results);
    const Json::Value results = json_results["resultcount"];
    
    const bool result = results.asInt();
    if ( result == true ) {
        std::cout << "Package " << package_name << " was found\n";
    } else {
        std::cout << "Package " << package_name << " wasn't found.\n";
    }
    return result;
}
