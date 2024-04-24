#include <sys/stat.h>
#include <iostream>
#include <gtest/gtest.h>

#include "utilities/env.h"

std::string extract_graph_name(const std::string& input_string) {
    // Find the last '/' character in the input string
    size_t last_slash_pos = input_string.rfind('/');

    // If a '/' is found and it's not the last character in the string
    if (last_slash_pos != std::string::npos && last_slash_pos < input_string.length() - 1) {
        // Extract the substring after the last '/'
        std::string graph_name = input_string.substr(last_slash_pos + 1);

        // Find the position of the '.' character in the extracted substring
        size_t dot_pos = graph_name.find('.');

        // If a '.' is found and it's not the first character in the substring
        if (dot_pos != std::string::npos && dot_pos > 0) {
            // Extract the part between the last '/' and the '.' to get the graph_name
            graph_name = graph_name.substr(0, dot_pos);
            return graph_name;
        }
    }

    // Return an empty string if the format is not as expected
    return "";
}

/**
 * @brief Splice the directory path and file name to generate the complete path of .sg graph
 * @details It is used for unit test to generate the path of sparse graph matrix required for test, and print the name of the graph matrix.
 * @param path
 * @param file
 * @return std::string the complete path
 */
std::string getFullPath_sg(const std::string path, const std::string file)
{
    std::cout << "The Matrix Name : " << file << std::endl;
    std::string full_path = std::string(PROJECT_PATH) + path + file + "/" + file + ".sg";
    std::cout << full_path << std::endl;
    return full_path;
}

/**
 * @brief Splice the directory path and file name to generate the complete path of .wsg graph
 * @details It is used for unit test to generate the path of sparse graph matrix required for test, and print the name of the graph matrix.
 * @param path
 * @param file
 * @return std::string the complete path
 */
std::string getFullPath_wsg(const std::string path, const std::string file)
{
    std::cout << "The Matrix Name : " << file << std::endl;
    std::string full_path = std::string(PROJECT_PATH) + path + file + "/" + file + ".wsg";
    std::cout << full_path << std::endl;
    return full_path;
}

/**
 * @brief Splice the directory path and file name to generate the complete path of .mtx graph
 * @details It is used for unit test to generate the path of sparse graph matrix required for test, and print the name of the graph matrix.
 * @param path
 * @param file
 * @return std::string the complete path
 */
std::string getFullPath_mtx(const std::string path, const std::string file)
{
    std::cout << "The Matrix Name : " << file << std::endl;
    std::string full_path = std::string(PROJECT_PATH) + path + file + "/" + file + ".mtx";
    std::cout << full_path << std::endl;
    return full_path;
}

std::string getResultFullPath_mtx(const std::string path, const std::string file)
{
    std::cout << "The Matrix Name : " << file << std::endl;
    std::string full_path = std::string(PROJECT_PATH) + path + file + "/" + file + "_result.mtx";
    std::cout << full_path << std::endl;
    return full_path;
}

/**
 * @brief Check if the input file exists
 *
 * @param[in] full_path The full path of the input file.
 * @return true The file exits.
 * @return false The file doesn't exits.
 */
bool check_file(const std::string full_path)
{
    struct stat buffer;
    return (stat(full_path.c_str(), &buffer) == 0);
}

/**
 * @brief Interface for performing a gtest unit test of performance.
 * @details It is used to print some basic information and skip the unit test of the input matrix not found,
 * @param[in] full_path The full path of the input graph matrix.
 * @param[in] func The function of unit test.
 */
void run_gtest(const std::string full_path,
               void (*func)(const std::string))
{
    if (check_file(full_path))
    {
        func(full_path);
    }
    else
    {
        std::cout << "Can't find the matrix :" << std::endl;
        std::cout << full_path << std::endl;
        std::cout << "\033[0;1;33m"
                  << "This test will be skipped!"
                  << "\033[0m" << std::endl;
        GTEST_SKIP();
    }
}

/**
 * @brief Interface for performing a gtest unit test of performance.
 * @details It is used to print some basic information and skip the unit test of the input matrix not found. Some tests may need to input some parameters in addition to the input matrix. Therefore, use this interface instead of the above interface.
 * @param[in] full_path The full path of the input graph matrix.
 * @param[in] args Pointer to the incoming parameter of the unit test function.
 * @param[in] func The function of unit test.
 */
void run_gtest(const std::string full_path, void *args,
               void (*func)(const std::string, void *))
{
    if (check_file(full_path))
    {
        func(full_path, args);
    }
    else
    {
        std::cout << "Can't find the matrix :" << std::endl;
        std::cout << full_path << std::endl;
        std::cout << "\033[0;1;33m"
                  << "This test will be skipped!"
                  << "\033[0m" << std::endl;
        GTEST_SKIP();
    }
}

/**
 * @brief Interface for performing a gtest unit test of correctness.
 * @details It is used to print some basic information and skip the unit test of the input matrix not found.
 * @param[in] full_path The full path of the input graph matrix.
 * @param[in] result_path The full path of the result to check.
 * @param[in] func The function of unit test.
 */
void run_gtest(const std::string full_path,
               const std::string result_path,
               void (*func)(const std::string, const std::string))
{
    bool matrix_flag = check_file(full_path);
    bool result_flag = check_file(result_path);

    if (matrix_flag && result_flag)
    {
        func(full_path, result_path);
    }
    else if (!matrix_flag)
    {
        std::cout << "Can't find the matrix :" << std::endl;
        std::cout << full_path << std::endl;
        std::cout << "\033[0;1;33m"
                  << "This test will be skipped!"
                  << "\033[0m" << std::endl;
        GTEST_SKIP();
    }
    else
    {
        std::cout << "Can't find the result :" << std::endl;
        std::cout << result_path << std::endl;
        std::cout << "\033[0;1;33m"
                  << "This test will be skipped!"
                  << "\033[0m" << std::endl;
        GTEST_SKIP();
    }
}

/**
 * @brief Interface for performing a gtest unit test of correctness.
 * @details It is used to print some basic information and skip the unit test of the input matrix not found. Some tests may need to input some parameters in addition to the input matrix. Therefore, use this interface instead of the above interface.
 * @param[in] full_path The full path of the input graph matrix.
 * @param[in] result_path The full path of the result to check.
 * @param[in] arg Pointer to the incoming parameter of the unit test function.
 * @param[in] func The function of unit test.
 */
void run_gtest(const std::string full_path,
               const std::string result_path,
               void *args,
               void (*func)(const std::string, const std::string, void *))
{
    bool matrix_flag = check_file(full_path);
    bool result_flag = check_file(result_path);

    if (matrix_flag && result_flag)
    {
        func(full_path, result_path, args);
    }
    else if (!matrix_flag)
    {
        std::cout << "Can't find the matrix :" << std::endl;
        std::cout << full_path << std::endl;
        std::cout << "\033[0;1;33m"
                  << "This test will be skipped!"
                  << "\033[0m" << std::endl;
        GTEST_SKIP();
    }
    else
    {
        std::cout << "Can't find the result :" << std::endl;
        std::cout << result_path << std::endl;
        std::cout << "\033[0;1;33m"
                  << "This test will be skipped!"
                  << "\033[0m" << std::endl;
        GTEST_SKIP();
    }
}