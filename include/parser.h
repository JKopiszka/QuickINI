/**
 * @file parser.h
 * @author Jakub Kopiszka (kopiszkajakub20@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef PARSER_H
#define PARSER_H

//! STRUCTS !//

//* INI's file parameter structure.
typedef struct
{
    char *key;
    char *value;
} INIParameter;

//* INI's file section structure
typedef struct
{
    char *name;
    INIParameter *parameters;
    int parameter_count;
} INISection;

//* INI's file section 
typedef struct
{
    INISection *sections;
    int section_count;
} INIFile;

//! FUNCTIONS !//

//? Function loading ini file
INIFile *ini_load(const char *path);

//? Function parsing ini's file content to string
char *load_ini_to_string(FILE *file);

//? Function returning ini's file sections array
INISection **get_sections(char *file_content);

//? Function setting file's pointer free
void ini_free(INIFile *file);

#endif