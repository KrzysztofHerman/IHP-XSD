#include <memory>   // std::unique_ptr
#include <iostream>
#include <string>

#include "basicihp.hxx"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "usage: " << argv[0] << " basicihp.xml" << endl;
        return 1;
    }

    try
    {
        // Parse the XML file into a Library object
        unique_ptr<Library> library = Library_(argv[1]);

        // Access the Component inside the Library
        const Component& component = library->Component();

        // Print component details
        cout << "Component Name: " << component.name() << endl;
        cout << "Schematic ID: " << component.schematic_id() << endl;
        cout << "Show Name: " << (component.show_name() ? "true" : "false") << endl;
        cout << "Description: " << component.Description() << endl;

        // Access Netlists (no need to check .present(), access directly)
        cout << "Ngspice Netlist: " << component.Netlists().NgspiceNetlist().value() << endl;

        // Access Symbols
        cout << "Symbol File: " << component.Symbols().Symbol().File() << endl;

        // Access Parameters
        for (const Parameter& param : component.Parameters().Parameter())
        {
            cout << "Parameter Name: " << param.name() << endl;
            cout << "Description: " << param.Description() << endl;
            cout << "Unit: " << param.unit() << endl;
            cout << "Default Value: " << param.default_value() << endl;
            cout << "Show: " << (param.show() ? "true" : "false") << endl;
        }
    }
    catch (const xml_schema::exception& e)
    {
        cerr << e << endl;
        return 1;
    }

    return 0;
}

