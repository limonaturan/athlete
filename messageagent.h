#ifndef MESSAGEAGENT_H
#define MESSAGEAGENT_H

#include <QObject>
#include <QWidget>

class MessageAgent : public QWidget
{
    Q_OBJECT
public:
    static MessageAgent *getInstance();

    void emitTileClicked();
    void emitProfileChanged();

signals:
    void tileClicked();
    void profileChanged();

private:
    MessageAgent();
    static MessageAgent *instance;
};

#endif // MESSAGEAGENT_H
