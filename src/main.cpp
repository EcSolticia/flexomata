#include <iostream> // For terminal I/O
#include <stdexcept> // For error-handling

#include "flexomatainterface.h"

int main(int argc, char** argv) {


    try {

    } catch (std::invalid_argument e) {
        std::cerr << "invalid_argument: " << e.what();
    } catch (std::runtime_error e) {
        std::cerr << "runtime_error: " << e.what();
    } catch (std::domain_error e) {
        std::cerr << "domain_error: " << e.what();
    } catch (std::out_of_range e) {
        std::cerr << "out_of_range: " << e.what();
    } catch (std::logic_error e) {
        std::cerr << "logic_error: " << e.what();
    } catch (std::exception e) {
        std::cerr << "An unexpected error occured.";
    } catch (...) {
        std::cerr << "An unkown error occured.";
    }

    //std::cerr << std::endl;
    std::cout << std::endl;

    return 0;
}
