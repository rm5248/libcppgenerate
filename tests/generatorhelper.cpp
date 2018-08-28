#include <apr_pools.h>
#include <apr_file_io.h>
#include <apr_thread_proc.h>
#include <iostream>

#include "generatorhelper.h"

GeneratorHelper::GeneratorHelper( std::string sourceDir, 
                                  std::string binaryDir, 
                                  std::string cmakeCommand, 
                                  std::string cmakeGenerator ) :
    m_sourceDir( sourceDir ),
    m_binaryDir( binaryDir ),
    m_cmakeCommand( cmakeCommand ),
    m_cmakeGenerator( cmakeGenerator ){
    apr_pool_create( &m_pool, NULL );
}

GeneratorHelper::~GeneratorHelper(){
    apr_pool_destroy( m_pool );
}

std::string GeneratorHelper::getOutputDirectory(){
    std::string ret = m_binaryDir;
    ret.append( "/build" );
    return ret;
}

void GeneratorHelper::createOutputDirectory(){
    apr_dir_make( getOutputDirectory().c_str(),
        APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
        m_pool
    );
}

void GeneratorHelper::generateBuildFiles(){
    apr_proc_t newProc;
    int exitcode;
    apr_exit_why_e why;
    apr_status_t status;
    apr_procattr_t* attr;
    std::string properSourceDir = "../";
    properSourceDir += m_sourceDir;
    const char* args[ 5 ];
    args[ 0 ] = m_cmakeCommand.c_str();
    args[ 1 ] = "-G";
    args[ 2 ] = m_cmakeGenerator.c_str();
    args[ 3 ] = properSourceDir.c_str();
    args[ 4 ] = NULL;

std::cout << "output dir is " << getOutputDirectory() << std::endl;
for( int x = 0; x < 4; x++ ){
std::cout << "arg " << x << ": " << args[ x ] << std::endl;
}

    apr_procattr_create( &attr, m_pool );
    apr_procattr_dir_set( attr, getOutputDirectory().c_str() );
    status = apr_proc_create( &newProc, 
                     m_cmakeCommand.c_str(),
                     args,
                     NULL,
                     attr,
                     m_pool );
    apr_proc_wait( &newProc, &exitcode, &why, APR_WAIT );
}

bool GeneratorHelper::buildProject(){
    apr_proc_t newProc;
    int exitcode;
    apr_exit_why_e why;
    apr_procattr_t* attr;
    const char* args[ 6 ];
    std::string outputDir = getOutputDirectory();
    args[ 0 ] = m_cmakeCommand.c_str();
    args[ 1 ] = "--build";
    args[ 2 ] = "./build";
    args[ 3 ] = "--config";
    args[ 4 ] = "Release";
    args[ 5 ] = NULL;

    apr_procattr_create( &attr, m_pool );
    apr_proc_create( &newProc, 
                     m_cmakeCommand.c_str(),
                     args,
                     NULL,
                     attr,
                     m_pool );
    apr_proc_wait( &newProc, &exitcode, &why, APR_WAIT );

    return exitcode == 0;
}

bool GeneratorHelper::generateAndBuild(){
    createOutputDirectory();
    generateBuildFiles();
    return buildProject();
}
