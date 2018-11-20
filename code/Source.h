#pragma once

/**
	Opens file using fstream and file name
	@param is file stream to open
	@param file_name
	@return true if the opening process was succeeded
*/
bool open_file(std::fstream & is, const std::string & file_name);
/**delete the conten of the file before writing*/
bool open_file_output(std::fstream & is, const std::string & file_name);

/**
	Tests whether a given token is a keyword or not
	@param is file stream contains a list of keywords to search in.
	@param token string to be tested if it's in that list or not
	@return true if token is a keyword
*/
bool is_keyword(std::fstream & is, const std::string & token);

/**
	Tests whether a given token is a special symbol (i.e. +, -, *, ..., etc) or not
	@param is file stream contains a list of symbols to search in.
	@param token char to be tested if it's in that list or not
	@return true if token is a special symbol
*/
bool is_special_symbol(std::fstream & is, char token);
