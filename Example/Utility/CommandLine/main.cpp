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
 *  @brief  Main function.
 *  @param  argc [i] argument count
 *  @param  argv [i] argument values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    /* Options:
     *   -a <string> : parameter a (1 value, required)
     *   -b <int int int> : parameter b (3 values, not required)
     *   intput value (reuqired)
     *
     * Examples:
     *   ./CommandLine -a message -b 1 2 3 value
     *   ./CommandLine -a message value
     *   ./CommandLine -h
     */

    // Parse given command line options.
    kvs::CommandLine commandline( argc, argv );
    commandline.addHelpOption();
    commandline.addOption( "a","Parameter a (string).", 1, true );
    commandline.addOption( "b","Parameter b (int*3).", 3, false );
    commandline.addValue( "input value.", true );
    if ( !commandline.parse() ) exit( EXIT_FAILURE );

    // Get the parameter which is given by the option 'a'.
    std::string a = commandline.optionValue<std::string>("a");

    // Get the parameters which are given by the option 'b'.
    int b[3] = { 0, 0, 0 }; // initial value
    if ( commandline.hasOption("b") )
    {
        b[0] = commandline.optionValue<int>("b",0);
        b[1] = commandline.optionValue<int>("b",1);
        b[2] = commandline.optionValue<int>("b",2);
    }

    // Get the input value as a string here.
    std::string value = commandline.value<std::string>();

    // Output the given parameters.
    std::cout << "Option 'a': " << a << std::endl;
    std::cout << "Option 'b': " << b[0] << " " << b[1] << " " << b[2] << std::endl;
    std::cout << "Input value: " << value << std::endl;

    return 0;
}
