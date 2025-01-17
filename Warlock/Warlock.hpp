#include <iostream>

class Warlock
{
    private:
        std::string _name;
        std::string _title;
        Warlock(); // default constructor = private in this case
        Warlock(const Warlock& original); // copy constuctor = private in this case
        Warlock& operator=(const Warlock& orginal); // copy assignment operator

    public:
        Warlock(const std::string &name, const std::string &title);
        ~Warlock(); // destructor

        const std::string &getName() const;
        const std::string &getTitle() const;
        void setTitle(const std::string& newTitle);
        void introduce() const;
};
