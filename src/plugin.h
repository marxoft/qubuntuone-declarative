#include <QDeclarativeExtensionPlugin>

namespace QtUbuntuOne {

class Plugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT

public:
    void registerTypes(const char *uri);
};

}
