#include <iostream>
#include <vector>
#include <functional>

class Grid {
    size_t width;
    size_t height;

    size_t max_state;

    std::vector<size_t> data;

    bool are_init_vars(const size_t width, const size_t height, const size_t max_state) const;

public:
    // Should be called with the post_init_run wrapper:
    void set_pixel(const size_t x, const size_t y, const size_t value);

    template <typename Func, typename... Args>
    auto post_init_run(Func&& func, Args&&... args)
        -> decltype(std::forward<Func>(func)(std::forward<Args>(args)...)) {
        
        if (!are_init_vars(this->width, this->height, this->max_state)) {
            throw std::runtime_error("Precondition failed: Grid not initialized.");
        }

        return std::forward<Func>(func)(std::forward<Args>(args)...);
    }

    // Should be called with the pre_init_run wrapper:
    void initialize_grid(const size_t width, const size_t height, const size_t max_state);

    template <typename Func, typename... Args>
    auto pre_init_run(Func&& func, Args&&... args)
        -> decltype(std::forward<Func>(func)(std::forward<Args>(args)...)) {
        
        if (are_init_vars(this->width, this->height, this->max_state)) {
            throw std::runtime_error("Precondition failed: Grid already initialized.");
        }

        return std::forward<Func>(func)(std::forward<Args>(args)...);
    }

    Grid();
};