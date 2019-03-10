#include "../include/Graph.h"
#include "../include/IO.h"
#include "../include/headers.h"

#include "../third_party/args.hxx"

#include "../include/Solve.h"

Graph *G;
Solve *solve;
IO io;

int main(int argc, char *argv[]) {

	/*-----Arguments setting-----*/

    args::ArgumentParser parser("Clique100: A clique seeking algorithm\n",
                                "Zhenyu Guo");
    args::HelpFlag help(parser, "help", "Display this help menu",
                        {'h', "help"});
    args::Group required(parser, "", args::Group::Validators::All);
    args::Positional<std::string> file(required, "file", "Data file");

    try {
        parser.ParseCLI(argc, argv);
    } catch (args::Help) {
        std::cout << parser;
        return 0;
    } catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    } catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

	/*-----Main process-----*/

    io.input(G, args::get(file));

    solve = new Solve(G);

    solve->searching();

    return 0;
}