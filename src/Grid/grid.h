#include <iostream>
#include <vector>
#include <functional>

class Grid {
    size_t width;
    size_t height;

    std::vector<size_t> data;

    static bool are_init_vars(const size_t width, const size_t height) {
        return (width && height);
    }

public:
    // Should be called using the post_init_run wrapper:
    void set_data(const std::vector<size_t>& dummy_data);
    void set_pixel(const size_t x, const size_t y, const size_t value);
    size_t get_width() const;
    size_t get_height() const;

    template <typename Func, typename... Args>
    auto post_init_run(Func&& func, Args&&... args)
        -> decltype(std::forward<Func>(func)(std::forward<Args>(args)...)) {
        
        if (!are_init_vars(this->width, this->height)) {
            throw std::runtime_error("Precondition failed: Grid not initialized.");
        }

        return std::forward<Func>(func)(std::forward<Args>(args)...);
    }

    // Should be called using the pre_init_run wrapper:
    void initialize_grid(const size_t width, const size_t height);

    template <typename Func, typename... Args>
    auto pre_init_run(Func&& func, Args&&... args)
        -> decltype(std::forward<Func>(func)(std::forward<Args>(args)...)) {
        
        if (are_init_vars(this->width, this->height)) {
            throw std::runtime_error("Precondition failed: Grid already initialized.");
        }

        return std::forward<Func>(func)(std::forward<Args>(args)...);
    }

    Grid();
};