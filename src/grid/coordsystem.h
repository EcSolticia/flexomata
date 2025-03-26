/**
 * @file coordsystem.h
 * @author Miftahul (ecsolticia@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "statemanager.h"

/**
 * @brief Class for handling coordinates
 * 
 */
class CoordSystem {
    size_t width;
    size_t height;

public:
    
    enum Mode {
        PERIODIC = 0,
        REFLECTIVE = 1
    };
    enum Component {
        X = 0,
        Y = 1
    };

    /**
     * @brief Get the specified component as transformed into the specified coordinate system.
     * 
     * @param parameter The "crude" component.
     * @param mode The coordinate tranformation/systen to be used.
     * @param component The component to get.
     * @return size_t The transformed component.
     */
    size_t get_component(const size_t parameter, Mode mode, Component component) const {
        size_t result;

        size_t dimension = (component == X) ? this->width : this->height;

        switch(mode) {
            case PERIODIC:
                result = parameter % dimension;
                break;
            case REFLECTIVE:
                size_t N = (size_t)(parameter/dimension);
                if (N & 1) {
                    result = (dimension - (parameter % dimension));
                } else {
                    result = parameter % dimension;
                }
                break;
        }

        return result;
    }

    /**
     * @brief Construct a new CoordSystem object
     * 
     * @pre That `width != 0 && height != 0`. Does not check for satisfaction as is it
     * expected that the Grid object constructor will handle the error.
     * @param width 
     * @param height 
     */
    CoordSystem(const size_t width, const size_t height) {
        this->width = width;
        this->height = height;
    }
};