/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::CommandLine class.
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include <iostream>
#include <string>
#include <kvs/CommandLine>


/*===========================================================================*/
/**
 *  @brief  Argument class.
 *  By using the kvs::CommandLine class, users can parse command line options
 *  and define some options in your original class which is inherited the
 *  kvs::CommandLine class by using the add_help_option, add_option and so on.
 */
/*===========================================================================*/
class Argument : public kvs::CommandLine
{
public:

    Argument( int argc, char** argv ):
        kvs::CommandLine( argc, argv )
    {
        // Add help option (generate help message automatically).
        add_help_option();

        // Add options.
        add_option( "a","Parameter a (string).", 1, true ); // 1 value, required
        add_option( "b","Parameter b (int*3).", 3, false ); // 3 values, not required

        // Add input value.
        add_value( "input value.", true ); // required
    }
};

/*===========================================================================*/
/**
 *  @brief  Main function.
 *  @param  argc [i] argument count
 *  @param  argv [i] argument values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    // Parse given command line options.
    Argument arg( argc, argv );
    if( !arg.parse() ) exit( EXIT_FAILURE );

    // Get the parameter which is given by the option 'a'.
    std::string a = ""; // initial value
    if( arg.hasOption("a") )
    {
        a = arg.optionValue<std::string>("a");
    }

    // Get the parameters which are given by the option 'b'.
    int b[3] = { 0, 0, 0 }; // initial value
    if( arg.hasOption("b") )
    {
        b[0] = arg.optionValue<int>("b",0);
        b[1] = arg.optionValue<int>("b",1);
        b[2] = arg.optionValue<int>("b",2);
    }

    // Output the given parameters.
    std::cout << "Option 'a': " << a << std::endl;
    std::cout << "Option 'b': " << b[0] << " " << b[1] << " " << b[2] << std::endl;

    return 0;
}
