#ifndef GENERATOR_HELPER_H
#define GENERATOR_HELPER_H

#include <string>
#include <apr_pools.h>

class GeneratorHelper{
public:
    GeneratorHelper( std::string sourceDir, 
                     std::string binaryDir,
                     std::string cmakeCommand, 
                     std::string cmakeGenerator );
    ~GeneratorHelper();

    std::string getOutputDirectory();
    void createOutputDirectory();

    void generateBuildFiles();
    /**
     * Run the build.
     * @return true if the build succeded, false otherwise
     */
    bool buildProject();
    bool generateAndBuild();

private:
    std::string m_sourceDir;
    std::string m_binaryDir;
    std::string m_buildDir;
    std::string m_cmakeCommand;
    std::string m_cmakeGenerator;
    apr_pool_t* m_pool;
};

#endif /* GENERATOR_HELPER_H */
