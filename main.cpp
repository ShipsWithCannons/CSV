#include <iterator>
#include <iostream>

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

typedef std::string Number;
typedef std::string Designation;
typedef std::string AdministrativeRegion;
typedef std::string Country;
typedef std::string Domain;
typedef std::string DateOfEntry;

struct ituCountry {
    /* List and format used: http://www.itu.int/online/mm/scripts/gensel8 */

    ituCountry(){};
    ituCountry(
        Number init_number,
        Designation init_designation,
        AdministrativeRegion init_administrativeRegion,
        Country init_country,
        Domain init_domain,
        DateOfEntry init_dateOfEntry
    )
    {
        number = init_number;
        designation = init_designation;
        administrativeRegion = init_administrativeRegion;
        country = init_country;
        domain = init_domain;
        dateOfEntry = init_dateOfEntry;
    }

    Number number;
    Designation designation;
    AdministrativeRegion administrativeRegion;
    Country country;
    Domain domain;
    DateOfEntry dateOfEntry;

    std::string printItuCountry()
    {
        std::ostringstream os;
        os << number << ' '
            << designation << ' '
            << administrativeRegion << ' '
            << country << ' '
            << domain << ' '
            << dateOfEntry << '\n';
        return os.str();
    }
};

class csvReader {
    std::vector<ituCountry> countries;

  public:
    void addElement(const ituCountry element) {
        countries.push_back(element);
    }

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    void getElements() {
        for (unsigned int i = 0; i < countries.size(); i++)
        {
            std::cout << countries.at(i).printItuCountry();
        }
    }
};

int main()
{
    std::ifstream  data("data/ITU.csv");
    std::string line;
    csvReader reader;
    while(std::getline(data, line))
    {
        std::stringstream  lineStream(line);
        std::string        cell;

        std::vector<std::string> fields = reader.split( line, ',' );
        ituCountry currentCountry(fields[0], fields[1], fields[2], fields[3], fields[4], fields[5]);
        reader.addElement(currentCountry);
        reader.getElements();
    }
 }
