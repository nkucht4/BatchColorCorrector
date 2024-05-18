#ifndef SETTINGS_H
#define SETTINGS_H
#include <qstring.h>
#include <string>

enum class System{
    LINUX,
    WINDOWS
};

class settings
{
 private:
    QString d_path_;
    double fps_;

public:
    settings();

    QString qd_path()const;
    std::string d_path()const;
    double fps()const;
};

#endif // SETTINGS_H
