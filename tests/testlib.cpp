#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <modern/lib.hpp>

#include <fstream>
#include <sstream>

const std::string FIXTURES_PATH(TEST_DATA_PATH);

TEST_CASE( "Quick check", "[main]" ) {
    std::string number_file_path = FIXTURES_PATH + "numbers.txt";
    std::ifstream fid(number_file_path);
    if(!fid){
      exit(-1);
    }

    std::vector<double> values;
    for (std::string line; std::getline(fid, line); ) {
      values.push_back(std::stod(line));
    }
    fid.close();

    // std::vector<double> values {1, 2., 3.};
    auto [mean, moment] = accumulate_vector(values);

    REQUIRE( mean == 2.0 );
    REQUIRE( moment == Approx(4.666666).margin(0.000001) );
}
